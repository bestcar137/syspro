# 과제 1 — 실행환경 정보 출력

`process_info.c` 하나에서 과제의 여섯 경우를 모두 처리한다.

| 실행 인자               | 출력                                  | 사용 함수/변수          |
|-------------------------|---------------------------------------|-------------------------|
| `-e`                    | 전체 환경변수를 `이름=값` 형태로 출력 | `environ`               |
| `-e PATH` 또는 `-ePATH` | PATH 환경변수의 값                    | `getenv()`              |
| `-u`                    | 실제·유효 사용자 ID                   | `getuid()`, `geteuid()` |
| `-g`                    | 실제·유효 그룹 ID                     | `getgid()`, `getegid()` |
| `-i`                    | 현재 프로세스 ID                      | `getpid()`              |
| `-p`                    | 부모 프로세스 ID                      | `getppid()`             |

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -o process_info process_info.c
./process_info -e
./process_info -e PATH
./process_info -u
./process_info -g
./process_info -i
./process_info -p
./process_info -u -g -i -p
```

CLion의 Program arguments에 `-e PATH` 등 필요한 인자를 입력한다. 프로그램 실행 후 키보드로 입력하는 방식이 아니다.

실제 ID는 프로세스를 실행한 사용자의 신원을 나타내고, 유효 ID는 파일 접근 등 권한 검사에 사용된다. 일반적인 실행에서는 두 ID가 같지만 set-user-ID/set-group-ID 등의 상황에서는 다를 수
있다. PID와 사용자 ID는 서로 다른 개념이다.

인자가 없거나 알 수 없는 옵션이면 사용법과 오류를 출력하고 실패 상태로 종료한다. 없는 환경변수도 오류로 처리한다. 값이 빈 문자열인 환경변수는 존재하는 변수이므로 정상 출력한다. 여러 옵션은 입력한 순서대로
처리하며, 옵션 묶음인 `-ug`는 지원하지 않는다.

`execution.txt`에는 여섯 경우의 실제 실행 결과를 저장했다. 전체 환경변수 검증은 재현용으로 지정한 PATH, HOME, CHAP08_TEST, EMPTY만 전달한 환경에서 수행했다. 일반 실행 시에는
해당 프로세스가 물려받은 실제 환경변수가 출력된다. PID는 실행마다 달라진다.
