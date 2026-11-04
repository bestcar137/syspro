//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Runs /bin/echo with the argument hello in a child process.
 *
 * @par Behavior
 * Prints a start message and attempts fork(). The child uses execl() to
 * replace its program with /bin/echo. If execl() returns, it prints an error
 * and calls exit(1). The original process prints an end message without waiting.
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
 * A successful execl() does not return; failure in the child leads to exit(1).
 *
 * @note Parent and child output order is not guaranteed. The variadic
 * execl() argument list must end with a null pointer.
 * @warning fork() failure is not checked.
 */
/* 자식 프로세스를 생성하여 echo 명령어를 실행한다. */
int main() {
    printf("부모 프로세스 시작 \n");
    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "첫 번째 실패");
        exit(1);
    }
    printf("부모 프로세스 끝\n");
}
