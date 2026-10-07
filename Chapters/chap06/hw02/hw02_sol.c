//
// Created by bestc on 26. 10. 07..
//

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

char type(mode_t);
char *perm(mode_t);

void printStat(char *, char *, struct stat *);

/* 옵션 사용 여부 */
int option_i = 0;
int option_p = 0;
int option_Q = 0;

/* 디렉터리 내용을 자세히 리스트한다. */
int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int c;

    /* 명령행 옵션 처리 */
    while ((c = getopt(argc, argv, "ipQ")) != -1) {
        switch (c) {
            case 'i':
                option_i = 1;
                break;

            case 'p':
                option_p = 1;
                break;

            case 'Q':
                option_Q = 1;
                break;

            default:
                fprintf(stderr, "사용법: %s [-i] [-p] [-Q] [directory]\n",
                        argv[0]);
                exit(1);
        }
    }

    /* 옵션 다음에 디렉터리가 있으면 그 디렉터리 사용 */
    if (optind < argc)
        dir = argv[optind];
    else
        dir = ".";

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        /* 디렉터리의 각 파일에 대해 */
        sprintf(path, "%s/%s", dir, d->d_name);

        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st);
    }

    closedir(dp);

    exit(0);
}


/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st) {

    /* -i 옵션 : inode 번호 출력 */
    if (option_i)
        printf("%8ld ", st->st_ino);

    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);

    printf("%s %s ",
           getpwuid(st->st_uid)->pw_name,
           getgrgid(st->st_gid)->gr_name);

    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);

    /* -Q 옵션 : 파일 이름을 큰따옴표로 감싼다 */
    if (option_Q)
        printf("\"%s\"", file);
    else
        printf("%s", file);

    /* -p 옵션 : 디렉터리이면 이름 뒤에 / 추가 */
    if (option_p && S_ISDIR(st->st_mode))
        printf("/");

    printf("\n");
}


/* 파일 타입을 반환 */
char type(mode_t mode) {
    if (S_ISREG(mode))
        return '-';

    if (S_ISDIR(mode))
        return 'd';

    if (S_ISCHR(mode))
        return 'c';

    if (S_ISBLK(mode))
        return 'b';

    if (S_ISLNK(mode))
        return 'l';

    if (S_ISFIFO(mode))
        return 'p';

    if (S_ISSOCK(mode))
        return 's';

    return '?';
}


/* 파일 접근권한을 반환 */
char *perm(mode_t mode) {
    static char perms[10];

    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';

        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';

        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }

    return perms;
}