//
// Created by bestc on 25. 10. 14..
//

/// 심볼릭 링크를 만드는데 성공하면 0, 실패하면 -1을 리턴한다.
int symlink(const char *actualpath, const char *sympath);

#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (symlink(argv[1], argv[2]) == -1) {
        exit(1);
    }
    exit(0);
}
