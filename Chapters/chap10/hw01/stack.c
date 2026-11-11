// 과제 1: 연결 리스트로 스택 구현
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data);
int pop(struct node *top);

int main(void) {
    // top은 더미 노드이며, top.next가 실제 스택의 맨 위 노드를 가리킨다.
    struct node top = {0, NULL};
    int data;

    // PDF 실행 예처럼 2.3은 2를 저장한 뒤 '.'에서 입력이 종료된다.
    while (scanf("%d", &data) == 1 && data > 0)
        push(&top, data);

    printf("Print stack\n");
    while (top.next != NULL)
        printf("%d\n", pop(&top));

    return 0;
}

void push(struct node *top, int data) {
    struct node *p = malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        while (top->next != NULL)
            pop(top);
        exit(EXIT_FAILURE);
    }

    p->data = data;
    p->next = top->next;
    top->next = p;
}

int pop(struct node *top) {
    struct node *p = top->next;
    int data;

    if (p == NULL) {
        fprintf(stderr, "오류: 스택이 비어 있습니다.\n");
        return -1;
    }

    data = p->data;
    top->next = p->next;
    free(p);
    return data;
}
