#!/usr/bin/env bash
# 독립 Bash에서 실행: bash job_control.sh
set -m
cleanup() {
    for pid in $(jobs -pr) $(jobs -ps); do
        kill -KILL -- "-$pid" 2>/dev/null || :
    done
    wait 2>/dev/null || :
}
trap cleanup EXIT
set -x
(echo START1; sleep 10; echo DONE1) &
first=$!
(echo START2; sleep 10; echo DONE2) &
second=$!
sleep 0.2
jobs -l
# 작업 전체(서브쉘과 sleep)에 신호를 보낸다.
kill -KILL %1
wait "$first" 2>/dev/null || :
# 이미 종료된 첫 작업이므로 아래 두 명령은 실패한다.
kill -STOP %1
kill -CONT %1
wait "$second"
set +x
printf '\n--- 새 작업에서 STOP/CONT 확인 ---\n'
set -x
(echo START1; sleep 10; echo DONE1) &
resumed=$!
sleep 0.2
kill -STOP %+
sleep 0.2
jobs -l
kill -CONT %+
jobs -l
wait "$resumed"
set +x
