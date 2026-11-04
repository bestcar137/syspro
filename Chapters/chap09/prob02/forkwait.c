//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @brief Creates a child and waits for its termination.
 *
 * @par Behavior
 * The child prints its PID and terminates with exit(1). The original process
 * calls wait(&status), prints its result, and prints status shifted right
 * by eight bits as the demonstrated exit-code extraction.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 * #include <sys/wait.h>
 * #include <stdlib.h>
 *
 * pid_t fork(void);
 * pid_t getpid(void);
 * pid_t wait(int *status);
 * pid_t waitpid(pid_t pid, int *statloc, int options);
 * void exit(int status);
 * @endcode
 *
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 * The child terminates with exit(1).
 *
 * @warning fork() and wait() failures are unchecked. If wait() fails, status
 * is not valid for decoding. Portable code checks WIFEXITED before using
 * WEXITSTATUS instead of assuming a status-bit layout.
 * @warning The source calls exit() without including <stdlib.h>.
 */
/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main() {
    int pid, child, status;
    printf("[%d] 부모 프로세스 시작 \n", getpid());
    pid = fork();
    if (pid == 0) {
        printf("[%d] 자식 프로세스 시작 \n", getpid());
        exit(1);
    }
    child = wait(&status); // 자식 프로세스가 끝나기를 기다린다.
    printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
}
