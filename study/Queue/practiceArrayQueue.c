/*큐를 활용하여 간단한 작업 관리 시스템 프로그램이다. */

#include <stdio.h>

#define MAX_QUEUE_SIZE 100

typedef struct
{
    int id;                // 작업 id
    char description[100]; // 작업 설명
} Task;

// 이렇게 구조체형 배열을 선언하므로써 위의 구조체에서 정의한 모든 변수를 사용할 수 있다.
Task queue[MAX_QUEUE_SIZE];

int rear = -1;
int front = -1;

int isQueueFull()
{
    return (rear == MAX_QUEUE_SIZE - 1);
}

int isQueueEmpty()
{
    return (rear == front);
}
void enQueue(Task task)
{
    if (isQueueFull())
    {
        printf("Queue is full. Cannot enqueue. \n");
        return;
    }
    queue[++rear] = task;
}

Task deQueue()
{
    if (isQueueEmpty())
    {
        printf("Queue is empty. Cannot deQueue. \n");
        Task emptyTask;
        emptyTask.id = -1;
        return emptyTask;
    }
    return queue[++front];
}

void printTask(Task task)
{
    printf("Task ID : %d\n", task.id);
    printf("Description: %s\n", task.description);
}
/*1번의 경우에는 값을 집어넣는 것이기 때문에 큐가 가득차있는지 아닌지를 판단
  2번의 경우에는 하나씩 값을 빼와서 그걸 출력하기에 큐가 비어있는지 아닌지를 판단
  3번의 경우에는 종료할건지 아닌지를 판단, 나머지의 경우에는 다시 입력하도록 설계*/
int main()
{
    int choice;
    while (1)
    {
        printf("1. Add Task\n2. Process Task.\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (!isQueueFull())
            {
                Task newTask;
                newTask.id = rear + 2; // 독보적인 id의 값을 생성한다.
                printf("Enter task description: ");
                scanf(" %[^\n]", newTask.description);
                enQueue(newTask);
                printf("Task added successfully.\n\n");
            }
            else
            {
                printf("Queue is full. Cannot add a new task. \n");
            }
            break;
        case 2:
            if (!isQueueEmpty())
            {
                Task task = deQueue();
                printf("Processing Task...\n");
                printTask(task);
                printf("Task processed successfully \n");
            }
            else
            {
                printf("Queue is empty. No task to process. \n");
            }
            break;

        case 3:
            printf("Exiting the program. \n");
            return 0; //해당 메인 함수를 종료시킨다. 

        default:
            printf("Invalid choice. Please try again. \n");
            break;
        }
    }
    return 0;
}
