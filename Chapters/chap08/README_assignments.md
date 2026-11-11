# 8장 과제 1~3

다운로드 폴더의 `8장-시스템 프로그래밍_8장_실습문제.pdf` 23~29쪽과 강의 자료 `chap8.pdf`, 기존 `chap08/prob01`~`prob06` 코드를 참고했다.

| 과제 | 소스 | 설명/실행 기록 |
| --- | --- | --- |
| 1 | `hw01/process_info.c` | `hw01/README.md`, `hw01/execution.txt` |
| 2 | `hw02/process_relation.c` | `hw02/README.md`, `hw02/execution.txt` |
| 3 | `hw03/fork_example.c` | `hw03/README.md`, `hw03/execution.txt` |

## WSL에서 실행

```bash
cd /home/bestcar137/CLionProjects/syspro/Chapters/chap08
gcc -std=c11 -Wall -Wextra -Wpedantic -o hw01/process_info hw01/process_info.c
gcc -std=c11 -Wall -Wextra -Wpedantic -o hw02/process_relation hw02/process_relation.c
gcc -std=c11 -Wall -Wextra -Wpedantic -o hw03/fork_example hw03/fork_example.c
./hw01/process_info -e PATH
./hw01/process_info -u -g -i -p
./hw02/process_relation
./hw03/fork_example
```

## CLion 실행 대상

CMake 프로젝트를 새로고침하고 다음 대상을 선택한다.

- `chap08_hw01_process_info`: Program arguments에 `-e PATH`, `-u` 등 입력
- `chap08_hw02_process_relation`: 인자 없음
- `chap08_hw03_fork_example`: 인자 없음

## 검증

세 소스를 `-std=c11 -Wall -Wextra -Wpedantic -Werror -fsanitize=undefined`로 컴파일하고 실행했다. 과제 1의 여섯 조회 경우, 붙여 쓴 환경변수 옵션, 빈 값/없는 환경변수, 잘못된 옵션, 인자 누락, 다중 옵션을 검사했다. PID와 PPID는 테스트 실행기가 알고 있는 실제 값과 대조했다. 과제 2는 의사 터미널에서 Bash 및 `ps` 목록과 비교했고, 과제 3은 세 번 실행하여 출력 두 줄과 부모·자식 PID 관계를 확인했다.
