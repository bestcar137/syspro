//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Launches three child commands that print hello, world, and bye.
 *
 * @par Behavior
 * Attempts three forks in the original process. Each child calls execl()
 * to run /bin/echo with hello, world, or bye, respectively. If execution
 * fails, that child prints an error and exits with status 1, 2, or 3.
 * The original process prints its end message without waiting.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 * #include <stdlib.h>
 *
 * pid_t fork(void);
 * int execl(const char *path, const char *arg, ...);
 * void exit(int status);
 * @endcode
 *
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 * Successfully replaced children follow /bin/echo termination behavior.
 *
 * @note All three commands use /bin/echo, unlike the lecture example
 * that also runs date and ls. Their execution order is unspecified.
 * @warning fork() failures are unchecked. execl() requires a null-pointer
 * terminator for its variadic argument list.
 */
/* 세 개의 자식 프로세스를 생성하여 각각 다른 명령어를 실행한다. */
int main() {
    printf("부모 프로세스 시작 \n");
    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "첫 번째 실패");
        exit(1);
    }
    if (fork() == 0) {
        execl("/bin/echo", "echo", "world", NULL);
        fprintf(stderr, "두 번째 실패");
        exit(2);
    }
    if (fork() == 0) {
        execl("/bin/echo", "echo", "bye", NULL);
        fprintf(stderr, "세 번째 실패");
        exit(3);
    }
    printf("부모 프로세스 끝\n");
}
