#include <stdio.h>
#include <string.h>
#include "copy.h"

/*
 * 요구사항:
 * - 문장 5개를 입력받아
 * - 문자열 길이가 긴 순서대로 정렬하여 출력
 * - 문자열 복사/교환은 제공된 copy()만 사용
 * - 안전한 입력을 위해 fgets 사용 (개행 문자 제거)
 */
int main(void) {
    char line[MAXLINE];
    char arr[5][MAXLINE];
    int n = 0;

    /* 입력: 최대 5줄 */
    while (n < 5 && fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0'; // 개행 제거
        copy(line, arr[n]);
        n++;
    }

    /* 길이 내림차순 정렬 (단순 버블 정렬) */
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

    /* 출력 */
    for (int i = 0; i < n; ++i) {
        printf("%s\n", arr[i]);
    }
    return 0;
}
