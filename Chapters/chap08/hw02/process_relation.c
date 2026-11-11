// 과제 2: 현재 PID, 부모 PID를 ps의 프로세스 목록과 비교한다.
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    printf("my process number : [%ld]\n", (long)getpid());
    printf("my parent's process number : [%ld]\n", (long)getppid());
    // 파일로 저장해도 앞의 두 줄이 ps보다 먼저 출력되게 한다.
    if (fflush(stdout) == EOF) { perror("fflush"); return EXIT_FAILURE; }

    int status = system("ps");
    if (status == -1) { perror("system"); return EXIT_FAILURE; }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "오류: ps 명령이 정상 종료하지 않았습니다.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
