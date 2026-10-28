//
// Created by bestc on 26. 10. 28..
//
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Outputs all environment variables to the standard output.
 *
 * @par Behavior
 * Iterates through the process's environment using the global variable `environ`.
 * Each environment variable is printed in the format "KEY=VALUE".
 * The function terminates after all environment variables have been output.
 *
 * @note This function relies on the external global variable `environ`.
 * Make sure the environment is properly initialized before invocation.
 *
 * @par Related function prototypes
 * @code
 * extern char **environ;
 * @endcode
 *
 */
/* 모든 환경 변수를 출력한다. */
int main(int argc, char *argv[]) {
    char **ptr;
    extern char **environ;

    for (ptr = environ; *ptr != 0; ptr++)   /* 모든 환경 변수 값 출력 */
        printf("%s \n", *ptr);
    exit(0);
}
