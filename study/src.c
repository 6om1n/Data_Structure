#include <stdio.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
} element;

element queue[MAX_QUEUE_SIZE];

int rear = -1;
int front = -1;

void addQueue(element item) {
    if (rear == MAX_QUEUE_SIZE -1)
        queueFull();
    queue[++rear] = item;
}

void deleteQueue(element item) {
    if (front == rear)
        return queueEmpty();
    return queue[++front];
}



