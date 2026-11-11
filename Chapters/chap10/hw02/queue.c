// 과제 2: 연결 리스트로 큐 구현
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data);
int delete(struct node *head, struct node *tail);

int main(void) {
    // head와 tail은 관리용 더미 노드이다.
    // head.next는 첫 노드, tail.next는 마지막 노드를 가리킨다.
    struct node head = {0, NULL};
    struct node tail = {0, NULL};
    int data;

    while (scanf("%d", &data) == 1 && data > 0)
        addq(&head, &tail, data);

    printf("Print queue\n");
    while (head.next != NULL)
        printf("%d\n", delete(&head, &tail));

    return 0;
}

void addq(struct node *head, struct node *tail, int data) {
    struct node *p = malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        while (head->next != NULL)
            delete(head, tail);
        exit(EXIT_FAILURE);
    }

    p->data = data;
    p->next = NULL;

    if (head->next == NULL)
        head->next = p;           // 빈 큐에 넣으면 첫 노드가 된다.
    else
        tail->next->next = p;     // 기존 마지막 노드 뒤에 연결한다.

    tail->next = p;
}

int delete(struct node *head, struct node *tail) {
    struct node *p = head->next;
    int data;

    if (p == NULL) {
        fprintf(stderr, "오류: 큐가 비어 있습니다.\n");
        return -1;
    }

    data = p->data;
    head->next = p->next;
    if (head->next == NULL)
        tail->next = NULL;        // 마지막 노드 삭제 후 꼬리도 초기화한다.

    free(p);
    return data;
}
