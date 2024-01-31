//이중 연결리스트의 삽입, 삭제
//맨 앞에 있는 값을 삭제할 때와, 맨 뒤에 있는 값을 삭제할 때 오류처리를 해줘야할 듯
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* llink; // 이전노드를 가리킴
    struct Node* rlink; //다음노드를 가리킴   
}Node;

//중간에 노드를 삽입하려는 경우
void insertNode(Node **head, Node* prevNode, int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode -> data =  data;

    newNode -> llink = prevNode; // 왼쪽을 이전 노드로 만들고
    newNode -> rlink = prevNode -> rlink; // 새로 만든 노드의 오른쪽을 이전 노드의 오른쪽으로 바꾼다.
    
    prevNode ->rlink = newNode;
    //중간에 삽입하는 경우, 서로가 서로를 가리키게끔 코드를 구현한다. 
    if (newNode ->rlink != NULL) {
        newNode->rlink->llink = newNode;
    } 
}
//맨 앞에 노드를 삽입하려는 경우
void insertHead(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode -> data = data;
    newNode -> rlink = *head;
    newNode ->rlink -> llink = newNode;
    *head = newNode;
}
//삭제하고 싶은 값을 찾아서 삭제하기.

void deleteNode(Node **head, int data) {
    //head의 처음을 가리킨 다음에 NULL이 나올 때까지 반복하기 
    Node *a = (Node *)malloc(sizeof(Node));
    a = *head;

    for(;a; a=a->rlink) {
        if (a->data == data){
            break;
        }
    }
    if (a == NULL) {
        fprintf(stdout, "찾으려는 값이 없습니다. ");
        return ;
    }

    a->llink ->rlink = a->rlink;
    a->rlink->llink = a->llink;
    free(a);
}

int main(){
    Node* head = NULL;

    Node* firstNode =(Node*)malloc(sizeof(Node));
    firstNode->data =1;
    firstNode->llink =NULL;
    firstNode->rlink=NULL;

    head = firstNode;

    insertNode(&head, firstNode, 2);
    insertNode(&head, firstNode, 4);
    insertHead(&head, 5);

   
    //리스트 출력
    /*Node* currentNode = head;
    while (currentNode != NULL) {
        printf("%d ",currentNode->data);
        currentNode = currentNode->rlink;
    }  */
    //5라는 값을 찾아서 삭제하기 
    deleteNode(&head, 4); 
   
    Node* againNode = head;
    while (againNode != NULL) {
        printf("%d ",againNode->data);
        againNode = againNode->rlink;
    } 
}