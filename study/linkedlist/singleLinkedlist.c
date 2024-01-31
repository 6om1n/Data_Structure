#include <stdio.h>
#include <stdlib.h>
typedef struct listNode *listPointer;
typedef struct listNode{
    int data; // 값을 저장하는 부분
    listPointer link; // 다음 연결리스트를 나타내는 부분
}listNode;

//새로 만들어 진 노드를 반환하므로 반환형은 listPointer이다. 값이랑 링크를 전달받음
listPointer createNode(int data, listPointer link) {
    listPointer newNode; //새로운 노드를 하나 만들어서
    newNode = (listPointer)malloc(sizeof(listNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 에러");
        exit(1);
    }
    newNode -> data = data;
    newNode -> link = link;
    return newNode;
}
/*새로운 노드를 헤더에 삽입한다. 
first는 포인터에 대한 주소를 저장하므로 이중 포인트를 사용하여 나타낸다. */
void insertHead(listPointer *first, listPointer newNode){
    newNode -> link = *first; // 기존 first가 가리키는 값이 link를 통해서 전달하고 
    *first = newNode; //first는 newNode를 가리키게한다.
}
//새로운 노드를 x 뒤에 삽입한다. newNode는 새롭게 삽입 할 원소를 나타낸다. 
void insert(listPointer *first, listPointer x, listPointer newNode){
    //first가 가리키는 값이 있을 때, 즉 연결리스트가 존재할 때
    //x->link를 newNode->link로 값을 수정한다. 
    if(*first) {
        newNode->link = x->link;
        x -> link = newNode;
    }
    // 배열의 값이 비어있을 때, first다음으로 값을 삽입한다. 
    else{
        newNode -> link = NULL;
        *first = newNode;
    }
}
//first는 포인터의 주소를 가리키고, trail은 삭제 할 노드의 직전노드를 가리키고, removeNode는 삭제 할 노드를 가리킨다.
void delete(listPointer *first, listPointer trail, listPointer removeNode){
        if(trail){
            trail -> link = removeNode -> link;
        }
        //처음 시작을 가리키는 first의 값을 NULL값으로 수정하여 나타낸다. 
        else {
            *first = (*first) -> link;
        }
        free(removeNode); // 삭제한 노드를 동적해제한다. 
}
//처음부터 돌면서 값을 출력시킨다. 
void printList(listPointer first){
    fprintf(stdout, "The list contains: ");
    for(; first; first = first -> link){
        fprintf(stdout,"%4d ",first -> data); }
    fprintf(stdout, "\n");
}
//원하는 값을 찾고, 검색한다. 
listPointer search(listPointer first, int x) {
    for(; first; first = first-> link) {
        if(first -> data == x)
            return first;
    }
    return NULL;
}

int main(int argc ,char *argv[]){
    listPointer list = NULL;
    listPointer temp = NULL;

    insertHead(&list, createNode(10, NULL));
    insertHead(&list, createNode(20, NULL));
    insertHead(&list, createNode(30, NULL));
    insertHead(&list, createNode(40, NULL));
    insertHead(&list, createNode(50, NULL));
    
    temp = search(list, 30);

    insert(&list, temp, createNode(25, NULL));
    printList(list);
    delete (&list, temp, temp->link);
    printList(list);
    delete (&list, NULL, list);
    printList(list);

    return 0;
}
