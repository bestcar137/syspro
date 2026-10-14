//
// Created by bestc on 26. 10. 14..
//

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/* 파일의 특정 영역에 원하는 잠금을 설정할 수 있는지 검사한다. */
pid_t lockt(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock = {0};

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if (fcntl(fd, F_GETLK, &lock) == -1)
        return -1;

    if (lock.l_type == F_UNLCK)
        return 0;

    return lock.l_pid;
}
