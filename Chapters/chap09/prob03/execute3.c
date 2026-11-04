//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Runs a command supplied on the command line in a child process.
 *
 * @par Behavior
 * The child calls execvp(argv[1], &argv[1]), allowing PATH lookup when
 * the command has no slash. On exec failure, it prints an error and reaches
 * the end of main(). The other branch calls wait() and prints status >> 8.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 * #include <sys/wait.h>
 *
 * pid_t fork(void);
 * int execvp(const char *file, char *const argv[]);
 * pid_t wait(int *status);
 * pid_t getpid(void);
 * @endcode
 *
 * @param argc Argument count; not checked or otherwise used.
 * @param argv Argument vector; argv[1] is the command and later entries
 * are its arguments.
 * @pre At least one command argument must be supplied (argc >= 2).
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 * Successful execvp() replaces the child and does not return.
 *
 * @warning Missing arguments, fork() failure, and wait() failure are unchecked.
 * Exec failure in the child still leads to an implicit return of 0.
 * The child PID passed to printf() has no corresponding format conversion.
 * Status decoding assumes normal termination and a particular bit layout.
 * The source lacks <sys/wait.h>, which declares wait().
 */
/* 명령줄 인수로 받은 명령을 실행시킨다. */
int main(int argc, char *argv[]) {
    int child, pid, status;
    pid = fork();
    if (pid == 0) {     // 자식 프로세스
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s 실행 불가\n", argv[1]);
    } else {            // 부모 프로세스
        child = wait(&status);
        printf("[%d] 자식 프로세스 종료\n", getpid(), pid);
        printf("\t종료 코드 %d \n", status >> 8);
    }
}
