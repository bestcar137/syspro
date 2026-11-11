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

# 각 실습의 디렉터리와 소스를 명시적으로 등록한다.
function(add_exercise target directory)
    list(TRANSFORM ARGN PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/Chapters/${directory}/")
    add_executable(${target} ${ARGN})
endfunction()

# chap03
add_exercise(chap03_hw01_main chap03/hw01 main.c copy.c)
add_exercise(chap03_prob01_main chap03/prob01 main.c copy.c)

# chap04
add_exercise(chap04_hw01_append chap04/hw01 append.c)
add_exercise(chap04_hw02_catEX chap04/hw02 catEX.c)
add_exercise(chap04_prob01_cat chap04/prob01 cat.c)
add_exercise(chap04_prob02_copy chap04/prob02 copy.c)
add_exercise(chap04_prob03_line chap04/prob03 line.c)
add_exercise(chap04_prob04_fprint chap04/prob04 fprint.c)
add_exercise(chap04_prob05_fscan chap04/prob05 fscan.c)
add_exercise(chap04_prob06_stcreate1 chap04/prob06 stcreate1.c)
add_exercise(chap04_prob07_stprint chap04/prob07 stprint.c)
add_exercise(chap04_prob08_buffer chap04/prob08 buffer.c)

# chap05
add_exercise(chap05_hw01_selectorLine chap05/hw01 selectorLine.c)
add_exercise(chap05_hw02_reverseLine chap05/hw02 reverseLine.c)
add_exercise(chap05_prob01_fopen chap05/prob01 fopen.c)
add_exercise(chap05_prob02_fsize chap05/prob02 fsize.c)
add_exercise(chap05_prob03_copy chap05/prob03 copy.c)
add_exercise(chap05_prob04_dup chap05/prob04 dup.c)
add_exercise(chap05_prob05_dbcreate chap05/prob05 dbcreate.c)
add_exercise(chap05_prob06_dbquery chap05/prob06 dbquery.c)
add_exercise(chap05_prob07_dbupdate chap05/prob07 dbupdate.c)

# chap06
add_exercise(chap06_hw02_hw02_list2 chap06/hw02 hw02_list2.c)
add_exercise(chap06_hw02_hw02_sol chap06/hw02 hw02_sol.c)
add_exercise(chap06_prob01_ftype chap06/prob01 ftype.c)
add_exercise(chap06_prob02_fchmod chap06/prob02 fchmod.c)
add_exercise(chap06_prob03_cptime chap06/prob03 cptime.c)
add_exercise(chap06_prob04_list1 chap06/prob04 list1.c)
add_exercise(chap06_prob05_list2 chap06/prob05 list2.c)
add_exercise(chap06_prob06_link chap06/prob06 link.c)
add_exercise(chap06_prob07_unlink chap06/prob07 unlink.c)
add_exercise(chap06_prob08_slink chap06/prob08 slink.c)
add_exercise(chap06_prob09_rlink chap06/prob09 rlink.c)

# chap07
add_exercise(chap07_hw01_test_locks chap07/hw01 test_locks.c locks.c)

# main()이 없는 함수 구현은 정적 라이브러리로 빌드한다.
add_library(chap07_hw02_lockt STATIC
    Chapters/chap07/hw02/lockt.c
)
add_exercise(chap07_prob01_rdlock chap07/prob01 rdlock.c)
add_exercise(chap07_prob01_wrlock chap07/prob01 wrlock.c)
add_exercise(chap07_prob02_wrlockf chap07/prob02 wrlockf.c)

# chap08
add_exercise(chap08_hw01_process_info chap08/hw01 process_info.c)
add_exercise(chap08_hw02_process_relation chap08/hw02 process_relation.c)
add_exercise(chap08_hw03_fork_example chap08/hw03 fork_example.c)
add_exercise(chap08_prob01_args chap08/prob01 args.c)
add_exercise(chap08_prob02_environ chap08/prob02 environ.c)
add_exercise(chap08_prob03_myenv chap08/prob03 myenv.c)
add_exercise(chap08_prob04_exit_handler chap08/prob04 exit_handler.c)
add_exercise(chap08_prob05_pid chap08/prob05 pid.c)
add_exercise(chap08_prob06_uid chap08/prob06 uid.c)

# chap09
add_exercise(chap09_hw03_shell1 chap09/hw03 shell1.c)
add_exercise(chap09_hw04_shell2 chap09/hw04 shell2.c)
add_exercise(chap09_prob01_fork1 chap09/prob01 fork1.c)
add_exercise(chap09_prob01_fork2 chap09/prob01 fork2.c)
add_exercise(chap09_prob01_fork3 chap09/prob01 fork3.c)
add_exercise(chap09_prob02_forkwait chap09/prob02 forkwait.c)
add_exercise(chap09_prob02_waitpid chap09/prob02 waitpid.c)
add_exercise(chap09_prob03_execute1 chap09/prob03 execute1.c)
add_exercise(chap09_prob03_execute2 chap09/prob03 execute2.c)
add_exercise(chap09_prob03_execute3 chap09/prob03 execute3.c)

# main()이 없는 함수 구현은 정적 라이브러리로 빌드한다.
add_library(chap09_prob04_mysystem STATIC
    Chapters/chap09/prob04/system.c
)
add_exercise(chap09_prob04_syscall chap09/prob04 syscall.c)
add_exercise(chap09_prob05_redirect1 chap09/prob05 redirect1.c)
add_exercise(chap09_prob05_redirect2 chap09/prob05 redirect2.c)
add_exercise(chap09_prob06_pgrp1 chap09/prob06 pgrp1.c)
add_exercise(chap09_prob06_pgrp2 chap09/prob06 pgrp2.c)

# chap10
add_exercise(chap10_hw01_stack chap10/hw01 stack.c)
add_exercise(chap10_hw02_queue chap10/hw02 queue.c)
add_exercise(Chapters_chap10_prob01_stud1 chap10/prob01 stud1.c)
add_exercise(Chapters_chap10_prob01_stud2 chap10/prob01 stud2.c)
add_exercise(Chapters_chap10_prob02_shm1 chap10/prob02 shm1.c)
add_exercise(Chapters_chap10_prob02_shm2 chap10/prob02 shm2.c)
add_exercise(Chapters_chap10_prob02_shm3 chap10/prob02 shm3.c)
add_exercise(Chapters_chap10_prob03_mem chap10/prob03 mem.c)
add_exercise(Chapters_chap10_prob03_mmap chap10/prob03 mmap.c)

# 참고용 예제
# chap09/reference/exec_placeholder/exec.c는 구현 후 등록한다.
# chap10/reference/vars.c는 fun()의 전방 선언을 추가한 후 등록한다.

# 소스 오류를 수정한 후 개별 빌드하거나 아래 제외 설정을 제거한다.
# chap06_prob07_unlink       - perror 선언을 위한 stdio.h 누락
# chap08_prob04_exit_handler - 33행에 불필요한 백틱 문자
# chap09_prob06_pgrp1/pgrp2  - main 반환형 누락
set_target_properties(
    chap06_prob07_unlink
    chap08_prob04_exit_handler
    chap09_prob06_pgrp1
    chap09_prob06_pgrp2
    PROPERTIES EXCLUDE_FROM_ALL TRUE
)
