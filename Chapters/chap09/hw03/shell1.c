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

/* 인용부호/이스케이프 없이 단어와 ; & < >를 분리하는 간단한 분석기. */
static int tokenize(char *line, char **tokens, char *types) {
    int count = 0;
    char *p = line;
    while (*p) {
        if (strchr(" \t\r\n", *p)) { ++p; continue; }
        if (count == MAXARG - 1) return -1;
        if (strchr(";&<>", *p)) {
            types[count] = *p++;
            tokens[count++] = NULL;
        } else {
            types[count] = 'w';
            tokens[count++] = p;
            while (*p && !strchr(" \t\r\n;&<>", *p)) {
                if (strchr("|\"'\\", *p)) return -1;
                ++p;
            }
            if (*p) {
                char separator = *p;
                *p++ = '\0';
                if (strchr(";&<>", separator)) {
                    if (count == MAXARG - 1) return -1;
                    types[count] = separator;
                    tokens[count++] = NULL;
                }
            }
        }
    }
    return count;
}

static int process_line(char *line) {
    char *tokens[MAXARG], types[MAXARG];
    int count = tokenize(line, tokens, types);
    if (count < 0) {
        fprintf(stderr, "구문 오류: 입력이 너무 길거나 지원하지 않는 문법입니다.\n");
        return 0;
    }
    int i = 0;
    while (i < count) {
        char *args[MAXARG], *input = NULL, *output = NULL;
        int argc = 0, background = 0;
        while (i < count && types[i] != ';' && types[i] != '&') {
            if (types[i] == '<' || types[i] == '>') {
                char type = types[i++];
                if (i == count || types[i] != 'w') goto syntax_error;
                if (type == '<') {
                    if (input) goto syntax_error;
                    input = tokens[i++];
                } else {
                    if (output) goto syntax_error;
                    output = tokens[i++];
                }
            } else args[argc++] = tokens[i++];
        }
        if (argc == 0) goto syntax_error;
        args[argc] = NULL;
        if (i < count) background = types[i++] == '&';
        if (strcmp(args[0], "exit") == 0) {
            if (argc != 1 || background || input || output) goto syntax_error;
            return 1;
        }
        execute(args, background, input, output);
        reap_background();
    }
    return 0;
syntax_error:
    fprintf(stderr, "구문 오류: 명령어, 구분자 또는 리디렉션 파일명을 확인하세요.\n");
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
        if (interactive) { printf("[shell] "); fflush(stdout); }
        if (getline(&line, &capacity, stdin) == -1) break;
        if (process_line(line)) break;
    }
    free(line);
    reap_background();
    return 0;
}
