#include <stdio.h>
#include <string.h>
#include "copy.h"


int main(void) {
    char line[MAXLINE];
    char arr[5][MAXLINE];
    int n = 0;

    while (n < 5 && fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0'; // 개행 제거
        copy(line, arr[n]);
        n++;
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (strlen(arr[i]) < strlen(arr[j])) {
                char tmp[MAXLINE];
                copy(arr[i], tmp);
                copy(arr[j], arr[i]);
                copy(tmp, arr[j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%s\n", arr[i]);
    }
    return 0;
}
