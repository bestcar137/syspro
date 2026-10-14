//
// Created by bestc on 26. 10. 14..
//

#include <sys/types.h>
#include <fcntl.h>

/* 파일의 특정 영역에 읽기 또는 쓰기 잠금을 설정한다. */
int locks(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock = {0};

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return fcntl(fd, F_SETLKW, &lock);
}
