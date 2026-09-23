//
// Created by bestc on 26. 9. 23..
//

#include <stdio.h>
#include "student.h"

/// 텍스트 파일에서 학생 정보를 읽어 프린트한다.
int main(int argc, char *argv[]) {
    struct student rec;
    FILE *fp;
    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
    while (fscanf(fp, "%d %s %d", &rec.id, rec.name, &rec.score) == 3)
        printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
    fclose(fp);
    return 0;
}
