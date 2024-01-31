//이중 연결리스트를 활용한 프로그램 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

 typedef struct node{
    int data;
    struct node* prev;
    struct node* next;
}Node;
//노드를 값을 받아 새로 생성하고 리턴한다. 
Node* create(int data) {
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode -> data = data;
    return newNode;
}
//값을 삽입위치, 데이터, 연결리스트의 시작노드를 입력받아 삽입한다. 
//pos의 위치를 받으면, 해당하는 위치보다 앞에 값을 삽입한다.  
void insert(int pos, int data, Node **start){
    //삽입 위치가 1보다 작을 때, 삽입할 수 없음을 나타낸다. 
    if (pos < 1){
        puts("Invalid position");
        return ;
    }   
    //아직 아무것도 리스트에 노드가 추가되지 않은 경우
    //새로운 노드를 하나 만들어서 연결한다. 이 때, 이 전과 다음 노드에는 연결 없음 
    if (*start == NULL) {
        *start = create(data);
        (*start) -> prev = NULL;
        (*start) -> next = NULL;
    }
    //노드에 값이 있는데 추가하려는 경우
    //이 때 맨 앞에 추가할 것인지, 맨 뒤에 추가할 것인지, 중간에 추가할 것인지에 따라서 코드가 다르다. 
    else {
        Node *curr = *start; // 처음 curr은 맨 처음을 가리키고 있고
        for (; curr->next && pos > 1; pos--)
            curr = curr -> next; // 현재의 curr의 위치를 찾는다.
        //맨 뒤에 삽입하는 경우
        if(pos > 1) {
            Node *newNode = create(data);
            newNode -> prev = curr;
            newNode -> next = curr->next;
            curr -> next = newNode;
        } 
        //맨 앞에 삽입하는 경우, 시작위치인 *start의 위치를 변경한다. 
        else if(curr == *start) {
            Node *newNode = create(data);
            newNode -> prev = curr->prev;
            newNode -> next = curr;
            curr -> prev = newNode;
            *start =newNode;
        }
        //중간에 삽입하는 경우
        else {
            Node *newNode = create(data);
            newNode -> prev = curr -> prev;
            newNode -> next = curr;
            curr -> prev -> next = newNode;
            curr -> prev = newNode;
        }
    }
}
//삭제할 pos의 위치와, 시작 지점을 받아서 삭제한다. 
void deleteByPosition(int pos, Node **start) {
    if (pos < 1 || *start == NULL){
        puts("Invalid position");
        return;
    }    
    //맨 앞을 삭제하는 경우
    else if(pos == 1) {
            Node *temp = *start;
            *start = (*start)->next;
            free(temp);
    }
    //pos의 위치를 찾아서 삭제해야한다. 
    else {
        Node *temp = *start;
        for (; temp && pos >1; pos--)
            temp = temp->next;
        //삭제하고 싶은 위치를 찾지 못한 경우
        if (temp == NULL){
            puts("Invalid position");
        }
        //삭제하고 싶은 위치를 찾은 경우, 그 떄의 경우가 맨 마지막인지 아닌지를 판단해야한다. 
        else {
            temp->prev->next = temp->next;
            //마지막이라면, temp의 next값이 없을 거기때문에 조건을 하나 달아준다. 
            if (temp -> next) {
                temp->next->prev = temp->prev;
            }
            free(temp);
        }
    }
}
//전달 받은 값이랑, 시작지점이랑을 받아서 노드를 삭제한다. 
void deleteByValue(int value, Node **start){
    //값을 넘기지 않고 지우고 싶은 부분이 맨 처음에 있을 경우 
    if((*start) -> data == value) {
        Node *temp = *start;
        *start = (*start)->next;
        free(temp);
    }
    // 처음부터 계속 탐색하면서 지우고 싶은 값이 있는지를 확인한다. 
    else {
        Node *temp = (*start)->next;
        //원하는 값을 찾았을 때 temp는 멈춘다. 
        for (; temp && temp->data != value; temp = temp->next)
            ;
        if (temp ==NULL)
            puts("Element not found");
        else {
            temp -> prev->next = temp->next;
            //항상 조건에서 제일 마지막인 경우를 고려한다.
            //제일 마지막인 경우는 그 다음이 NULL이기 때문에 그 이전이 존재하지 않아서 에러발생
            if (temp -> next){
                temp->next->prev = temp->prev;
            }
            free(temp);
        }
    }
}
//순회하는 함수 만들기
void traverse(Node *x){
    int cnt =1;
    //매개변수로 넘겨받은 x가 null이 아닐 때까지 계속 반복한다.
    while(x) {
        fprintf(stdout, "%d: %d\t", cnt++, x->data);
        x =x->next;
    }
    fprintf(stdout,"\n");
}

void traverseInReverse(Node *x){
    int cnt =1;
    //넘겨받은 인자가 null이 아닐 때까지
    if (x) {
        //x -> next가 null이 아닐 때까지 계속 반복한다.  
        while(x -> next) {
            x = x -> next;
            cnt++; //제일 마지막 cnt 번호를 입력하고 싶어서 증감시킴
        }
        while(x) {
            fprintf(stdout, "%d: %d\t", cnt--, x->data);
            x = x-> prev;
        }
    }
    fprintf(stdout, "\n");
}

int menu(void){
    int choice;
    puts("1-insert data at end");
    puts("2-insert at beginning");
    puts("3-insert at position");
    puts("4-delete by position");
    puts("5--delete by element");
    puts("6-Display");
    puts("7-Display in reverse");
    puts("8-Exit");
    fprintf(stdout, "Enter choice: ");
    scanf("%d",&choice);
    getchar(); //입력한 문자를 가져간다. scanf()로 입력을 받는데에 문제를 없애기 위함

    return choice;
}

int main (int argc, char *argv[]) {
    Node *start = NULL;
    char input[10];
    int pos;

    while(1){
        switch(menu()){
            case 1:
                puts("Enter numbers, blank line to stop");
                //입력받는 문자가 공백이 아닐 때까지 계속 입력을 받는다.
                while (gets(input) && input[0] !=0)
                    insert(INT_MAX, atoi(input), &start);
                break;
            case 2 :
                fprintf(stdout, "Enter number: ");
                insert(1, atoi(gets(input)), &start);
                break;
            case 3:
                fprintf(stdout, "Enter position: ");
                pos = atoi(gets(input));
                fprintf(stdout, "Enter number: ");
                insert(pos, atoi(gets(input)), &start);
                break;
            case 4:
                fprintf(stdout, "Enter position: ");
                deleteByPosition(atoi(gets(input)), &start);
                break;
            case 5:
                fprintf(stdout, "Enter value : ");
                deleteByValue(atoi(gets(input)), &start);
                break;
            case 6:
                traverse(start);
                break;
            case 7:
                traverseInReverse(start);
                break;
            case 8:
                exit(0);
        }
    }
    return 0;
}