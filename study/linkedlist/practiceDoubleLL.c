#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct node{
    struct node *prev;// 이전노드
    int roll_no; //학번
    char name[N]; //이름
    float marks; //성적
    struct node *next; //다음노드
}node;

void init(node *);
void insertAfter(node *);
node *insertBefore(node *);
node *delete(node *);
void search(node *);
void display(node *);
void rollSrch(node *);
void nameSrch (node *);
void markSrch (node *);

//초기화하는 함수, 연결 없이 그저 하나의 노드를 만드는 것
void init(node *current){
    current -> prev = NULL;
    fprintf(stdout, "\nEnter Roll number\n");
    scanf("%d", &current->roll_no);
    getchar(); //널 문자를 없애는 역할을 한다.

    fprintf(stdout, "\nEnter the name\n");
    gets(current->name);

    fprintf(stdout, "\nEnter the marks\n");
    scanf("%f", &current->marks);
    getchar();

    current->next = NULL;
}
node *insertBefore(node *current) {
    int rno; // 이 전에 집어넣을 노드의 학번을 나타내는 값
    //newnode는 새로 만든 노드를 나타내고, temp는 하나씩 앞으로 갈 노드를 나타낸다.
    node *newnode, *temp;  
    newnode = (node *)malloc(sizeof(node));
    fprintf(stdout, "\nEnter the roll number before which you want to insert a node\n");
    scanf("%d",&rno);
    getchar(); //버퍼비우기
    
    init(newnode);
    //head의 값을 입력받았으므로 맨 앞에 노드를 집어넣겠다는 말
    //따라서 노드의 변화가 필요하다. 
    if (current -> roll_no == rno) {
        newnode -> next = current;
        current -> prev = newnode;
        current = newnode; // 맨 앞에 집어넣었으므로 current의 위치를 바꾸고
        return (current); 
    }
    //처음부터 하나씩 진행하면서 해 나갈 temp를 만든다.
    temp = current;
    //주어진 노드를 끝까지 확인한다. 노드를 찾았을 경우 temp 앞에 값을 넣어준다. 
    //current의 값은 맨 처음에서 움직이지 않았으므로 current의 값을 리턴해준다.  
    while (temp -> next != NULL) {
        if (temp->next->roll_no == rno){
            newnode -> next = temp ->next;
            newnode -> prev = temp;
            temp -> next = newnode;
            temp -> next -> prev = newnode;
            return (current);
        }
        temp = temp -> next;  
    }
    //여기까지 온 이상 값을 못찾았다는 의미
    fprintf(stdout, "\nMatch not found\n");
    return (current); // 값을 못찾았으니 추가하지 않고 기존의 head를 리턴해준다. 
}
//마찬가지로 이 후에 넣을 노드를 찾고, 새롭게 움직일 노드를 하나 만든다. 
void insertAfter(node *current) {
    int rno;
    int flag =0; // 여기서 flag는 원하는 것을 시도를 했는지 안했는지를 판단하는 변수
    node *newnode = (node *)malloc(sizeof(node));
    fprintf(stdout, "\nEnter the roll number after which you want to insert a node\n");
    scanf("%d", &rno);
    getchar();

    init(newnode);
    while (current -> next != NULL) {
        // 첫 번째 노드에서 이미 값을 찾음
        if (current -> roll_no == rno){
            newnode-> next = current -> next;
            current -> next = newnode;
            current -> next -> prev = newnode;
            newnode -> prev = current;
            flag =1; // 원하는 걸 이미 했다는 것을 의미한다. 
        }
        current = current -> next;
    }
        //맨 마지막에서 원하는 값을 찾은 경우
        if (flag == 0 && current -> next == NULL && current -> roll_no == rno){
            newnode -> next = current -> next;
            newnode -> prev = current;
            current -> next = newnode;
            flag =1; // 원하는 값을 찾았다는 것을 의미함
        }
        //노드의 끝에서도 원하는 것을 찾지 못함, 해당하는 걸 찾지못했다는 문구
        else if (flag ==0 && current -> next ==NULL) {
            fprintf(stdout, "\nNo match found\n");
        }
}
node *delete(node *current) {
    int rno;
    node *newnode, *temp;
    fprintf(stdout, "\nEnter the roll number whose node you want to delete\n");
    scanf("%d", &rno);
    getchar();

    newnode = current;
    if (current -> roll_no == rno) {
        current = current->next;
        current->prev = NULL;
        free(newnode);
        return (current);
    }
    else {
        while (newnode->next->next !=NULL) {
            if (newnode->next->roll_no == rno){
                temp = newnode ->next;
                newnode->next = newnode->next-> next;
                newnode->next->prev = newnode;
                free(temp);
                return (current);
            }
            newnode = newnode->next;
        }
        if (newnode->next->next == NULL && newnode->next->roll_no ==rno){
            temp = newnode->next;
            free(temp);
            newnode ->next =NULL;
            return (current);
        }
    }
    fprintf(stdout, "\nWatch not found\n");
    return (current);
}
void search(node *current) {
    int ch; //어떤 걸 기준으로 탐색할 지를 변수로 받아온다/
    fprintf(stdout, "\nEnter the criteria for search\n");
    fprintf(stdout, "\n1. Roll number");
    fprintf(stdout, "\n2. Name\n");
    fprintf(stdout, "\n3. Marks\n");
    scanf("%d", &ch);
    getchar();

    switch(ch) {
        case 1:
            rollSrch(current);
            break;
        case 2:
            nameSrch(current);
            break;
        case 3:
            markSrch(current);
            break;
        default :
            rollSrch(current);
    }
}
//학번을 기준으로 탐색한다.
void rollSrch(node *current) {
    int rno;
    fprintf(stdout, "\nEnter the roll number to search\n");
    scanf("%d", &rno); // 기준으로 찾고 싶은 학번을 입력받는다.
    getchar();
    //그 다음이 NULl값이 아닐 때까지
    while(current -> next != NULL) {
        if (current -> roll_no == rno) {
            fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);
        }
        current = current -> next; //한칸씩 뒤로 이동한다.
    }
    if (current -> next ==NULL && current->roll_no == rno)
        fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);
}

void nameSrch (node *current) {
    char arr[20]; //이름을 입력받는 배열
    fprintf(stdout, "\nEnter the name to search\n"); //
    gets(arr); //문자열을 gets로 입력받는다.
    while (current -> next != NULL ){
        if (strcmp(current-> name, arr) == 0)
           fprintf(stdout, "\n%d\t%s\t%f\n", current-> roll_no, current->name, current->marks);
        current = current -> next;
    }
    if (current -> next == NULL && strcmp(current -> name, arr) == 0)
        fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);
}

//성적을 기준으로 찾는다.
void markSrch(node *current) {
    float marks;
    fprintf(stdout, "\nEnter the marks to search\n");
    scanf("%f", &marks);
    getchar();

    while(current -> next != NULL) {
        if (current -> marks == marks)
            fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);
        current = current -> next;
    }
    if (current -> next == NULL && current -> marks == marks)
        fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);
}

void display(node *current) {
    fprintf(stdout, "\nroll no\t\tname\t\tmark");
    while (current != NULL){
        fprintf(stdout, "\n%4d\t\t%s\t\t%f", current->roll_no, current->name, current->marks);
        current = current -> next;
    }
}

int main(int argc, char *argv[]) {
    node *head;
    static int flag =0;
    char ch;
    int opt;
    system("clear"); // 이걸 굳이 하는 이유는?
    head = (node *)malloc(sizeof(node));
    head-> next = NULL;
    head -> prev = NULL;
    do {
        again:
        fprintf(stdout, "\nEnter your option\n");
        fprintf(stdout, "\n1. Initialize the node\n");
        fprintf(stdout, "\n2. Insert before a specified node\n");
        fprintf(stdout, "\n3. Insert after a specified node\n");
        fprintf(stdout, "\n4. Delete a particular node\n");
        fprintf(stdout, "\n5. Search the nodes\n");
        fprintf(stdout, "\n6. Display all the nodes\n");
        scanf("%d", &opt);
        getchar();

        if(flag ==0 && opt != 1){
            fprintf(stdout, "\nNo. You must first initialize at least one node\n");
            goto again;
        }
        if (flag ==1 && opt ==1){
            fprintf(stdout, "\nInitialisation can occur only once.\n");
            fprintf(stdout, "\nNow you can insert a node\n");
            goto again;
        }
        if(opt ==4 && head -> next ==NULL){
            fprintf(stdout, "\nYou cannot delete the one and only the single node\n");
            goto again;
        }
        if (flag ==0 && opt ==1)
            flag =1;
        switch (opt){
            case 1:
                init(head);
                break;
            case 2:
                head = insertBefore(head);
                break;
            case 3:
                insertAfter(head);
                break;
            case 4:
                head = delete(head);
                break;
            case 5:
                search(head);
                break;
            case 6:
                display(head);
                break;
        }
        fprintf(stdout, "\nDo you wish to continue[y/n]\n");

        ch = getchar();
        fprintf(stdout, "%c\n", ch);
    } while(ch == 'Y' || ch =='y');

    fprintf(stdout, "\nDone by \"SHABBIR\"\n");
    fprintf(stdout, "\nPress any key to exit\n");
    return 0;
        
}
