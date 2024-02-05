#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

typedef struct stack *stackPointer;
typedef struct stack {
    element data;
    stackPointer link;
} stack;

void push(stackPointer *top, element item);
int pop(stackPointer *top, element *item);
int peek(stackPointer top, element *item);
void printStack(stackPointer top);

int main(int argc, char *argv[]) {
    stackPointer top = NULL;
    element data1, data2, data3, data4;
    element temp;

    data1.key = 10;
    data2.key = 20;
    data3.key = 30;
    data4.key = 40;

    push(&top, data1);
    fprintf(stdout, "push : %4d\n", data1.key);
    push(&top, data2);
    fprintf(stdout, "push : %4d\n", data2.key);
    push(&top, data3);
    fprintf(stdout, "push : %4d\n", data3.key);
    push(&top, data4);
    fprintf(stdout, "push : %4d\n", data4.key);

    printStack(top); // 지금까지 들어온 값들을 모두 출력한다.
    
    peek(top, &temp); //임시로 저장이 되어 있던 temp에 값을 저장한다.
    fprintf(stdout, "peek : %4d\n", temp.key);

    pop(&top, &temp);
    fprintf(stdout, "pop : %4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop : %4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop : %4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop : %4d\n", temp.key);
    pop(&top, &temp);

    printStack(top); //마지막에 출력했을 때는 stack에 아무 것도 남아있지 않은 상태이다. 
    return 0;
}
void push(stackPointer *top, element item) {
    stackPointer temp;
    temp = (stackPointer)malloc(sizeof(*temp));
    if (temp == NULL){
        fprintf(stderr, "메모리 할당 에러\n");
        exit(1);
    }
    temp -> data = item;
    temp -> link = *top; // 기존의 temp가 가리키고 있는 걸 다음으로 가리킨다.  
    *top = temp; // top의 위치를 재조정한다. 
}

//삭제하는 연산
int pop(stackPointer *top, element *item){
    stackPointer temp = *top;
    item -> key = -1;
    //만약 temp의 값이 Null이라면 리턴시킨다. 
    if (!temp)
        return 0;

    *item = temp-> data;
    *top = temp -> link;
    free(temp);

    return 1;
}
//top을 확인한다. 
int peek(stackPointer top, element *item) {
    if(top == NULL)
        return 0;
    else {
        *item = top-> data;
        return 1;
    }
}

void printStack(stackPointer top) {
        fprintf(stdout, "The stack contains : ");
        for (; top; top = top -> link)
            fprintf(stdout, "%4d ", top ->data.key);
        fprintf(stdout, "\n");
}
