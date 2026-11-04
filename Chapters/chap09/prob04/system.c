//
// Created by bestc on 26. 11. 4..
//

/**
 * @brief Implements a simplified synchronous shell-command runner.
 *
 * @par Behavior
 * Returns 1 immediately for a null command pointer. Otherwise, forks a child
 * that calls execl() to run /bin/sh -c cmdstring. On exec failure, the child
 * calls _exit(127). The parent waits for that child with waitpid(), retrying
 * after EINTR, and returns the encoded wait status.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 * #include <sys/wait.h>
 *
 * pid_t fork(void);
 * int execl(const char *path, const char *arg, ...);
 * void _exit(int status);
 * pid_t waitpid(pid_t pid, int *status, int options);
 * @endcode
 *
 * @param cmdstring Shell command string, or NULL for the implemented probe.
 * @return 1 for NULL; -1 if fork() fails or waitpid() fails with an error
 * other than EINTR; otherwise the encoded child wait status.
 *
 * @note A null command returns 1 without actually checking shell availability.
 * Use WIFEXITED before WEXITSTATUS to decode normal child termination.
 * This is not a complete implementation of standard system() signal behavior.
 * @warning The source currently omits required headers: <stddef.h> for NULL,
 * <unistd.h> for process APIs, <sys/wait.h> for waitpid(), and <errno.h>
 * for errno and EINTR. Prototypes shown here are documentation only.
 */
int mysystem(const char *cmdstring) {
    int pid, status;

    if (cmdstring == NULL) /* 명령어가 NULL인 경우 */
        return 1;
    pid = fork();

    if (pid == -1) /* 프로세스 생성 실패 */
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
        _exit(127); /* 명령어 실행 오류 */
    }

    do {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR) /* waitpid()로부터 EINTR 오류 외 */
                return -1;
        } else return status;
    } while (1);
}
