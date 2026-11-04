//
// Created by bestc on 26. 11. 4..
//

#include <complex.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Runs a command in a child with stdout redirected to a file.
 *
 * @par Behavior
 * The child opens argv[1] using O_CREAT | O_TRUNC | O_WRONLY and mode 0600,
 * duplicates that descriptor onto stdout, closes it, and calls
 * execvp(argv[2], &argv[2]). On exec failure, it prints a diagnostic using
 * the output filename and reaches the end of main(). The other branch
 * waits for a child and prints a termination message.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 * #include <fcntl.h>
 * #include <sys/wait.h>
 *
 * pid_t fork(void);
 * int open(const char *path, int flags, ...);
 * int dup2(int oldfd, int newfd);
 * int close(int fd);
 * int execvp(const char *file, char *const argv[]);
 * pid_t wait(int *status);
 * @endcode
 *
 * @param argc Argument count; not checked or otherwise used.
 * @param argv Argument vector: argv[1] is the output file, argv[2] is the
 * command, and later entries are command arguments.
 * @pre Supply both an output filename and a command (argc >= 3).
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 * A successful execvp() replaces the child and does not return.
 *
 * @note On successful redirection, stderr keeps its inherited destination.
 * File creation permissions are filtered by umask.
 * @warning Arguments and fork(), open(), dup2(), close(), and wait() results
 * are unchecked. Exec failure still leads to an implicit return of 0.
 * The diagnostic names argv[1], not the command in argv[2]. The child PID
 * passed to printf() has no corresponding format conversion. Closing fd
 * after dup2() assumes it differs from descriptor 1.
 */
/* 자식 프로세스의 표준 출력을 파일에 재지정한다. */
int main(int argc, char *argv[]) {
    int child, pid, fd, status;

    pid = fork();
    if (pid == 0) {
        fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
        dup2(fd, 1); // 파일을 표준출력에 복제
        close(fd);
        execvp(argv[2], &argv[2]);
        fprintf(stderr, "%s실행 불가\n", argv[1]);
    } else {
        child = wait(&status);
        printf("[%d] 자식 프로세스  %d 종료\n", getpid(), child);
    }
}
