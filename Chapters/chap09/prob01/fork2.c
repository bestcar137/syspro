//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <unistd.h>


/**
 * @brief Prints different greetings in the parent and child processes.
 *
 * @par Behavior
 * Calls fork() once. A zero result selects the child greeting; every other
 * result selects the parent greeting. Each greeting includes the current PID.
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
 * @note The parent does not wait for the child; output order is unspecified.
 * @warning A fork() failure also enters the parent branch.
 */
/* 부모 프로세스가 자식 프로세스를 생성하고 서로 다른 메시지를 프린트 */
int main() {
    int pid;
    pid = fork();
    if (pid == 0) {     // 자식 프로세스
        printf("[Child] Hello, world pid=%d\n", getpid());
    }
    else {              // 부모 프로세스
        printf("[Parent] Hello, world pid=%d\n", getpid());
    }
}
