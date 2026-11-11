#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXARG 128

/* 다음 명령을 받기 전에 종료한 후면 자식을 회수한다. */
static void reap_background(void) {
    while (waitpid(-1, NULL, WNOHANG) > 0) {}
}

static int redirect_fd(const char *path, int target, int flags) {
    int fd = open(path, flags, 0666);
    if (fd == -1) { perror(path); return -1; }
    if (dup2(fd, target) == -1) {
        perror("dup2");
        close(fd);
        return -1;
    }
    if (fd != target) close(fd);
    return 0;
}

static void execute(char **args, int background,
                    const char *input, const char *output) {
    fflush(NULL);
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return; }
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (background) {
            if (setpgid(0, 0) == -1) { perror("setpgid"); _exit(1); }
            /* 후면 명령이 쉘의 입력을 가져가지 않도록 한다. */
            if (input == NULL) input = "/dev/null";
        }
        if (input && redirect_fd(input, STDIN_FILENO, O_RDONLY) == -1)
            _exit(1);
        if (output && redirect_fd(output, STDOUT_FILENO,
                                  O_WRONLY | O_CREAT | O_TRUNC) == -1)
            _exit(1);
        execvp(args[0], args);
        perror(args[0]);
        _exit(127);
    }
    if (background) {
        printf("[background] %ld\n", (long)pid);
        fflush(stdout);
    } else {
        /* 다른 후면 자식이 먼저 끝나도 전면 자식만 기다린다. */
        while (waitpid(pid, NULL, 0) == -1) {
            if (errno != EINTR) { perror("waitpid"); break; }
        }
    }
}

static int process_line(char *line) {
    char *args[MAXARG];
    char *save = NULL;
    int argc = 0, background = 0;
    size_t length = strlen(line);
    while (length && strchr(" \t\r\n", line[length - 1])) line[--length] = '\0';
    if (length && line[length - 1] == '&') {
        background = 1;
        line[--length] = '\0';
    }
    if (strpbrk(line, ";&<>|\"'\\")) {
        fprintf(stderr, "구문 오류: 이 과제는 명령어와 끝의 &만 지원합니다.\n");
        return 0;
    }
    /* 과제에서 지정한 strtok_r()와 args[MAXARG]를 사용한다. */
    for (char *token = strtok_r(line, " \t\r\n", &save); token;
         token = strtok_r(NULL, " \t\r\n", &save)) {
        if (argc == MAXARG - 1) {
            fprintf(stderr, "오류: 명령줄 인수가 너무 많습니다.\n");
            return 0;
        }
        args[argc++] = token;
    }
    if (argc == 0) {
        if (background) fprintf(stderr, "구문 오류: 명령어가 없습니다.\n");
        return 0;
    }
    args[argc] = NULL;
    if (strcmp(args[0], "exit") == 0) {
        if (argc == 1 && !background) return 1;
        fprintf(stderr, "사용법: exit\n");
        return 0;
    }
    execute(args, background, NULL, NULL);
    return 0;
}

int main(void) {
    char *line = NULL;
    size_t capacity = 0;
    int interactive = isatty(STDIN_FILENO);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    /* 파이프로 입력받아도 자식이 읽을 입력을 미리 버퍼링하지 않는다. */
    setvbuf(stdin, NULL, _IONBF, 0);
    for (;;) {
        reap_background();
        if (interactive) { printf("[Shell] "); fflush(stdout); }
        if (getline(&line, &capacity, stdin) == -1) break;
        if (process_line(line)) break;
    }
    free(line);
    reap_background();
    return 0;
}
