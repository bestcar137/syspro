# 과제 2 — 현재 프로세스와 부모 프로세스의 관계

`process_relation.c`는 PDF 28쪽 예제처럼 `getpid()`, `getppid()`를 출력하고 `system("ps")`로 실행 중인 프로세스를 확인한다.

## 실제 실행 결과

```text
launcher bash PID: 43329
my process number : [43330]
my parent's process number : [43329]
    PID TTY          TIME CMD
  43329 pts/7    00:00:00 bash
  43330 pts/7    00:00:00 process_relatio
  43331 pts/7    00:00:00 sh
  43332 pts/7    00:00:00 ps
relation program finished
```

전체 로그는 `execution.txt`에 있다. 처음과 마지막 줄은 검증용 Bash가 출력한 줄이다.

첫 번째 출력 43330은 실행 중인 프로그램 자신을 나타내며 `ps`의 `process_relatio` 행 PID와 일치한다. 명령 이름은 `ps`에서 잘려 표시되었다.

두 번째 출력 43329는 이 프로그램을 생성한 부모 프로세스 번호이다. 실행용 Bash가 출력한 자신의 PID 및 `ps`의 `bash` 행 PID와 일치한다. 따라서 이 실행에서는 Bash가 부모이고 프로그램이
자식이다. CLion에서 실행하면 IDE의 실행 도구나 중간 프로세스가 부모가 될 수 있어 반드시 Bash인 것은 아니다.

`system("ps")`는 명령을 해석할 `/bin/sh`를 통해 `ps`를 실행하고 완료될 때까지 기다린다. 이 실행에서는 프로그램 외에 `sh`, `ps`가 목록에 나타났다. 쉘 구현이나 실행 최적화에 따라
중간 `sh`가 별도 행으로 보이지 않을 수도 있다. `ps` 기본 출력에는 PPID 열이 없으므로 목록에서 부모 관계 자체를 직접 확인하려면 `ps -f`를 사용한다.

PDF의 출력 흐름을 유지하면서 `fflush(stdout)`와 `system()` 반환 상태 검사를 추가했다. `fflush()`는 출력이 파일로 향할 때도 앞의 두 줄이 `ps` 출력보다 먼저 나오게 한다.
PID는 실행마다 달라지며 앞뒤 프로세스 번호가 연속일 필요는 없다.

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -o process_relation process_relation.c
./process_relation
```

목록 비교는 WSL 터미널에서 실행하는 것이 편리하다.
