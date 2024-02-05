#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5
#define ERROR_CODE -1

typedef struct {
    int id; // 작업 id
    char description[100]; // 작업 설명
} Task;

Task queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

/*큐가 꽉 차 있을 때 */
void queueFull() {
    fprintf(stderr, "Queue is full, cannot add task\n");
    exit(EXIT_FAILURE);
}
/*큐가 비어있을 떄 */
Task queueEmpty() {
    Task emptyTask;
    emptyTask.id = ERROR_CODE;
    fprintf(stderr, "Queue is empty, no task to process\n");
    return emptyTask;
}
/*원소를 삽입할 때는 rear의 값을 하나 증가시키고 그 자리에 원소를 삽입한다. */
void addQueue(Task task) {
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (rear == front)
        return queueFull();
    queue[rear] = task ;
}
/*원소를 삭제할 때는 front의 값을 하나 증가시키고, 그 자리에 있는 원소를 삭제한다.
후에 해당하는 원소를 반환한다. */
Task deleteQueue() {
    if (front == rear)  
        queueEmpty();
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}
/*맨 처음에 있는 원소부터 값을 출력한다. 마지막 원소가 나오면 멈춘다. */
void printQueue() {
    int i;
    fprintf(stdout, "Front: %d Rear: %d\n", front, rear);
    fprintf(stdout, "Queue:\n");

    if (front == rear){
        printf("Empty\n");
        return;
    }
    i = (front + 1) % MAX_QUEUE_SIZE; //처음 원소가 있는 위치를 나타낸다.
    while (1) {
        printf("Task ID: %d\n", queue[i].id);
        printf("Description: %s\n", queue[i].description);

        if (i == rear){
            break;
        }
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}
int main(){
    int choice;
    while (1) {
        printf("1. Add Task\n2. Process Task.\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
       // getchar();

        switch (choice)
        {
        case 1:
            if ((rear + 1) % MAX_QUEUE_SIZE == front) {
                printf("Queue is full. Cannot add a new task. \n");
            } else {
                Task newTask;
                newTask.id = rear + 2;
                printf("Enter task description: ");
                scanf(" %[^\n]", newTask.description);
                addQueue(newTask);
                printf("Task added successfully. \n");
            }
            break;
        case 2:
            if (front == rear) {
                printf("Queue is empty. No task to process. \n");
            } else {
                Task task = deleteQueue();
                printf("Processing Task ...\n");
                printf("Task ID: %d\n", task.id);
                printf("Description: %s\n", task.description);
                printf("Task processed successfully. \n");
            }
            break;
        case 3:
            printf("Exiting the program. \n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        printQueue();
    }
    return 0;
}

