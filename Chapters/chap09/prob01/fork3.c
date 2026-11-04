//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Attempts to create two children that print separate greetings.
 *
 * @par Behavior
 * The first child prints its PID and calls exit(0) before the second fork().
 * The original process then attempts a second fork(). The second child prints
 * its PID and calls exit(0); the original process prints the parent greeting.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 * #include <stdlib.h>
 *
 * pid_t fork(void);
 * pid_t getpid(void);
 * void exit(int status);
 * @endcode
 *
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 * Child branches terminate with exit(0) instead of returning.
 *
 * @note With successful forks, exactly two children are created. The parent
 * does not wait for them, and output order is unspecified.
 * @warning fork() failures are unchecked. The source calls exit() without
 * including its required <stdlib.h> declaration.
 */
/* 부모 프로세스가 두 개의 자식 프로세스를 생성한다. */
int main() {
    int pid1, pid2;
    pid1 = fork();
    if (pid1 == 0 ) {
        printf("[Child 1] Hello, world ! pid=%d\n", getpid());
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0) {
        printf("[Child 2] Hello, world ! pid=%d\n", getpid());
        exit(0);
    }
    printf("[Parent] Hello, world ! pid=%d\n", getpid());
}