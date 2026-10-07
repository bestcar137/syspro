//
// Created by bestc on 26. 10. 07..
//

#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (link(argv[1], argv[2]) == -1) {
        exit(1);
    }
    exit(0);
}
