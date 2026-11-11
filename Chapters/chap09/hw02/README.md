# 과제 2 — 작업제어 실습

## 원문 명령의 의미

```bash
(echo START1; sleep 10; echo DONE1) &
(echo START2; sleep 10; echo DONE2) &
kill -KILL %1
kill -STOP %1
kill -CONT %1
```

괄호 안 명령은 서브쉘에서 순서대로 실행된다. 각각 START1 또는 START2를 출력하고 10초를 기다린 뒤 DONE1 또는 DONE2를 출력한다. 두 작업에 `&`가 붙어 있어 서로 동시에 실행되며
START1과 START2의 출력 순서는 보장되지 않는다.

| 신호              | 의미                                                                      |
|-------------------|---------------------------------------------------------------------------|
| SIGKILL (`-KILL`) | 대상 프로세스를 강제로 종료한다. 프로세스가 신호를 잡거나 무시할 수 없다. |
| SIGSTOP (`-STOP`) | 살아 있는 프로세스의 실행을 정지한다. 종료는 아니며 무시할 수 없다.       |
| SIGCONT (`-CONT`) | 정지된 프로세스를 다시 실행 가능한 상태로 만든다.                         |

원문의 순서대로 같은 첫 프로세스에 신호를 보내면 **KILL 이후에는 이미 종료되었으므로 STOP과 CONT로 정지하거나 되살릴 수 없다.** 작업을 회수한 뒤 `%1`로 지정하면 `no such job`, 사라진
PID를 지정하면 `No such process` 오류가 발생한다.

여기서는 원문의 “첫 번째 프로세스”를 첫 번째 후면 작업 전체로 해석해 `%1`로 지정했다. 작업 제어가 켜진 Bash에서 작업 번호를 대상으로 신호를 보내면 서브쉘과 그 안의 `sleep`이 속한 프로세스 그룹에
전달된다. 서브쉘 PID 하나만 KILL하면 그 안에서 실행 중이던 `sleep`이 남을 수 있다.

## STOP과 CONT를 확인하는 별도 실험

첫 실험을 마친 후 새 작업을 시작한다.

```bash
(echo START1; sleep 10; echo DONE1) &
kill -STOP %+
jobs -l
kill -CONT %+
jobs -l
wait %+
```

`%+`는 현재 작업을 뜻한다. STOP 뒤 `jobs`는 `Stopped`를 표시하고, CONT 뒤에는 `Running`이 된다. 재개된 작업은 결국 DONE1을 출력한다. 정지 중에도 실제 시간이 흐르므로
`sleep`이 요청한 대기 시간이 이미 지났다면 재개 후 곧 끝날 수 있다.

## 실제 실행 결과

`execution.txt`에 전체 로그를 저장했다.

- 첫 작업 PID 39312를 KILL한 뒤 두 신호 전달이 `no such job`으로 실패했다.
- 두 번째 작업은 정상적으로 DONE2를 출력했다. 종료된 첫 작업은 DONE1을 출력하지 않았다.
- 새 작업 PID 40419에서 `Stopped (signal)` → `Running` 전환과 DONE1 출력을 확인했다.

PID는 실행마다 달라진다. 스크립트의 짧은 대기는 START 출력과 상태 관찰을 위한 것이며, 종료 시 남은 실습 작업은 정리한다.

```bash
cd /home/bestcar137/CLionProjects/syspro/Chapters/chap09/hw02
bash job_control.sh
```

전체 실습은 약 20초 걸린다.
