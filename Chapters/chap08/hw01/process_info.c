// 과제 1: 하나의 프로그램에서 실행 환경과 프로세스 정보를 조회한다.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

static void usage(const char *program) {
    fprintf(stderr, "사용법: %s -e [환경변수이름] | -u | -g | -i | -p\n", program);
    fprintf(stderr, "여러 옵션을 함께 사용할 수 있습니다. 예: -u -g -i -p\n");
}

int main(int argc, char *argv[]) {
    int result = EXIT_SUCCESS;
    if (argc < 2) { usage(argv[0]); return EXIT_FAILURE; }

    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "-e", 2) == 0) {
            const char *name = argv[i] + 2;
            // -e PATH와 -ePATH를 모두 지원한다.
            if (*name == '\0' && i + 1 < argc && argv[i + 1][0] != '-')
                name = argv[++i];
            if (*name == '\0') {
                for (char **p = environ; *p != NULL; ++p)
                    puts(*p);
            } else {
                const char *value = getenv(name);
                if (value == NULL) {
                    fprintf(stderr, "오류: 환경변수 %s가 없습니다.\n", name);
                    result = EXIT_FAILURE;
                } else printf("%s = %s\n", name, value);
            }
        } else if (strcmp(argv[i], "-u") == 0) {
            printf("실제 사용자 ID: %lu\n", (unsigned long)getuid());
            printf("유효 사용자 ID: %lu\n", (unsigned long)geteuid());
        } else if (strcmp(argv[i], "-g") == 0) {
            printf("실제 그룹 ID: %lu\n", (unsigned long)getgid());
            printf("유효 그룹 ID: %lu\n", (unsigned long)getegid());
        } else if (strcmp(argv[i], "-i") == 0) {
            printf("프로세스 ID: %ld\n", (long)getpid());
        } else if (strcmp(argv[i], "-p") == 0) {
            printf("부모 프로세스 ID: %ld\n", (long)getppid());
        } else {
            fprintf(stderr, "오류: 알 수 없는 인자 %s\n", argv[i]);
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    }
    return result;
}
