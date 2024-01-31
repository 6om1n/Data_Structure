//다항식의 덧셈 -> 연결리스트를 이용한
#include <stdio.h>
#include <stdlib.h>
typedef struct listNode{
    int coef;
    int expon;
    struct listNode *link;
}listNode;

typedef struct listHeader{
    int length;
    listNode *head;
    listNode *tail;
}listHeader;

//초기화 하는 함수
void init(listHeader *plist){
    plist -> length =0;
    plist -> head = NULL;
    plist -> tail = NULL;
}

void insertNodeLast(listHeader *plist, int coef, int expon){
    listNode *temp;
    temp = (listNode *)malloc(sizeof(listNode));
    if(temp ==NULL) {
        fprintf(stderr, "메모리 할당 에러");
    }
    temp -> coef = coef;
    temp -> expon = expon;
    temp -> link = NULL;
    //아직 아무것도 연결이 안 된 상태라면
    if (plist -> tail ==NULL) {
        plist -> head = plist -> tail = temp;

    }
    //뭐 하나라도 연결이 된 상태라면, tail의 값을 뒤로 이동시킨다.
    else {
        plist -> tail -> link = temp;
        plist -> tail = temp;
    }
    plist -> length++;
}

void polyadd(listHeader *plist1, listHeader *plist2, listHeader *plist3){
    //움직일 아이들의 링크를 설정해준다. 
    listNode *a = plist1 -> head;
    listNode *b = plist2 -> head;
    int sum =0;
    //하나라도 먼저 null값에 도달하면 while문은 종료된다.
    //더했을 떄 0이 되면 넣지 않으므로 그 조건도 같이 넣어준다. 
    while (a&&b) {
        if(a->expon == b-> expon){
            sum = a->coef + b -> coef;
            if (sum != 0)
                insertNodeLast(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
        }
        else if(a->expon > b->expon){
            insertNodeLast(plist3, a->coef, a->expon);
            a = a->link; //a가 더 큰 경우에는 a만을 이동시킨다. 
        }
        else {
            insertNodeLast(plist3, b->coef, b->expon);
            b = b->link;
        }
    }
    //a가 다 끝나지 않은 경우 
    for(;a!=NULL;a = a -> link){
        insertNodeLast(plist3, a->coef,a->expon);
    }
    //b가 다 끝나지 않은 경우 
    for(;b!=NULL; b = b->link){
        insertNodeLast(plist3, b->coef, b->expon);
    }
}
void printpoly(listHeader *plist){
    listNode *p =plist-> head;
    for (;p;p=p->link){
        fprintf(stdout, "%dX^%d ", p->coef, p->expon);
        if(p->link != NULL){
            fprintf(stdout, "+");
        }
    }
    fprintf(stdout, "\n");
}
//할당 받은 걸 돌려주는 함수 
void polyDelete(listHeader *plist){
    listNode *temp = plist-> head;
    listNode *del;
    while(temp->link != NULL){
        
        del = temp;
        temp = del -> link; // del보다 하나 뒤를 가리키려고 
        plist -> head = temp; // temp를 따라간다. 
        free(del);
    }
    free(temp);
}

int main(int argc, char*argv[]){
    listHeader list1, list2, list3;
    init(&list1);
    init(&list2);
    init(&list3);

    insertNodeLast(&list1, 3,5);
    insertNodeLast(&list1, 2,3);
    insertNodeLast(&list1,2,2);

    insertNodeLast(&list2,8,6);
    insertNodeLast(&list2, 3,4);
    insertNodeLast(&list2,10,2);

    polyadd(&list1, &list2, &list3);

    fprintf(stdout, "A의 다항식 : ");
    printpoly(&list1);

    fprintf(stdout, "B의 다항식 : ");
    printpoly(&list2);

    fprintf(stdout, "----------------------\n");
    fprintf(stdout, "결과 다항식 : ");
    printpoly(&list3);

    polyDelete(&list1);    
    polyDelete(&list2); 
    polyDelete(&list3);
}

