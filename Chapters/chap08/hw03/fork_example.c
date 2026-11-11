// 과제 3: fork 전에는 부모만, fork 후 조건문에서는 자식만 출력한다.
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    printf("[1] =%ld\n", (long)getpid());
    // fork 시 미출력 버퍼가 복제되어 [1]이 중복 출력되는 것을 방지한다.
    if (fflush(stdout) == EOF) { perror("fflush"); return EXIT_FAILURE; }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return EXIT_FAILURE; }
    if (pid == 0)
        printf("[2] = %ld, %ld\n", (long)getpid(), (long)getppid());

    sleep(1); // PDF와 같이 부모와 자식 모두 실행한다.

    // 부모가 자식보다 먼저 종료하지 않도록 자식을 기다리고 회수한다.
    if (pid > 0) {
        while (waitpid(pid, NULL, 0) == -1) {
            if (errno != EINTR) { perror("waitpid"); return EXIT_FAILURE; }
        }
    }
    return EXIT_SUCCESS;
}
