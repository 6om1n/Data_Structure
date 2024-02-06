/*백준 큐 - 큐2
첫째 줄에서 주어지는 명령의 수가 너무 커서 연결리스트로 구현하기*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queueNode {
    int item;
    struct queueNode *link;
} queueNode;

typedef struct queueType {
    queueNode *front;
    queueNode *rear;
    int size;
}queueType;

/*정수 x를 큐에 넣는 연산이다, 큐에 아무것도 없는 상태인지 아닌지를 판별해야함*/
void push(queueType *q) {
    int item;
    scanf("%d", &item); 
    getchar();
    queueNode *temp = (queueNode *)malloc(sizeof(queueNode));
    temp -> item = item;
    temp -> link = NULL;
    /*아무런 값도 들어가지 않은 상태라면*/
    if (q -> front == NULL) {
        q -> front = temp;
        q -> rear = temp;
        q -> size = q -> size + 1;
    }   
    /*큐에 값이 하나라도 들어가있는 상태라면*/
    else {
        q -> rear -> link = temp;
        q -> rear = temp;
        q -> size = q -> size + 1;
    }
}
/*큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. */
int pop(queueType *q) {
    if (q -> front == NULL)
        return -1;
    else {
        queueNode *temp = q -> front;
        int item = temp -> item;
        q -> front = q -> front -> link;
        //하나밖에 없는 값을 삭제하는 경우
        if (q -> front == NULL) {
            q -> rear = NULL;
        }
        free(temp);
        q -> size = q -> size -1;
        return item;
    }
}
int empty(queueType *q) {
    if (q -> front == NULL)
        return 1;
    else
        return 0;
}
int front(queueType *q) {
    if (q -> front == NULL) {
        return -1;
    }
    else {
        return q -> front -> item;
    }
}   
int back(queueType *q) {
    if (q -> front == NULL)
        return -1;
    else {
        return q -> rear -> item;
    }
}
void init(queueType *q) {
    q -> front = NULL;
    q -> rear = NULL;
    q -> size =0;
}
int size(queueType *q) {
    return q -> size;
}
int main(int argc, char *argv[]) {
    int N;
    char string[6]; //명령을 입력받을 변수
    scanf("%d", &N);
    getchar(); //버퍼비워주기
    queueType q;
    init(&q);
    //N개 만큼의 명령이 주어진다.
    for (int i=0; i<N; i++) {
        scanf("%s", string);
        getchar();
        if (strcmp(string, "push") == 0 ) {
            push(&q); //push함수와 같은 것을 호출한다면 push 함수를 호출
        }
        else if (strcmp(string, "pop") == 0){
            fprintf(stdout, "%d\n", pop(&q));
        }
        else if (strcmp(string, "empty") == 0) {
            fprintf(stdout, "%d\n", empty(&q));
        }
        else if(strcmp(string, "front") == 0) {
            fprintf(stdout, "%d\n", front(&q));
        }
        else if(strcmp(string, "back") == 0){
            fprintf(stdout, "%d\n", back(&q));
        }
        else if(strcmp(string, "size") == 0){
            fprintf(stdout, "%d\n", size(&q));
        }
    }
}