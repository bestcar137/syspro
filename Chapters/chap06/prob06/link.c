//
// Created by bestc on 25. 10. 14..
//

#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (link(argv[1], argv[2]) == -1) {
        exit(1);
    }
    exit(0);
}
