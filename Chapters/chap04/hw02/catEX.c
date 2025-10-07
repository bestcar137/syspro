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

    if (argc < 2) {
        fp = stdin;
        while ((c = getc(fp)) != EOF) putc(c, stdout);
        return 0;
    }

    // 인수로 받은 파일들을 앞에서부터 차례로 처리
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-") == 0) fp = stdin;
        else {
            fp = fopen(argv[i], "r");
            if (!fp) {
                perror(argv[i]);
                continue;
            }
        }
        // 문자 단위로 읽어 그대로 출력
        while ((c = getc(fp)) != EOF)
            putc(c, stdout);

        if (fp != stdin)
            fclose(fp);
    }
    return 0;
}
