#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;
Node * createNode(int data){
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp ==NULL) {
        printf("메모리 할당 오류");
        exit(1); //비정상적인 오류를 나타낸다.
    }
    temp -> data = data;
    temp -> next = NULL;
    return temp;
}

void insertNode(Node **head, int data){
    Node *newNode = createNode(data);
    //아직 아무런 값도 입력이 되지 않았을 때
    if (*head == NULL){
        *head = newNode;
        newNode -> next = newNode; //자기자신을 가리키도록 한다.
    }
    //빈 노드가 아닐 경우
    else {
        newNode-> next = (*head) -> next;
        (*head) ->next = newNode;
        *head = newNode; //제일 마지막에 추가된 노드로 head의 위치를 옮긴다. 
    }
}
void printCircularList(Node *head){
    if (head ==NULL){
        printf("리스트가 비어 있습니다.\n");
        return;
    }
    Node *current = head -> next;
    do {
        printf("%d -> ", current -> data);
        current = current -> next;
    } while(current != head -> next);

    printf("...\n");
}

int main(){
    Node* head = NULL;

    insertNode(&head,1);
    insertNode(&head,2);
    insertNode(&head,3);

    printf("환형 연결 리스트 :");
    printCircularList(head);

    return 0;
}