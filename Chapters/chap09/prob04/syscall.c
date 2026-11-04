//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * @brief Runs three shell commands and prints extracted exit-status fields.
 *
 * @par Behavior
 * Calls the standard system() function sequentially with date, hello,
 * and who; exit 44. Reports negative system() results with perror(),
 * but then applies WEXITSTATUS to every result, including failures.
 *
 * @par Related function prototypes
 * @code
 * #include <stdlib.h>
 *
 * int system(const char *command);
 * @endcode
 *
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 *
 * @note system() returns an encoded wait status, not a plain exit code.
 * If hello is not found, the shell normally exits with status 127.
 * The last command explicitly requests shell exit status 44.
 * @warning WEXITSTATUS is meaningful only after a successful call and
 * normal termination confirmed by WIFEXITED. The source lacks <stdlib.h>.
 * This file calls system(), not the separate mysystem() implementation.
 */
int main() {
    int status;
    if ((status = system("date")) < 0)
        perror("system() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = system("hello")) < 0)
        perror("system() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = system("who; exit 44")) < 0)
        perror("system() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));
}
