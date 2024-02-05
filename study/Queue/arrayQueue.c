/*배열을 사용하여 큐를 구현*/
#include <stdio.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
/*초기에는 둘 다 같은 값을 가리키도록 초기화해준다. */
int rear = -1;
int front = -1;

/*큐가 꽉 차있을 떄 */
int isQueueFull() {
    return (rear == MAX_QUEUE_SIZE -1);
}
/*큐가 비어있을 떄*/
int isQueueEmpty() {
    return (front == rear);    
}
/* 큐에 원소를 삽입한다. -> 꽉차있을 때는 원소를 삽입하지 못한다. */
void enQueue(element item){
    if (isQueueFull()) {
        printf("Queue is full. Cannot enqueue. \n");
        return;
    }
    queue[++rear] = item;
}
/*큐에 있는 원소를 삭제한다. -> 비어있을 때는 원소를 삭제하지 못한다.
비어있을 때는 임의의 변수를 선언하여 -1로 값을 바꾸고 리턴한다. */
element deQueue() {
    if (isQueueEmpty()) {
        printf("Queue is empty. Cannot dequeue.\n");
        element emptyElement;
        emptyElement.key = -1; //왜 자꾸 삭제할 때 -1의 값을 추가하지?
        return emptyElement;
    }
    return queue[++front];
}

int main() {
    element item;
    item.key = 42;
    /*꽉 차있지 않는 경우 큐에 원소를 삽입한다. */
    if (!isQueueFull()) {
        enQueue(item);
        printf("Enqueued : %d\n", item.key);
    }
    /*큐가 비어있지 않은 경우 큐에 원소를 삭제한다. */
    if (!isQueueEmpty()) {
        element removedItem = deQueue();
        printf("Dequeued : %d\n", removedItem.key);
    }
}


