//
// Created by bestc on 25. 9. 30..
//

#include <stdio.h>
/* 텍스트 파일 내용을 표준출력에 출력 */

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    if (argc < 2)
        fp = stdin;
    else fp = fopen(argv[1], "r");

    c = getc(fp);
    while (c != EOF) {
        putc(c, stdout);
        c = getc(fp);
    }
    fclose(fp);
    return 0;
}
