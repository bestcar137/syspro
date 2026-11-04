//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <unistd.h>

/**
 * @brief Shows that a child inherits its parent process group.
 *
 * @par Behavior
 * Prints the original process PID and process-group ID, then calls fork().
 * On success, the child prints its own PID and inherited process-group ID.
 * getpgrp() queries membership; it does not create or change a group.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 *
 * pid_t fork(void);
 * pid_t getpid(void);
 * pid_t getpgrp(void);
 * @endcode
 *
 * @note A process-group ID (PGID) is distinct from a user group ID.
 * The parent does not wait for the child.
 * @warning fork() failure is unchecked. main() has no explicit return type;
 * this legacy implicit-int form is not valid in C99 and later.
 * The output strings contain a literal n rather than a newline escape.
 */
main() {
    int pid, gid;
    printf("RARENT: PID = %d GID = %dn", getpid(), getpgrp());
    pid = fork();
    if (pid == 0) {     // 자식 프로세스
        printf("CHILD: PID = %d GID = %dn", getpid(), getpgrp());
    }
}