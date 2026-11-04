cmake_minimum_required(VERSION 3.31.6)
project(syspro LANGUAGES C)

# Linux / WSL의 POSIX 시스템 프로그래밍 실습 프로젝트입니다.
# 각 실행 대상: chapNN_probNN_파일명 또는 chapNN_hwNN_파일명
# 여러 main()을 하나의 실행 파일로 연결하지 않습니다.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
# lockf 등 강의 예제에서 사용하는 Unix 확장을 허용합니다.
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(WARNING "Linux / WSL toolchain is recommended for these POSIX exercises.")
endif()

# 소스를 명시적으로 등록합니다. 새 예제 추가 시 해당 장에 대상을 추가하세요.

# ============================================================================
# chap03
# ============================================================================

add_executable(chap03_hw01_main
    Chapters/chap03/hw01/main.c
    Chapters/chap03/hw01/copy.c
)

add_executable(chap03_prob01_main
    Chapters/chap03/prob01/main.c
    Chapters/chap03/prob01/copy.c
)

# ============================================================================
# chap04
# ============================================================================

add_executable(chap04_hw01_append
    Chapters/chap04/hw01/append.c
)

add_executable(chap04_hw02_catEX
    Chapters/chap04/hw02/catEX.c
)

add_executable(chap04_prob01_cat
    Chapters/chap04/prob01/cat.c
)

add_executable(chap04_prob02_copy
    Chapters/chap04/prob02/copy.c
)

add_executable(chap04_prob03_line
    Chapters/chap04/prob03/line.c
)

add_executable(chap04_prob04_fprint
    Chapters/chap04/prob04/fprint.c
)

add_executable(chap04_prob05_fscan
    Chapters/chap04/prob05/fscan.c
)

add_executable(chap04_prob06_stcreate1
    Chapters/chap04/prob06/stcreate1.c
)

add_executable(chap04_prob07_stprint
    Chapters/chap04/prob07/stprint.c
)

add_executable(chap04_prob08_buffer
    Chapters/chap04/prob08/buffer.c
)

# ============================================================================
# chap05
# ============================================================================

add_executable(chap05_hw01_selectorLine
    Chapters/chap05/hw01/selectorLine.c
)

add_executable(chap05_hw02_reverseLine
    Chapters/chap05/hw02/reverseLine.c
)

add_executable(chap05_prob01_fopen
    Chapters/chap05/prob01/fopen.c
)

add_executable(chap05_prob02_fsize
    Chapters/chap05/prob02/fsize.c
)

add_executable(chap05_prob03_copy
    Chapters/chap05/prob03/copy.c
)

add_executable(chap05_prob04_dup
    Chapters/chap05/prob04/dup.c
)

add_executable(chap05_prob05_dbcreate
    Chapters/chap05/prob05/dbcreate.c
)

add_executable(chap05_prob06_dbquery
    Chapters/chap05/prob06/dbquery.c
)

add_executable(chap05_prob07_dbupdate
    Chapters/chap05/prob07/dbupdate.c
)

# ============================================================================
# chap06
# ============================================================================

add_executable(chap06_hw02_hw02_list2
    Chapters/chap06/hw02/hw02_list2.c
)

add_executable(chap06_hw02_hw02_sol
    Chapters/chap06/hw02/hw02_sol.c
)

add_executable(chap06_prob01_ftype
    Chapters/chap06/prob01/ftype.c
)

add_executable(chap06_prob02_fchmod
    Chapters/chap06/prob02/fchmod.c
)

add_executable(chap06_prob03_cptime
    Chapters/chap06/prob03/cptime.c
)

add_executable(chap06_prob04_list1
    Chapters/chap06/prob04/list1.c
)

add_executable(chap06_prob05_list2
    Chapters/chap06/prob05/list2.c
)

add_executable(chap06_prob06_link
    Chapters/chap06/prob06/link.c
)

add_executable(chap06_prob07_unlink
    Chapters/chap06/prob07/unlink.c
)

add_executable(chap06_prob08_slink
    Chapters/chap06/prob08/slink.c
)

add_executable(chap06_prob09_rlink
    Chapters/chap06/prob09/rlink.c
)

# ============================================================================
# chap07
# ============================================================================

add_executable(chap07_hw01_test_locks
    Chapters/chap07/hw01/test_locks.c
    Chapters/chap07/hw01/locks.c
)

add_executable(chap07_prob01_rdlock
    Chapters/chap07/prob01/rdlock.c
)

add_executable(chap07_prob01_wrlock
    Chapters/chap07/prob01/wrlock.c
)

add_executable(chap07_prob02_wrlockf
    Chapters/chap07/prob02/wrlockf.c
)

# main()이 없는 잠금 조회 함수는 정적 라이브러리로 컴파일합니다.
add_library(chap07_hw02_lockt STATIC
    Chapters/chap07/hw02/lockt.c
)

# ============================================================================
# chap08
# ============================================================================

add_executable(chap08_prob01_args
    Chapters/chap08/prob01/args.c
)

add_executable(chap08_prob02_environ
    Chapters/chap08/prob02/environ.c
)

add_executable(chap08_prob03_myenv
    Chapters/chap08/prob03/myenv.c
)

add_executable(chap08_prob04_exit_handler
    Chapters/chap08/prob04/exit_handler.c
)

add_executable(chap08_prob05_pid
    Chapters/chap08/prob05/pid.c
)

add_executable(chap08_prob06_uid
    Chapters/chap08/prob06/uid.c
)

# ============================================================================
# chap09
# ============================================================================

add_executable(chap09_prob01_fork1
    Chapters/chap09/prob01/fork1.c
)

add_executable(chap09_prob01_fork2
    Chapters/chap09/prob01/fork2.c
)

add_executable(chap09_prob01_fork3
    Chapters/chap09/prob01/fork3.c
)

add_executable(chap09_prob02_forkwait
    Chapters/chap09/prob02/forkwait.c
)

add_executable(chap09_prob02_waitpid
    Chapters/chap09/prob02/waitpid.c
)

add_executable(chap09_prob03_execute1
    Chapters/chap09/prob03/execute1.c
)

add_executable(chap09_prob03_execute2
    Chapters/chap09/prob03/execute2.c
)

add_executable(chap09_prob03_execute3
    Chapters/chap09/prob03/execute3.c
)

add_executable(chap09_prob04_syscall
    Chapters/chap09/prob04/syscall.c
)

add_executable(chap09_prob05_redirect1
    Chapters/chap09/prob05/redirect1.c
)

add_executable(chap09_prob05_redirect2
    Chapters/chap09/prob05/redirect2.c
)

add_executable(chap09_prob06_pgrp1
    Chapters/chap09/prob06/pgrp1.c
)

add_executable(chap09_prob06_pgrp2
    Chapters/chap09/prob06/pgrp2.c
)

# syscall.c는 libc의 system()을 호출합니다. mysystem()은 별도 구현입니다.
# system.c는 main()이 없으므로 실행 파일이 아닌 정적 라이브러리입니다.
# 현재 누락된 헤더로 컴파일되지 않아 기본 전체 빌드에서는 제외합니다.
# 헤더를 보완한 후 이 대상을 직접 빌드하거나 EXCLUDE_FROM_ALL을 제거하세요.
add_library(chap09_prob04_mysystem STATIC EXCLUDE_FROM_ALL
    Chapters/chap09/prob04/system.c
)

# reference/exec_placeholder/exec.c는 구현이 없어 빌드 대상에서 제외합니다.
