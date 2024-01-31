#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

node *prevNode;

int i = 0; // 전역변수로 설정해둔다. (어디서든 사용할 수 있게끔)
void insertNode(node **head, int item)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = item;
    newNode->next = NULL;
    // 원형 연결리스트에서 아무 값이 없으면 본인 스스로를 가리킨다.
    if (*head == NULL)
    {
        *head = newNode;
        newNode->next = newNode;
    }
    // 환형 연결리스트에서 head는 맨 앞의 값을 가지고 있다.
    else
    {
        newNode->next = (*head)->next;
        (*head)->next = newNode;
        (*head) = newNode;
    }
}

void circleNode(node *head, int number, int *result)
{
    i = 0;
    int count = 0;
    node *current = NULL;
    prevNode = head;
    head = head->next; // 맨 처음에 삽입된 노드를 가리킨다.
    while (head->next != head)
    {
        ++i;
        if (i == number)
        {
            current = head;
            head = head->next;
            result[count++] = current->data;
            prevNode->next = current->next;
            free(current);
            i = 0;
            continue;
        }
        head = head->next;
        prevNode = prevNode->next;
    }
    // 노드의 값이 하나밖에 남지 않은경우, 환형 연결리스트이기에 본인의 값을 가리킨다.
    if (head->next == head)
    {
        result[count] = head->data;
        free(head); // 최종 마지막 값을 삭제한다.
        return;
    }
}
// 없어도 되는 부분의 코드, 연결리스트가 잘 작동이 되는지를 확인하는 코드이다.
void printNode(node *head)
{
    node *current = head;
    current = current->next;
    do
    {
        fprintf(stdout, "%d ", current->data);
        current = current->next;
    } while (current != head->next);
}
// 출력문을 위한 함수
void printResult(int *result, int N)
{
    fprintf(stdout, "<");
    for (int i = 0; i < N - 1; i++)
    {
        fprintf(stdout, "%d, ", result[i]);
    }
    fprintf(stdout, "%d>", result[N - 1]);
}

int main(int argc, char *argv[])
{
    int N, K;
    scanf("%d", &N);
    int *result = (int *)calloc(N, sizeof(int)); // 배열을 삽입한다.
    getchar();                                   // 버퍼비우기
    node *head = NULL;

    // 1부터 N까지의 값을 연결리스트에 추가한다.
    for (int i = 1; i <= N; i++)
    {
        insertNode(&head, i);
    }
    scanf("%d", &K);
    getchar();
    circleNode(head, K, result);
    printResult(result, N);
    return 0;
}
