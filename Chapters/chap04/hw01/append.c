/** 프로그램 7.2는 rdlock.c으로 레코드에 대한 내용이라 교재의 프로그램 5.3: copy.c를 참고함
//
// Created by bestc on 25. 9. 30..
//

* copy.c
#include <stdio.h>
//파일 복사 프로그램

int main(int argc, char *argv[]) {
    char c;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "How to use: %s File1 File2\n", argv[0]);
        return 1;
    }
    fp1 = fopen(argv[1], "r");

    if (fp1 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[1]);
        return 2;
    }
    fp2 = fopen(argv[2], "w");

    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
*/

#include <stdio.h>
/* append 프로그램: file1.txt의 내용을 file2.txt 뒤에 덧붙인다. */

int main(int argc, char *argv[]) {
    int c;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "How to use: %s File1 File2\n", argv[0]);
        return 1;
    }
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[1]);
        return 2;
    }

    fp2 = fopen(argv[2], "a");  // Mode: append
    if (fp2 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[2]);
        fclose(fp1);
        return 3;
    }

    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);

    fclose(fp1);
    fclose(fp2);
    return 0;
}
