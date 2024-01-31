#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int key;
}element;
//stack이라는 자료형을 가리키고 있는 포인터인 stackpointer
//여기서 해당하는 stack은 data값과 link의 값을 가지고 있다.
typedef struct stack *stackPointer;
typedef struct stack{
    element data;
    stackPointer link;
}stack;

void push(stackPointer *top, element item) {
    stackPointer temp;
    temp = (stackPointer)malloc(sizeof(stack));

    if(temp == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        exit(1);
    }
    temp -> data =item;
    temp -> link = *top;
    *top = temp;
}
int pop(stackPointer *top, element *item){
    stackPointer temp = *top;

    item->key = -1;
    if (!temp)
        return 0;
    *item = temp->data;
    *top = temp->link; //top의 위치를 한 칸 뒤로 옮긴다.
    free(temp); //링크드리스트에서 맨 위의 값을 삭제한다.

    return 1;
}
int peek(stackPointer top, element *item){
    if (top == NULL)
        return 0;
    else {
        *item = top -> data;
        return 1;
    }
}

void printStack(stackPointer top) {
    fprintf(stdout, "The stack contains : ");
    for(; top; top = top->link)
        fprintf(stdout, "%4d ", top->data.key);
    fprintf(stdout, "\n");
}
int main(int argc, char *argv[]) {
    stackPointer top = NULL;
    element data1, data2, data3, data4;
    element temp;

    data1.key =10;
    data2.key =20;
    data3.key =30;
    data4.key =40;

    push(&top, data1);
    fprintf(stdout, "push : %4d\n", data1.key);
    push(&top, data2);
    fprintf(stdout, "push : %4d\n", data2.key);
    peek(top, &temp); //2를 반환할듯
    push(&top, data3);
    fprintf(stdout, "push : %4d\n", data3.key);
    push(&top, data4);
    fprintf(stdout, "push : %4d\n", data4.key);

    printStack(top);

    peek(top, &temp);
    fprintf(stdout, "peek : %4d\n", temp.key);

    pop(&top, &temp);
    fprintf(stdout, "pop :%4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop :%4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop :%4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop :%4d\n", temp.key);
    
    pop(&top, &temp);
    return 0;

}
