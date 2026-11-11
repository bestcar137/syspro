//
// Created by bestc on 26. 11. 11..
//

// 공유 메모리: shm1.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    int shmid;
    key_t key;
    char *shmaddr;

    key = ftok("helloshm", 1);
    shmid = shmget(key, 1024, IPC_CREAT | 0644);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    printf("shmid: %d", shmid);
    shmaddr = (char *) shmat(shmid, NULL, 0);
    strcpy(shmaddr, "hello shared memory");
    return (0);
}
