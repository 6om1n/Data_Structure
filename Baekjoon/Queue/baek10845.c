/* 백준 - 큐 -> 연결리스트로 구현해보자 
-> 연결리스트로 구현했더니 문제가 둘 다 맞아서 이 문제는 다시 배열을 사용해서 구현해보기 (다시 풀기 !)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10001

int queue[MAX_QUEUE_SIZE];

int front = -1;
int rear = -1;
int totalsize = 0;

/*큐 배열에 값을 집어넣는 함수*/
void push() {
    int item;
    scanf("%d", &item);
    getchar();
    queue[++rear] = item;
    totalsize += 1;
}
/*큐에서 맨 앞의 값을 삭제하는 함수*/
int pop() {
    int item;
    if (front == rear)
        return -1;
    else {
        totalsize -= 1;
        item = queue[++front];
        return item;
    }
    
}
int size() {
    return totalsize;
}
int empty(){
    if (front == rear)
        return 1;
    else
        return 0;
}
int getFront(){
    if (front == rear)
        return -1;
    else {
    return queue[front+1];
    }  
}
int getBack(){
    if (front == rear)
        return -1;
    else 
        return queue[rear];
}

int main(int argc, char *argv[]) {
    int N;
    char string[6];
    scanf("%d", &N);
    getchar();
    for (int i=0; i<N; i++) {
        scanf("%s", &string);
        getchar();
        if (strcmp(string, "push") ==0)
            push();
        else if (strcmp(string, "pop") == 0)
            fprintf(stdout, "%d\n", pop());
        else if (strcmp(string, "size") == 0)
            fprintf(stdout, "%d\n", size());
        else if (strcmp(string, "empty") == 0)
            fprintf(stdout, "%d\n", empty());
        else if (strcmp(string, "front") == 0)
            fprintf(stdout, "%d\n", getFront());
        else if (strcmp(string, "back") ==0)
            fprintf(stdout, "%d\n",getBack());
    }
}
