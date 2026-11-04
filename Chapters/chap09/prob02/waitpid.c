//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @brief Creates two children and waits specifically for the first child.
 *
 * @par Behavior
 * The first child requests a one-second sleep and exits with status 1.
 * The second requests a two-second sleep and exits with status 2.
 * After successful creation, the parent uses waitpid(pid1, &status, 0)
 * to wait only for the first child, then prints its PID and status >> 8.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 * #include <stdlib.h>
 * #include <sys/wait.h>
 *
 * pid_t fork(void);
 * pid_t getpid(void);
 * unsigned int sleep(unsigned int seconds);
 * void exit(int status);
 * pid_t waitpid(pid_t pid, int *status, int options);
 * @endcode
 *
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 * The children terminate with exit(1) and exit(2), respectively.
 *
 * @note sleep() uses seconds, not milliseconds, and may be interrupted.
 * The parent does not reap the second child in this program.
 * @warning fork() and waitpid() failures are unchecked. If the first fork()
 * fails, pid1 is -1 and waitpid() can select any child. Status decoding
 * assumes normal termination and a particular status-bit layout.
 */
/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main() {
    int pid1, pid2, child, status;

    printf("[%d] 부모 프로세스 시작 \n", getpid());
    pid1 = fork();
    if (pid1 == 0) {
        printf("[%d] 자식 프로세스 [1] 시작 \n", getpid());
        sleep(1);
        printf("[%d] 자식 프로세스 [1] 종료 \n", getpid());
        exit(1);
    }
    pid2 = fork();
    if (pid2 == 0) {
        printf("[%d] 자식 프로세스 [2] 시작 \n", getpid());
        sleep(2);
        printf("[%d] 자식 프로세스 [2] 종료 \n", getpid());
        exit(2);
    }
    // 자식 프로세스 #1의 종료를 기다린다.
    child = waitpid(pid1, &status, 0);
    printf("[%d] 자식 프로세스 #1 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
}
