/*백준 -덱 덱 
덱이란 양쪽에서 삽입과 삭제가 가능한 구조이며 스택과 큐의 연산을 모두 지원한다.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dequeNode{
    int item;
    struct dequeNode *next;
    struct dequeNode *prev;
}dequeNode;

typedef struct dequeType{
    dequeNode *front;
    dequeNode *rear;
    int size;
} dequeType;

dequeType *dq;

void push_back(dequeType *);
void push_front(dequeType *);
void printDeque(dequeType *);
void init ();

/*정수 x를 덱의 앞에 넣는다.
처음에 값을 넣는 경우와 하나라도 있을 때를 구분 지어서 생각한다.*/
void push_front(dequeType *dq){
    int item;
    scanf("%d", &item);
    getchar();
    dequeNode *temp = (dequeNode *)malloc(sizeof(dequeNode));
    temp -> item = item;
    temp -> prev = NULL;
    temp -> next = NULL;
    if (dq -> front == NULL){
        dq -> front = temp;
        dq -> rear = temp;
    }
    else {
        temp -> next = dq -> front;
        dq -> front -> prev = temp;
        dq -> front = temp;
    }
    dq -> size = dq -> size +1;
}
/*정수 x를 덱의 뒤에 넣는다
처음에 값을 넣는 경우와 하나라도 있을 때를 구분 지어서 생각한다.*/
void push_back(dequeType *dq) {
    int item;
    scanf("%d", &item);
    getchar();
    dequeNode *temp = (dequeNode *)malloc(sizeof(dequeNode));
    temp -> item = item;
    temp -> prev = NULL;
    temp -> next = NULL;
    if (dq -> front == NULL){
        dq -> front = temp;
        dq -> rear = temp;
    }    
    else {
        dq -> rear -> next = temp;
        temp -> prev = dq -> rear;
        dq -> rear = temp;
    }
    dq -> size = dq -> size +1;
}
/*덱의 가장 앞에 있는 수를 뺴고, 그 수를 출력한다.*/
int pop_front(dequeType *dq) {
   
    if (dq -> front == NULL)
        return -1;

    dequeNode *temp = dq -> front;
    int item = temp -> item;
    dq -> front = dq -> front -> next;
    //즉, 하나만 있는 경우를 삭제한 경우
    if (dq -> front == NULL) {
        dq -> rear = NULL;
        free(temp);
        dq -> size = dq -> size -1;
        return item;
    }
    else {
        dq -> front -> prev = NULL;
        free(temp);
        dq -> size = dq -> size -1;
        return item;
    }

}
int pop_back(dequeType *dq) {
   
   if (dq -> front == NULL)
        return -1; 
    dequeNode *temp = dq -> rear;
    int item = dq -> rear -> item;
    dq -> rear = dq -> rear -> prev;
    if (dq -> rear == NULL) {
        dq -> front = NULL;
        free(temp);
        dq -> size = dq -> size -1;
        return item;
    }
    else {
        temp -> prev -> next = NULL;
        free(temp);
        dq -> size = dq -> size -1;
        return item;
    }
}
int size(dequeType *dq){
    return dq -> size;
}
int empty(dequeType *dq){
    if (dq -> front == NULL)
        return 1;
    else
        return 0;
}
int front(dequeType *dq) {
    if (dq -> front == NULL)
        return -1;
    else
        return dq -> front -> item;
}
int back(dequeType *dq) {
    if (dq -> front == NULL)
        return -1;
    else
        return dq -> rear -> item;
}
void init(){
    dq -> front = NULL;
    dq -> rear = NULL;
    dq -> size = 0;
}
int main() {
    int N;
    char string[12];
    
    scanf("%d", &N);
    getchar();
    for (int i=0; i<N; i++) {
        scanf("%s", string);
        getchar();
        if (strcmp(string, "push_back") == 0)
            push_back(&dq);
        else if (strcmp(string, "push_front") ==0)
            push_front(&dq);
        else if (strcmp(string, "pop_front") ==0)
            fprintf(stdout, "%d\n", pop_front(&dq));
        else if (strcmp(string, "pop_back") ==0)
            fprintf(stdout, "%d\n",pop_back(&dq));
        else if (strcmp(string, "size") ==0)
            fprintf(stdout, "%d\n", size(&dq));
        else if (strcmp(string, "empty") ==0)
            fprintf(stdout, "%d\n", empty(&dq));
        else if (strcmp(string, "front") ==0 )
            fprintf(stdout, "%d\n", front(&dq));
        else if (strcmp(string, "back") ==0)
            fprintf(stdout, "%d\n", back(&dq));
    }
}