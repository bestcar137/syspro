//
// Created by bestc on 26. 10. 14..
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int locks(int fd, int type, off_t offset, int whence, off_t len);

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }

    printf("쓰기 잠금을 요청합니다.\n");
    fflush(stdout);

    if (locks(fd, F_WRLCK, 0, SEEK_SET, 0) == -1) {
        perror("locks");
        close(fd);
        return 1;
    }

    printf("잠금 성공! Enter를 누르면 프로그램이 종료되고 잠금이 해제됩니다.\n");
    fflush(stdout);
    getchar();

    close(fd);
    return 0;
}
