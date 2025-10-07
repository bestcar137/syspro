//
// Created by bestc on 25. 9. 30..
//

#include <stdio.h>
#include <string.h>

/// 실습 1번 cat 프로그램을 기반으로 확장하시오.
/// 확장 사항 1: 명령어 인수로 여러 개의 파일을 받으면 순차적으로 파일 내용 출력
/// 확장 사항 2: -n 옵션은 파일 내용을 줄 번호와 함께 출력
int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    // -n 옵션이 존재하는 경우 처리 케이스. gpt 도움 받음
    // 1) -n 존재 여부만 먼저 검사
    int has_n = 0;
    for (int i = 1; i < argc; ++i)
        if (strcmp(argv[i], "-n") == 0) {
            has_n = 1;
            break;
        }

    // 2) -n 전용 경로: 줄번호 출력
    if (has_n) {
        int line = 1, at_start = 1;

        // 파일 인자가 없는 경우(-n만 있거나 파이프 입력)
        int file_exists = 0;
        for (int i = 1; i < argc; ++i)
            if (strcmp(argv[i], "-n") != 0) {
                file_exists = 1;
                break;
            }

        if (!file_exists) {
            fp = stdin;
            while ((c = getc(fp)) != EOF) {
                if (at_start) {
                    printf("%6d\t", line++);
                    at_start = 0;
                }
                putc(c, stdout);
                if (c == '\n') at_start = 1;
            }
            return 0;
        }

        // -n이 있을 때만 별도 처리, 파일들은 순서대로 출력(-n은 건너뜀)
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-n") == 0) continue;

            if (strcmp(argv[i], "-") == 0) fp = stdin;
            else {
                fp = fopen(argv[i], "r");
                if (!fp) {
                    perror(argv[i]);
                    continue;
                }
            }

            while ((c = getc(fp)) != EOF) {
                if (at_start) {
                    printf("%6d\t", line++);
                    at_start = 0;
                }
                putc(c, stdout);
                if (c == '\n') at_start = 1;
            }
            if (fp != stdin) fclose(fp);
        }
        return 0;
    }

    if (argc < 2) {
        fp = stdin;
        while ((c = getc(fp)) != EOF) putc(c, stdout);
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-") == 0) fp = stdin;
        else {
            fp = fopen(argv[i], "r");
            if (!fp) {
                perror(argv[i]);
                continue;
            }
        }
        while ((c = getc(fp)) != EOF)
            putc(c, stdout);

        if (fp != stdin)
            fclose(fp);
    }
    return 0;
}
