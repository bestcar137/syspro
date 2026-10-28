//
// Created by bestc on 26. 10. 28..
//

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief atexit(): Registers an exit handler to run at normal program termination.
 *
 * @par Header and function prototype
 * @code
 * #include <stdlib.h>
 * int atexit(void (*func)(void));
 * // Returns: 0 on success, nonzero on failure.
 * @endcode
 *
 * @par Parameters
 * func: A pointer to the function to call at program termination.
 * The function must take no arguments and return void.
 *
 * @par Return value
 * Returns 0 if registration succeeds, or a nonzero value if registration fails.
 *
 * @par Invocation timing and order
 * Registered exit handlers run at normal program termination through
 * a call to exit() or a return from main().
 * They are called in the reverse order of their registration.
 * Example: Register A → register B → execute B → execute A at termination.
 *
 * @note Support for registering at least 32 exit handlers is guaranteed.
 * The actual registration limit may vary by implementation.
 */`

static void exit_handler1(void),
        exit_handler2(void);

int main(void) {
    if (atexit(exit_handler1) != 0)
        perror("exit_handler1 등록할 수 없음.");
    if (atexit(exit_handler2) != 0)
        perror("exit_handler2 등록할 수 없음.");
    printf("main 끝\n");
    exit(0);
}

static void exit_handler1(void) {
    printf("첫 번째 exit 처리기\n");
}

static void exit_handler2(void) {
    printf("두 번째 exit 처리기\n");
}

// $ atexit
// main 끝
// 두 번째 exit 처리기
// 첫 번째 exit 처리기