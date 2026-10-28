//
// Created by bestc on 26. 10. 28..
//

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

/**
 * @brief Process user and group IDs: real and effective identities.
 *
 * A process has user and group IDs in addition to its process ID.
 * These identities help determine which operations the process may perform.
 *
 * @par Real and effective IDs
 * - The real user ID identifies the user who originally started the process.
 * - The effective user ID is used primarily for permission checks and
 *   determining the ownership of newly created files.
 * - The real group ID identifies the process's real group.
 * - The effective group ID is used in group-based permission checks.
 * - Real and effective IDs are normally identical, but may differ when
 *   executing programs with special permission settings.
 *
 * @par Headers and function prototypes
 * @code
 * #include <sys/types.h>
 * #include <unistd.h>
 *
 * uid_t getuid(void);
 * uid_t geteuid(void);
 * gid_t getgid(void);
 * gid_t getegid(void);
 *
 * int setuid(uid_t uid);
 * int seteuid(uid_t uid);
 * int setgid(gid_t gid);
 * int setegid(gid_t gid);
 * @endcode
 *
 * @par Retrieving IDs
 * - getuid(): Returns the calling process's real user ID.
 * - geteuid(): Returns the calling process's effective user ID.
 * - getgid(): Returns the calling process's real group ID.
 * - getegid(): Returns the calling process's effective group ID.
 *
 * @par Changing IDs
 * - setuid(uid): Sets the effective user ID. With sufficient privileges,
 *   it also sets the real and saved set-user-ID.
 * - seteuid(uid): Sets the effective user ID.
 * - setgid(gid): Sets the effective group ID. With sufficient privileges,
 *   it also sets the real and saved set-group-ID.
 * - setegid(gid): Sets the effective group ID.
 *
 * @par Parameters
 * - uid: The requested user ID.
 * - gid: The requested group ID.
 *
 * @par Return values
 * The get functions return the corresponding user or group ID.
 * The set functions return 0 on success, or -1 on failure and set errno.
 *
 * @note uid_t and gid_t are integer types used to represent user and group IDs.
 *
 * @warning ID changes are subject to permission restrictions.
 * Always check the return value of an ID-changing function.
 */
/* 사용자 ID를 출력한다. */
int main() {
    printf("나의 실제 사용자 ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
    printf("나의 유효 사용자 ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
    printf("나의 실제 그룹 ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
    printf("나의 유효 그룹 ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
}
