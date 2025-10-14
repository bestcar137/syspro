//
// Created by bestc on 25. 10. 14..
//

#include<sys/unistd.h>

/// path 심볼릭 링크의 실제 내용을 읽어서 buf에 저장한다.
/// 성공하면 buf에 저장한 바이트 수를 반환하며 실패하면 -1을 반환한다.
int readlink(const char *path, char *buf, size_t bufsize);


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buffer[1024];
    int nread;

    nread = readlink(argv[1], buffer, 1024);
    if (nread > 0) {
        write(1, buffer, nread);
        exit(0);
    } else {
        fprintf(stderr, "Error: No such link\n");
        exit(1);
    }
}
