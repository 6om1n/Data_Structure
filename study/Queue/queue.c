#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5
#define ERR_CODE -1

typedef struct{
    int key;
}element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;
int capacity = 1;

//용량을 2배로 늘리는 데에 사용함
void queueFull(){
  fprintf(stderr, "queue is full, cannot add element\n");
  exit(EXIT_FAILURE);
}

element queueEmpty(){
    element temp;
    temp.key = ERR_CODE;
    fprintf(stderr, "queue is empty, cannot delete element\n");
    return temp;
}

void addq(element item){
    rear = (rear +1) % MAX_QUEUE_SIZE;
    if(rear == front){
        queueFull();
    }
    queue[rear] = item;
}

element deleteq(){
    if(rear == front){
        return queueEmpty();
    }
    front = (front+1) % MAX_QUEUE_SIZE;
    return queue[front];
}

void printqueue(){
    printf("front : %d, rear : %d \n", front, rear);
    printf("Queue : ");
    if(rear == front){
        printf("\n");
        return;
    }
    int i = front;
    while(1){
        i=(i+1) % MAX_QUEUE_SIZE;
        printf("[%d]%d ", i, queue[i].key);
        if(i==rear)
            break;   
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    element item1, item2, item3;
     item1.key =10;
     item2.key =20;
     item3.key =30;

     addq(item1);
     printqueue();

     addq(item2);
     printqueue();

     addq(item3);
     printqueue();

    deleteq();
    printqueue();
    
    deleteq();
    printqueue();

    deleteq();
    printqueue();

    deleteq();
    printqueue();

     addq(item1);
     printqueue();

     addq(item2);
     printqueue();

     addq(item3);
     printqueue();

    addq(item1);
    printqueue();

    addq(item2);
    printqueue(); 


}