/*백준 - 큐 (카드2)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct queueNode{
    int item;
    struct queueNode *link;
} queueNode;

typedef struct queueType{
    queueNode *front;
    queueNode *rear;
} queueType;

queueType *q;

void init(queueType *);
void addQueue(queueType *, int);
void deleteQueue(queueType *);
int insertUnderQueue(queueType *);
void printQueue(queueType *);

void init(queueType *q) {
    q -> front = NULL;
    q -> rear = NULL;
}
/*처음 N개까지의 원소를 다 집어넣는다. */
void addQueue(queueType *q, int item) {
    queueNode *temp = (queueNode *)malloc(sizeof(queueNode));
    temp -> item = item;
    temp -> link = NULL;
    /*아무런 값이 없을 경우*/
    if (q -> front == NULL) {
        q -> front = temp;
        q -> rear = temp;
    }
    else {
        q -> rear -> link = temp;
        q -> rear = temp;
    }
}
/*삭제할 때 오직 하나만 남은 경우를 생각하기
삭제하는 경우*/
void deleteQueue(queueType *q) {
    queueNode *deleteTemp = q -> front;
    q -> front = q -> front -> link;
    //하나만 남은 경우 삭제하기
    if (q -> front == NULL){
        q -> rear = NULL;
    }
    free(deleteTemp); //맨 앞에 있는 값 버리기
}
/*맨 위에 있는 큐를 맨 아래로 내리기 -> 대신, 값이 하나만 있다면 그 값을 리턴하기*/
int insertUnderQueue(queueType *q) {
    int item;
    queueNode *temp = (queueNode *)malloc(sizeof(queueNode));
    item = q -> front -> item;
    addQueue(q, item);
    deleteQueue(q);
}
    
void printQueue(queueType *q) {
    queueNode *queuelink = q -> front;
    while(queuelink != NULL) {
        fprintf(stdout, "%d\n", queuelink->item);
        queuelink = queuelink -> link;
    }
}
int main(int argc, char *argv[]) {
    int N, item;
    scanf("%d", &N);
    getchar();
    init(&q);
    for (int i=0; i<N; i++){
        addQueue(&q, i+1);
    }
    for(int i=0; i<N-1; i++){
        deleteQueue(&q);
        insertUnderQueue(&q);
    }
    printQueue(&q);
}