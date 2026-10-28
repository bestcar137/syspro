//
// Created by bestc on 26. 10. 28..
//

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Entry point of the program that retrieves and prints specific environment variables.
 *
 * This function accesses the environment variables "HOME", "SHELL", and "PATH" using the `getenv()`
 * function and prints their values. The program terminates explicitly using `exit(0)`.
 *
 * @par Behavior
 * The program performs the following steps:
 * - It retrieves the value of the "HOME" environment variable using `getenv()` and prints it.
 * - It retrieves the value of the "SHELL" environment variable using `getenv()` and prints it.
 * - It retrieves the value of the "PATH" environment variable using `getenv()` and prints it.
 * - The program terminates with a status of 0 using `exit(0)`.
 *
 * @param argc The number of command-line arguments passed to the program. Unused.
 * @param argv Array of command-line argument strings. Unused.
 *
 * @return Implicitly returns 0 when the program reaches its closing brace in C99 and later.
 *
 * @par Related function prototypes
 * @code
 * #include <stdlib.h>
 * #include <stdio.h>
 * char *getenv(const char *name);
 * void exit(int status);
 * @endcode
 */
/* 환경 변수 3개를 프린트한다. */
int main(int argc, char *argv[]) {
    char *ptr;

    ptr = getenv("HOME");
    printf("HOME = %s \n", ptr);

    ptr = getenv("SHELL");
    printf("SHELL = %s \n", ptr);

    ptr = getenv("PATH");
    printf("PATH = %s \n", ptr);

    exit(0);
}
