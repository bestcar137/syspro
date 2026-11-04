//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
pid_t getpgrp(void);

/**
 * @brief Attempts to put a child into its own process group.
 *
 * @par Behavior
 * Prints the original process PID and PGID, then calls fork(). In the child,
 * setpgid(0, 0) requests a group whose ID equals the child PID. The child
 * then prints its PID and current PGID, whether or not setpgid() succeeded.
 *
 * @par Related function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 *
 * pid_t fork(void);
 * pid_t getpid(void);
 * pid_t getpgrp(void);
 * int setpgid(pid_t pid, pid_t pgid);
 * @endcode
 *
 * @note On successful setpgid(), the child becomes a process-group leader
 * and belongs to a different group from its parent. The parent does not wait.
 * @warning fork() and setpgid() failures are unchecked. main() has no explicit
 * return type; this legacy implicit-int form is not valid in C99 and later.
 * The output strings contain a literal n rather than a newline escape.
 */
main() {
    int pid, gid;
    printf("RARENT: PID = %d GID = %dn", getpid(), getpgrp());
    pid = fork();
    if (pid ==0) {
        setpgid(0, 0);
        printf("CHILD: PID = %d GID = %dn", getpid(), getpgrp());
    }
}