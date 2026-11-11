#!/usr/bin/env bash
# 독립 Bash에서 실행: bash foreground_background.sh
set -m
cleanup() {
    for pid in $(jobs -pr); do kill -TERM -- "-$pid" 2>/dev/null || :; done
    wait 2>/dev/null || :
}
trap cleanup EXIT
set -x
sleep 100 &
sleep 100 &
jobs
ps -f
kill %1
# 종료와 회수를 기다린 뒤 ps를 찍어 실행 시점에 따른 차이를 없앤다.
wait %1 2>/dev/null || :
ps -f
set +x
