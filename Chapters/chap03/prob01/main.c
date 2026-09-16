//
// Created by bestc on 26. 9. 16..
//

#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE]; // 입력 줄
char longest[MAXLINE]; // 가장 긴 줄
/* 입력 줄 가운데 가장 긴 줄을 프린트한다. */

int main() {
    int len;
    int max;

    max = 0;

    while (fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);

        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }

    if (max > 0)
        printf("%s \n", longest);

    return 0;
}