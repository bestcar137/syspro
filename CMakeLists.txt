cmake_minimum_required(VERSION 3.31.6)
project(syspro C)

set(CMAKE_C_STANDARD 11)

# =======================
# chap03
# =======================

# hw01 실행 파일
add_executable(chap03_hw01
        Chapters/chap03/hw01/main.c
        Chapters/chap03/hw01/copy.c
)

# prob01 실행 파일
add_executable(chap03_prob01
        Chapters/chap03/prob01/main.c
        Chapters/chap03/prob01/copy.c
)

# =======================
# chap04
# =======================

# prob01 - cat 명령어 프로그램 구현
add_executable(chap04_prob01_cat
        Chapters/chap04/prob01/cat.c
)

# prob02 - 파일 복사 프로그램 구현
add_executable(chap04_prob02_copy
        Chapters/chap04/prob02/copy.c
)

# prob03 - line 명령어 프로그램 구현
add_executable(chap04_prob03_line
        Chapters/chap04/prob03/line.c
)

# prob04 - 입력 받은 학생 정보 파일에 저장
add_executable(chap04_prob04_fprint
        Chapters/chap04/prob04/fprint.c
)

# prob05 - 파일 내 텍스트를 읽어 출력
add_executable(chap04_prob05_fscan
        Chapters/chap04/prob05/fscan.c
)

# prob06 - 구조체를 이용한 학생 정보 파일에 저장
add_executable(chap04_prob06_stcreate1
        Chapters/chap04/prob06/stcreate1.c
)

# prob07 - 파일 내 저장된 학생 레코드 출력
add_executable(chap04_prob07_stprint
        Chapters/chap04/prob07/stprint.c
)

# prob08 - 파일의 버퍼 사용 방식에 따른 출력
add_executable(chap04_prob08_buffer
        Chapters/chap04/prob08/buffer.c
)

# hw02 - 실습 1번 cat 프로그램을 기반으로 여러 개의 파일을 받으면 순차적으로 파일 내용 출력되도록 확장
add_executable(Chapters_chap04_hw02_catEX
        Chapters/chap04/hw02/catEX.c
)