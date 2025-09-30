cmake_minimum_required(VERSION 4.0)
project(syspro C)

set(CMAKE_C_STANDARD 11)

# =======================
# chap03 과제들
# =======================

# chap03/hw01 실행 파일
add_executable(chap03_hw01
        Chapters/chap03/hw01/main.c
        Chapters/chap03/hw01/copy.c
)

# chap03/prob01 실행 파일
add_executable(chap03_prob01
        Chapters/chap03/prob01/main.c
        Chapters/chap03/prob01/copy.c
)

# =======================
# chap04, chap05도 같은 방식으로 추가
# 예시:
# add_executable(chap04_hw01 Chapters/chap04/hw01/main.c ...)
# =======================
