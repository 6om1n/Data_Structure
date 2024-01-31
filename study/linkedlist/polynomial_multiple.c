//다항식의 곱셈 -> 연결리스트를 이용한
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

void init(listHeader *plist){
    plist -> length =0;
    plist -> head = plist -> tail = NULL;
}
void insertNodeLast(listHeader *plist, int coef, int expon) {
    listNode *temp;
    temp = (listNode *)malloc(sizeof(listNode));
    if(temp == NULL){
        fprintf(stderr, "메모리 할당 에러 ");
        exit(1);
    }
        temp -> coef = coef;
        temp -> expon = expon;
        temp -> link = NULL;
    //아직 하나도 노드의 삽입이 이루어지지 않았다는 뜻
    if(plist -> tail == NULL){
        plist -> head = plist -> tail = temp;
    }
    //삽입된 노드가 여러개가 존재한다면 그 뒤에 연결시키고, temp를 뒤로 이동시키기
    else {
        plist -> tail-> link = temp;
        plist -> tail = temp;
    }
    plist -> length++; // 길이 증가시키기

}
void polyMul(listHeader *plist1, listHeader *plist2, listHeader *plist3) {
    listNode *a = plist1 -> head;
    listNode *b = plist2 -> head;
    int *multiply, i, highest;
    highest = a-> expon + b-> expon;
    //지수가 0인 것도 저장을 해야하므로 highest +1 만큼의 동적할당을 해준다. 
    multiply = calloc(highest+1,sizeof(int));
    while (a!=NULL){
        //a는 고정시키고 , b만 한 칸씩 뒤로 움직이면서 값을 계산한다.
      if(b!= NULL) {
        //아직 이 전에 더해진 값이 없다는 뜻
        if(multiply[(a->expon + b->expon)] ==0){
            multiply[(a->expon + b->expon)] = a->coef * b->coef;
        }
        //이 전에 이미 더해진 값이 있다는 뜻 (기 존에 있던 값에서 더해준다.)
        else {
            multiply[(a->expon + b -> expon)] += a->coef * b->coef;
        }
        b = b->link; // b는 한 칸씩 뒤로 움직이면서 a의 계수와 곱해준다. 
      }
        else {
            a = a->link;
            b = plist2 -> head; //b는 초기값으로 돌아간다.
        }   
    }
    //계수가 0일 때는 더해주는 것이 의미가 없으므로 더하지 않는다. 
    for(i=highest; i>=0; i--){
        if(multiply[i]!=0){
            insertNodeLast(plist3, multiply[i],i);
        }
    }
}
void printpoly(listHeader *plist){
    listNode *a = plist->head;
    for(;a; a=a->link){
        fprintf(stdout, "%dX^%d ", a->coef, a-> expon);
        if(a->link != NULL)
            fprintf(stdout, "+");
    }
    fprintf(stdout, "\n");
}

void polyDelete(listHeader *plist){
    listNode *temp = plist -> head;
    listNode *del;
    while(temp->link != NULL) {
        del = temp;
        temp = del-> link; // 다음 링크를 가르킨다.
        plist -> head = temp;
        free(del);
    }
    free(temp);
}
int main(int argc, char*argv[]) {
    listHeader list1, list2, list3;
    init(&list1);
    init(&list2);
    init(&list3);

    insertNodeLast(&list1,3,3);
    insertNodeLast(&list1,2,2);
    insertNodeLast(&list1,2,1);

    insertNodeLast(&list2,8,3);
    insertNodeLast(&list2,3,2);
    insertNodeLast(&list2,10,0);

    polyMul(&list1, &list2, &list3);

    fprintf(stdout, "A의 다항식 : ");
    printpoly(&list1);

    fprintf(stdout, "B의 다항식 : ");
    printpoly(&list2);

    fprintf(stdout, "-----------------------------\n");
    fprintf(stdout, "다항식 곱셈 : ");
    printpoly(&list3); 

    polyDelete(&list1);
    polyDelete(&list2);
    polyDelete(&list3);

    return 0;
}