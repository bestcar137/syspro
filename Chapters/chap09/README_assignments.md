# 9장 과제 1~4

강의 자료의 `fork()`, `execvp()`, `waitpid()`, `open()`, `dup2()`와 기존 `prob03/execute*.c`, `prob05/redirect*.c`를 참고했다.

| 과제 | 제출 자료 | 내용 |
| --- | --- | --- |
| 1 | `hw01/README.md`, `foreground_background.sh`, `execution.txt` | 전면·후면 처리 설명, 실행 스크립트, 실제 로그 |
| 2 | `hw02/README.md`, `job_control.sh`, `execution.txt` | 작업 신호 설명, 실행 스크립트, 실제 로그 |
| 3 | `hw03/shell1.c` | 명령 실행, `;` 순차 실행, `&` 후면 실행, `<`·`>` 리디렉션 |
| 4 | `hw04/shell2.c` | `strtok_r()`로 인수 분리, 전면·후면 실행 |

## 컴파일 및 실행

WSL 터미널에서 실행한다.

```bash
cd /home/bestcar137/CLionProjects/syspro/Chapters/chap09
gcc -std=c11 -Wall -Wextra -Wpedantic -o hw03/shell1 hw03/shell1.c
gcc -std=c11 -Wall -Wextra -Wpedantic -o hw04/shell2 hw04/shell2.c
./hw03/shell1
# 종료하려면 exit 또는 Ctrl+D
./hw04/shell2
```

CLion은 CMake를 새로고침하고 `chap09_hw03_shell1`, `chap09_hw04_shell2`를 선택한다. 과제 1·2는 Bash 실습이므로 C 실행 대상이 없다.

## 과제 3 사용 예

```text
[shell] echo hello
hello
[shell] echo first; echo second; echo third
first
second
third
[shell] sleep 3 &
[background] (실제 자식 PID)
[shell] echo payload > output.txt
[shell] cat < output.txt
payload
[shell] cat < output.txt > copy.txt
[shell] exit
```

`>`는 파일이 없으면 생성하고, 있으면 기존 내용을 지운 뒤 출력한다. `<`는 지정한 파일을 표준 입력으로 사용한다. 공백 없이 `echo hello>output.txt`처럼 입력해도 연산자를 구분한다. `;` 앞의 전면 명령이 끝나야 다음 명령을 실행하며, `&` 앞의 명령은 기다리지 않는다.

## 과제 4 사용 예

```text
[Shell] ls -l
(현재 디렉터리 목록)
[Shell] sleep 3 &
[background] (실제 자식 PID)
[Shell] echo hello
hello
[Shell] exit
```

끝의 `&`를 먼저 제거한 뒤 `strtok_r()`로 공백과 탭, 줄바꿈을 구분하여 `char *args[MAXARG]`에 저장한다. 마지막 인수 다음에는 NULL을 넣고 `execvp(args[0], args)`를 호출한다.

## 공통 구현 설명과 범위

1. 프롬프트를 출력하고 `getline()`으로 한 줄을 읽는다. 터미널이 아닌 입력에서는 프롬프트를 생략한다.
2. 명령과 인수를 분리한 뒤 `fork()`로 자식을 만든다.
3. 자식은 필요한 리디렉션을 적용하고 `execvp()`로 명령을 실행한다. 실행 실패 시 오류를 출력하고 `_exit(127)`로 끝난다.
4. 전면 실행은 `waitpid(pid, ...)`로 해당 자식만 기다린다. 후면 실행은 PID를 출력하고 즉시 다음 입력으로 진행한다.
5. 종료된 후면 자식은 명령 처리 사이와 다음 입력 직전에 `waitpid(-1, ..., WNOHANG)`으로 회수한다. 입력을 기다리는 도중 종료한 자식은 다음 입력이 올 때까지 잠시 좀비로 남을 수 있다.

후면 자식은 별도 프로세스 그룹을 사용하며 입력 파일이 없으면 표준 입력을 `/dev/null`로 연결한다. 따라서 쉘의 명령 입력을 후면 프로그램이 가져가지 않는다. `exit` 시 아직 실행 중인 후면 작업의 완료를 기다리거나 강제 종료하지 않는다.

학습용으로 요구된 문법을 구현했다. 따옴표, 이스케이프, 파이프, 변수 확장, 와일드카드, `cd`·`jobs`·`fg`·`bg` 내장 명령과 완전한 터미널 작업 제어는 지원하지 않는다. 과제 4는 `;`, `<`, `>`도 지원하지 않는다. 파일명과 인수에 공백이 없어야 하며 인수/토큰 한도는 127개이다. 과제 3에서 앞 명령을 이미 실행한 뒤 뒤 명령의 구문 오류를 발견하면 앞 명령의 실행은 되돌리지 않는다.

## 검증

WSL GCC의 `-Wall -Wextra -Wpedantic -Werror` 컴파일 및 UndefinedBehaviorSanitizer 실행을 통과했다. 일반 명령, 빈 입력, 잘못된 명령 후 계속 실행, 인수 한도, 전면 대기, 후면 즉시 반환, 종료 자식 회수를 검사했다. 과제 3은 순차 출력, 파일 생성·덮어쓰기·입출력 동시 재지정, 없는 입력 파일, 누락된 리디렉션 파일명도 확인했다.
