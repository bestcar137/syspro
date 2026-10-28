//
// Created by bestc on 26. 10. 28..
//
#include <stdio.h>
#include <unistd.h>


/**
 * @brief Displays the process ID of the current process and its parent process.
 *
 * This function retrieves and prints the current process ID and the parent process ID
 * using system calls. It demonstrates the use of process-related APIs in C.
 *
 * @par Behavior
 * - Calls the `getpid()` function to retrieve the process ID of the running program.
 * - Calls the `getppid()` function to retrieve the process ID of the parent process.
 * - Prints both IDs using formatted output.
 *
 * @par Related function prototypes
 * @code
 * #include <unistd.h>
 * pid_t getpid(void);
 * pid_t getppid(void);
 * @endcode
 *
 * @return Returns 0 implicitly if the end of the main function is reached (starting with C99).
 */
int main() {
    printf("나의 프로세스 번호 : [%d]\n", getpid());
    printf("부모 프로세스 번호 : [%d]\n", getppid());
}

// $ pid
// 나의 프로세스 번호 : [pid]
// 부모 프로세스 번호 : [ppid]