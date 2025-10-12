//
// Created by MinGyu on 25. 10. 12.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // read, close
#include <fcntl.h>      // open
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_LINES 100
#define MAX_COLS  256

static void trim(char *s) {
    char *p = s;
    while (*p && isspace((unsigned char) *p)) p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    size_t n = strlen(s);
    while (n && isspace((unsigned char) s[n - 1])) s[--n] = '\0';
}

static int is_posint(const char *s) {
    if (!*s) return 0;
    for (const unsigned char *p = (const unsigned char *) s; *p; ++p)
        if (!isdigit(*p)) return 0;
    return 1;
}

static int clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static int load_lines(const char *path, char saved[][MAX_COLS], int *trunc_lines) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("파일 열기 오류");
        return -1;
    }

    // 초기화
    for (int i = 0; i < MAX_LINES; ++i) saved[i][0] = '\0';

    int line = 0, col = 0;
    ssize_t n;
    char ch;
    int long_line = 0; // 현재 줄이 너무 길어 잘리는 중인지
    *trunc_lines = 0;

    while ((n = read(fd, &ch, 1)) > 0) {
        if (ch == '\r') continue; // CRLF 대응
        if (ch == '\n') {
            if (line < MAX_LINES) {
                saved[line][col] = '\0';
            }
            if (long_line) {
                (*trunc_lines)++;
                long_line = 0;
            }
            col = 0;
            if (++line >= MAX_LINES) {
                // 저장 한도 도달. 이후 줄은 읽기만 계속(경고용)하지만 저장은 불가
            }
        } else {
            if (line < MAX_LINES) {
                if (col < MAX_COLS - 1) {
                    saved[line][col++] = ch;
                } else {
                    long_line = 1; // 남은 문자는 버림
                }
            }
        }
    }

    if (n < 0) {
        perror("read 실패");
        close(fd);
        return -1;
    }

    // 파일이 개행 없이 끝난 마지막 줄 처리
    if (col > 0) {
        if (line < MAX_LINES) saved[line][col] = '\0';
        if (long_line) {
            (*trunc_lines)++;
            long_line = 0;
        }
        line++;
    }

    close(fd);
    return line; // 총 줄 수(저장 여부와 무관한 실제 줄 개수)
}

static void print_one(int idx, char saved[][MAX_COLS], int total) {
    if (idx >= 1 && idx <= total) {
        // 저장 한도를 초과한 줄은 빈 문자열일 수 있음. 그 경우 안내.
        if (saved[idx - 1][0] == '\0') {
            printf("%d\t[저장 한도 초과로 내용 미보관]\n", idx);
        } else {
            printf("%d\t%s\n", idx, saved[idx - 1]);
        }
    } else {
        fprintf(stderr, "경고: %d는 유효한 줄 번호가 아닙니다(1~%d).\n", idx, total);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s test.txt\n", argv[0]);
        return 1;
    }

    char saved[MAX_LINES][MAX_COLS];
    int trunc_lines = 0;
    int total = load_lines(argv[1], saved, &trunc_lines);
    if (total < 0) return 1;

    if (total > MAX_LINES)
        fprintf(stderr, "알림: 줄 개수 %d가 MAX_LINES(%d)를 초과하여 일부 줄은 미보관되었습니다.\n",
                total, MAX_LINES);
    if (trunc_lines > 0)
        fprintf(stderr, "알림: 너무 긴 줄 %d개가 잘려 저장되었습니다(MAX_COLS=%d).\n",
                trunc_lines, MAX_COLS);

    printf("원하는 줄 번호를 입력하세요 (예: 3 | 1,3,5 | 2-4 | * ): ");
    char spec[256];
    if (!fgets(spec, sizeof(spec), stdin)) {
        fprintf(stderr, "입력 오류\n");
        return 1;
    }
    trim(spec);

    // 전체 출력
    if (strcmp(spec, "*") == 0) {
        // 중복방지(전체 출력은 중복 의미 없음)
        for (int i = 1; i <= total; ++i) print_one(i, saved, total);
        return 0;
    }

    // 토큰별 처리(리스트/범위 혼합 지원), 중복 방지
    char buf[256];
    strncpy(buf, spec, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    int printed[MAX_LINES + 1] = {0};

    for (char *tok = strtok(buf, ","); tok; tok = strtok(NULL, ",")) {
        trim(tok);
        if (!*tok) {
            fprintf(stderr, "경고: 빈 토큰 무시\n");
            continue;
        }

        char *dash = strchr(tok, '-');
        if (dash) {
            *dash = '\0';
            char *L = tok, *R = dash + 1;
            trim(L);
            trim(R);
            if (!is_posint(L) || !is_posint(R)) {
                fprintf(stderr, "경고: 범위 '%s-%s'는 올바른 양의 정수가 아닙니다.\n", L, R);
                continue;
            }
            int a = atoi(L), b = atoi(R);
            if (a == 0 || b == 0) {
                fprintf(stderr, "경고: 0은 유효한 줄 번호가 아닙니다.\n");
                continue;
            }
            if (a <= b) {
                for (int i = a; i <= b; ++i) {
                    int x = clamp(i, 1, total);
                    if (!printed[x]) {
                        print_one(x, saved, total);
                        printed[x] = 1;
                    }
                }
            } else {
                for (int i = a; i >= b; --i) {
                    int x = clamp(i, 1, total);
                    if (!printed[x]) {
                        print_one(x, saved, total);
                        printed[x] = 1;
                    }
                }
            }
        } else {
            if (!is_posint(tok)) {
                fprintf(stderr, "경고: '%s'는 양의 정수가 아닙니다.\n", tok);
                continue;
            }
            int n = atoi(tok);
            if (n == 0) {
                fprintf(stderr, "경고: 0은 유효한 줄 번호가 아닙니다.\n");
                continue;
            }
            n = clamp(n, 1, total);
            if (!printed[n]) {
                print_one(n, saved, total);
                printed[n] = 1;
            }
        }
    }
    return 0;
}
