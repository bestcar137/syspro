//
// Created by bestc on 26. 10. 28..
//
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Entry point for the program.
 *
 * The main function serves as the starting point of program execution.
 * It typically handles initial setup, program logic flow, and clean termination.
 * In C99 and later, reaching the closing brace of main() implicitly returns 0.
 *
 * @param argc The number of command-line arguments passed to the program, including the program name.
 * @param argv An array of pointers to the command-line arguments, with argv[0] being the program name.
 *             If no arguments are passed, argc is 1, and argv[0] contains the program name.
 * @return Returns 0 to indicate successful execution. Non-zero values may signal an error or specific status.
 *
 * @par Behavior
 * When the program is executed, the operating system provides command-line arguments in the form of argc
 * and argv. These values can be used to influence the program's behavior or pass information at runtime.
 * @note 모든 명령줄 인수를 출력한다.
 */

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) /* 모든 명령줄 인수를 출력. */
        printf("argv[%d]: %s \n", i, argv[i]);
    exit(0);
}

// $ args hello world
// argv[0]: args
// argv[1]: hello
// argv[2]: world
