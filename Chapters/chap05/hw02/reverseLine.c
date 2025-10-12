//
// Created by MinGyu on 25. 10. 12.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // read, close
#include <fcntl.h>    // open
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_COLS  256

// 좌우 공백 제거(입력 사양 보호용, 여기서는 파일 내용엔 적용하지 않음)
static void trim(char *s) {
    char *p = s;
    while (*p && isspace((unsigned char) *p)) p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    size_t n = strlen(s);
    while (n && isspace((unsigned char) s[n - 1])) s[--n] = '\0';
}

// 파일을 read()로 읽어 줄 단위로 saved[row]에 저장, 반환값=총 줄 수
static int load_lines(const char *path, char saved[][MAX_COLS]) {
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
    int long_line = 0, trunc_lines = 0;

    while ((n = read(fd, &ch, 1)) > 0) {
        if (ch == '\r') continue; // CRLF 대응
        if (ch == '\n') {
            // 줄 종료
            if (line < MAX_LINES) saved[line][col] = '\0';
            if (long_line) {
                trunc_lines++;
                long_line = 0;
            }
            col = 0;
            if (++line >= MAX_LINES) {
                // 이후 줄은 저장 불가(경고는 아래에서 출력)
            }
        } else {
            if (line < MAX_LINES) {
                if (col < MAX_COLS - 1) saved[line][col++] = ch;
                else long_line = 1; // 너무 긴 줄 → 앞부분만 저장
            }
        }
    }
    if (n < 0) {
        perror("read 실패");
        close(fd);
        return -1;
    }

    // 마지막 줄이 개행 없이 끝나는 경우
    if (col > 0) {
        if (line < MAX_LINES) saved[line][col] = '\0';
        if (long_line) {
            trunc_lines++;
            long_line = 0;
        }
        line++;
    }

    close(fd);

    if (line > MAX_LINES)
        fprintf(stderr, "알림: 줄 개수 %d가 MAX_LINES(%d)를 초과하여 일부 줄은 미보관되었습니다.\n",
                line, MAX_LINES);
    if (trunc_lines > 0)
        fprintf(stderr, "알림: 너무 긴 줄 %d개가 잘려 저장되었습니다(MAX_COLS=%d).\n",
                trunc_lines, MAX_COLS);

    return line; // 실제 줄 개수
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }

    char saved[MAX_LINES][MAX_COLS];
    int total = load_lines(argv[1], saved);
    if (total < 0) return 1;

    // **역순 출력** (마지막 줄 → 첫 줄)
    for (int i = total - 1; i >= 0; --i) {
        // 저장 한도를 넘어 미보관된 줄은 빈 문자열일 수 있음 → 그대로 줄바꿈만 출력
        printf("%s\n", saved[i]);
    }
    return 0;
}
