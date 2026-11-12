# 시스템 프로그래밍

Linux/WSL 환경에서 C 언어로 운영체제의 기능과 시스템 호출을 학습하는 저장소입니다. 파일 입출력, 파일·디렉터리 정보, 잠금, 프로세스와 셸, 메모리 관리 실습 및 과제 자료를 장별로 보관합니다.

## 자료 바로가기

| 구분                                                    | 내용                                         |
|---------------------------------------------------------|----------------------------------------------|
| [장별 소스](Chapters/)                                  | 3~10장 예제와 과제                           |
| [8장 과제 안내](Chapters/chap08/README_assignments.md)  | 실행환경 정보, 부모·자식 프로세스, fork 실습 |
| [9장 과제 안내](Chapters/chap09/README_assignments.md)  | 전면·후면 실행, 작업 제어, 간단한 셸 구현    |
| [10장 과제 안내](Chapters/chap10/README_assignments.md) | 연결 리스트 기반 스택과 큐                   |
| [강의자료](강의자료/)                                   | 1~13장 강의 PDF                              |
| [실습문제](실습문제/)                                   | 2~5장·7~10장 과제 및 실습문제 PDF            |
| [주석 작성 참고](참고/Doxygen%20주석%20작성%20참고.md)  | Doxygen 주석 작성 안내                       |
| [CMake 구성](CMakeLists.txt)                            | 실습별 실행 파일과 정적 라이브러리 등록      |

## 디렉터리 구성

```text
syspro/
├── Chapters/
│   ├── chap03/          # 다중 소스 구성과 문자열 처리
│   ├── chap04/          # 표준 입출력과 학생 레코드
│   ├── chap05/          # 저수준 파일 입출력과 임의 접근
│   ├── chap06/          # 파일 정보·디렉터리·링크
│   ├── chap07/          # 파일 및 레코드 잠금
│   ├── chap08/          # 실행환경·프로세스 정보
│   ├── chap09/          # 프로세스 제어·명령 실행·셸
│   └── chap10/          # 동적 메모리·공유 메모리·자료구조
├── 강의자료/            # 장별 강의 PDF
├── 실습문제/            # 실습과 과제 PDF
├── 참고/                # 개발 참고 문서
├── CMakeLists.txt       # Linux/WSL용 C 빌드 설정
└── README.md            # 저장소 전체 안내
```

각 장의 `probNN/`에는 예제, `hwNN/`에는 과제를 둡니다. 일부 장에는 과제 안내 문서와 참고용 `reference/`가 있습니다. 실습 폴더에는 소스 외에도 입력용 텍스트, 학생 레코드 파일, 실행
기록과 기존 바이너리·오브젝트 파일이 함께 있습니다.

## 장별 학습 내용

| 장   | 위치                       | 주요 내용                                                                |
|------|----------------------------|--------------------------------------------------------------------------|
| 3장  | [chap03](Chapters/chap03/) | `main.c`·`copy.c`·`copy.h`로 구성한 다중 소스 예제와 과제                |
| 4장  | [chap04](Chapters/chap04/) | 표준 스트림, 텍스트 복사·출력, 줄 처리, 구조체 레코드의 읽기·쓰기와 버퍼 |
| 5장  | [chap05](Chapters/chap05/) | open·read·write, 파일 디스크립터 복제, lseek 기반 레코드 생성·조회·수정  |
| 6장  | [chap06](Chapters/chap06/) | 파일 종류·권한·시간, 디렉터리 목록, 하드 링크와 심볼릭 링크              |
| 7장  | [chap07](Chapters/chap07/) | fcntl·lockf 기반 잠금과 잠금 동작 확인                                   |
| 8장  | [chap08](Chapters/chap08/) | 명령행 인자·환경변수, 종료 처리, PID·PPID·UID·GID 및 fork                |
| 9장  | [chap09](Chapters/chap09/) | fork·wait·exec, system 구현, 입출력 리디렉션, 프로세스 그룹과 셸         |
| 10장 | [chap10](Chapters/chap10/) | malloc, System V 공유 메모리, mmap, 연결 리스트 기반 스택·큐             |

### 과제 안내와 실행 기록

-

8장: [실행환경 정보 조회](Chapters/chap08/hw01/README.md), [부모·자식 관계](Chapters/chap08/hw02/README.md), [fork 동작](Chapters/chap08/hw03/README.md).

- 9장: [전면·후면 처리](Chapters/chap09/hw01/README.md), [작업 제어](Chapters/chap09/hw02/README.md). 셸 과제의 사용 예와 지원 범위는 9장 과제 안내에
  있습니다.
- 10장: 스택은 후입선출, 큐는 선입선출로 입력값을 꺼내며 노드 메모리를 해제합니다. 입력 조건과 출력 예는 10장 과제 안내에 있습니다.

8장 과제 1~3과 9장 과제 1~2 폴더의 `execution.txt`에는 기존 실행 기록이 있습니다. PID와 프로세스 출력 순서는 실행 환경과 시점에 따라 달라집니다.

## 빌드 및 실행

### 환경

- Linux 또는 Ubuntu WSL: POSIX/Unix API를 사용하는 실습입니다.
- CMake 3.31.6 이상과 C 컴파일러, 빌드 도구가 필요합니다.
- CMake는 C11과 Unix 확장을 사용하며 실습마다 독립된 실행 대상을 생성합니다.
- CLion에서는 Linux/WSL 툴체인으로 CMake 프로젝트를 불러옵니다.

### CMake로 개별 실습 실행

다음 명령은 Ubuntu WSL 터미널에서 실행합니다. 기존 IDE 빌드 캐시와 구별되는 임시 폴더를 사용합니다.

```bash
cd /home/bestcar137/CLionProjects/syspro
syspro_build_dir=$(mktemp -d /tmp/syspro-build-XXXXXX)
cmake -S . -B "$syspro_build_dir"
cmake --build "$syspro_build_dir" --target chap08_hw01_process_info
"$syspro_build_dir/chap08_hw01_process_info" -u -g -i -p
```

대부분의 실행 대상 이름은 `chapNN_probNN_파일명` 또는 `chapNN_hwNN_파일명`입니다. 10장의 일부 예제는 `Chapters_chap10_...` 접두사를 사용하므로 정확한 이름은
`CMakeLists.txt`에서 확인합니다. 인자를 사용하는 실습은 CLion의 Program arguments에 필요한 값을 입력합니다.

스택·큐 과제의 빌드와 실행 예:

```bash
cmake --build "$syspro_build_dir" --target chap10_hw01_stack chap10_hw02_queue
printf '10 20 30 0\n' | "$syspro_build_dir/chap10_hw01_stack"
printf '10 20 30 0\n' | "$syspro_build_dir/chap10_hw02_queue"
```

### 실습 폴더에서 직접 컴파일

```bash
cd /home/bestcar137/CLionProjects/syspro/Chapters/chap08/hw02
gcc -std=c11 -Wall -Wextra -Wpedantic -o /tmp/syspro-process-relation process_relation.c
/tmp/syspro-process-relation
```

3장처럼 여러 `.c`가 한 실행 파일을 구성하는 실습은 필요한 소스를 함께 컴파일해야 합니다. 3장의 기존 `makefile`에는 현재 폴더 구성과 맞지 않는 경로가 있어 루트 CMake의 등록을 기준으로
빌드합니다. 상대 경로로 입력 파일을 읽거나 결과 파일을 만드는 실습은 해당 실습 폴더를 작업 디렉터리로 사용하고, 파일명과 실행 인자를 소스에서 확인합니다.

## 현재 구현 및 빌드 참고 사항

- CMake는 실행 대상 69개와 정적 라이브러리 2개를 등록합니다. 진입점이 없는 `chap07_hw02_lockt`와 `chap09_prob04_mysystem`은 정적 라이브러리입니다.
- 소스 오류가 기록된 `chap06_prob07_unlink`, `chap08_prob04_exit_handler`, `chap09_prob06_pgrp1`, `chap09_prob06_pgrp2`는 기본 전체
  빌드에서 제외되어 있습니다. 원인과 제외 설정은 CMake 파일 끝에 있습니다.
- `Chapters/chap09/reference/exec_placeholder/exec.c`는 주석만 있는 자리표시 파일입니다. `Chapters/chap10/reference/vars.c`도 CMake 대상에
  포함되지 않습니다.
- 9장의 학습용 셸은 Bash의 모든 기능을 구현하지 않습니다. 지원하는 문법과 제한은 9장 과제 안내에서 확인합니다.
- 일부 소스는 CP949로 저장되어 있고 나머지 다수는 UTF-8입니다. 편집할 때 기존 인코딩을 확인합니다.
- 기존 `.exe`, 확장자 없는 바이너리와 `.o` 파일은 과거 환경의 산출물입니다. 현재 환경에서는 소스로 다시 빌드합니다.

기존 과제 문서의 검증 결과는 해당 작업 당시의 기록입니다. 이번 루트 README 작성에서는 파일 구성, 소스와 CMake 등록, 문서 링크를 대조했으며 전체 실습을 새로 빌드하거나 실행하지는 않았습니다.
