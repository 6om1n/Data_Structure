#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define ERR_CODE -1

typedef struct{
    int key;
} element;

element *stack;
int capacity = 1;
int top = -1;

element stackEmpty(){
    element temp;
    temp.key =ERR_CODE;
    fprintf(stderr, "stack is empty, cannot delete element\n");
    return temp;
}

void stackFull(){
    stack = realloc(stack, 2*capacity*sizeof(*stack));
    capacity *=2;
}

int isEmpty() {
    if(top==-1)
        return true;
    else
        return false;
}

int isFull(){
    if(top >= capacity-1)
        return true;
    else
        return false;
}
void push(element item){
    if(isFull())
        stackFull();
    stack[++top] = item;
}

element pop(){
    if(isEmpty())
        return stackEmpty();
    return stack[top--]; 
}

void printstack() {
    printf("Stack: ");
    for(int i=0; i<=top; i++){
        printf("%d ", stack[i].key);
    }
    printf("\n");
}
int main(int argc, char *argv[]){
    element item1, item2, item3;    
    stack = (element*)malloc(sizeof(*stack));

    item1.key =10;
    item2.key=22;
    item3.key =55;

    printstack();

    push(item1);
    printstack();
    push(item2);
    printstack();
    push(item3);
    printstack();

    pop();
    printstack();
    pop();
    printstack();
    pop();
    printstack();

    return 0;
}










