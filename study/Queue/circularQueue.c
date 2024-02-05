/*원형 큐를 사용한 간단한 프로그램*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5
#define ERR_CODE -1

typedef struct {
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void queueFull();
element queueEmpty();
void addQueue(element item);
element deleteQueue();
void printQueue();

int main(int argc, char *argv[]) {
    element item1, item2, item3;
    item1.key = 10;
    item2.key = 20;
    item3. key = 30;

    addQueue(item1);
    printQueue();

    addQueue(item2);
    printQueue();

    addQueue(item3);
    printQueue();

    deleteQueue();
    printQueue();

    deleteQueue();
    printQueue();

    deleteQueue();
    printQueue();

    deleteQueue();
    printQueue();

    addQueue(item1);
    printQueue();

    addQueue(item2);
    printQueue();

    addQueue(item3);
    printQueue();

    addQueue(item1);
    printQueue();

    addQueue(item2);
    printQueue();

    return 0;
}
/*큐가 가득 차 있을 때 */
void queueFull(){
    fprintf(stderr, "Queue is full, cannot add element\n");
    exit(EXIT_FAILURE);
}
/*큐가 비어있을 때 */
element queueEmpty(){
    element temp;
    temp.key = ERR_CODE;
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    return temp;
}
/*큐가 가득 차 있지 않으면 원소를 삽입한다.
원소를 삽입할 때 우선, rear의 값을 하나 추가하고 그 자리에 삽입한다. */
void addQueue(element item) {
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == rear)
        queueFull();
    queue[rear] = item;
}
/*큐가 비어있지 않으면 원소를 삭제한다. 
원소를 삭제할 때 front의 값을 하나 증가시키고, 그 자리에 있는 원소를 삭제한다. */
element deleteQueue(){
    if (front == rear)
        return queueEmpty();
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front]; 
}
/*front와 rear의 값을 하나씩 프린트한다. 
만약 front와 rear가 같다면 비어있는 상태이므로 출력하지 않는다.
처음의 값부터 끝까지 값을 출력한다. */
void printQueue() {
    int i;
    fprintf(stdout, "front:%d rear:%d\n", front, rear);
    fprintf(stdout, "Queue: ");
    if (front == rear){
        printf("\n");
        return;
    }
    i = front;
    while (1) {
        i = (i+1) % MAX_QUEUE_SIZE;
        fprintf(stdout, "[%d]%d ", i, queue[i].key);
        if (i == rear)
            break;
    }
    fprintf(stdout, "\n");
}