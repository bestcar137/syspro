//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <unistd.h>

/**
 * @brief Creates a child process and prints process IDs and fork() results.
 *
 * @par Behavior
 * Prints the current PID, calls fork(), and prints the PID and fork() result
 * in each process that continues. On success, the parent receives the child PID
 * and the child receives 0. On failure, the original process receives -1.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 *
 * pid_t fork(void);
 * pid_t getpid(void);
 * @endcode
 *
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 *
 * @note Parent and child execution order is not guaranteed. Buffered output
 * written before fork() may be duplicated when stdout is redirected.
 * @warning fork() failure is printed but not explicitly handled.
 */
/* 자식 프로세스를 생성한다. */
int main() {
    int pid;
    printf("[%d] 프로세스 시작\n", getpid());
    pid = fork();
    printf("[%d] 프로세스 리턴값 %d\n", getpid(), pid);
}