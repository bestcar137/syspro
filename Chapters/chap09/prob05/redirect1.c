//
// Created by bestc on 26. 11. 4..
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Redirects standard output to a file while leaving stderr unchanged.
 *
 * @par Behavior
 * Opens argv[1] for writing with O_CREAT | O_TRUNC and creation mode 0600.
 * Calls dup2(fd, 1), closes fd, and writes separate messages to stdout
 * and stderr. With successful redirection, only the stdout message goes
 * to the file; stderr retains its inherited destination.
 *
 * @par Related function prototypes
 * @code
 * #include <fcntl.h>
 * #include <unistd.h>
 *
 * int open(const char *path, int flags, ...);
 * int dup2(int oldfd, int newfd);
 * int close(int fd);
 * @endcode
 *
 * @param argc Argument count; not checked or otherwise used.
 * @param argv Argument vector; argv[1] names the output file.
 * @pre Supply an output filename (argc >= 2).
 * @return Returns 0 when execution reaches the end of main() in C99 or later.
 *
 * @note Creation permissions are filtered by umask. Existing files are
 * truncated; their existing permissions are not replaced by the mode argument.
 * @warning Argument count and open(), dup2(), and close() results are unchecked.
 * Closing fd after dup2() assumes fd is different from descriptor 1.
 */
/* 표준출력을 파일에 재지정하는 프로그램 */
int main(int argc, char *argv[]) {
    int fd, status;
    fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
    dup2(fd, 1); /* 파일을 표준출력에 복제 */
    close(fd);
    printf("Hello stdout !\n");
    fprintf(stderr, "Hello stderr !\n");
}
