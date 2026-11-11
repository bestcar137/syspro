//
// Created by bestc on 26. 11. 11..
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char str[32] = "Do you like Linux?";
    char *ptr, *p;

    ptr = (char *) malloc(32);
    memcpy(ptr, str, strlen(str));
    puts(ptr);
    memset(ptr + 12, 'l', 1);
    puts(ptr);

    p = (char *) memchr(ptr, 'l', 18);
    puts(p);
    memmove(ptr + 12, str + 7, 10);
    puts(str);
}
