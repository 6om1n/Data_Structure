#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

char string[103];
char stack[103];

int top = -1;
int result =0;

void push(char item) {
    stack[++top]=item;    
}
char pop() {
    return stack[top--];
}

int isEmpty() {
    if(top == -1)
        return true;
    else
        return false;
}

 
int eval(char *string) {
    char result;
    
    for(int i=0; i<strlen(string); i++){
        if (string[i] == '(') {
            push('(');
        }
        else if (string[i] == '[') {
            push('[');
        }
        
        else if (string[i] == ')'){
            if(isEmpty()){
                return -1;
            }
            else {
                result = pop();
                if(result != '(') { 
                    return -1;   
                }
            }
        }
      
        else if(string[i] == ']') {
            if(isEmpty()){
                return -1;
            }
            else {
                result = pop();
                if(result != '['){
                    return -1;
                }
            }
        }
    }

    if(!isEmpty()) {
        return -1;
    } 
    return 1; 
}

int main (void) {
    while(1){
        fgets(string, 103, stdin);
        if (strcmp(string, ".\n")==0)
            break;

        //공백을 포함해서 문자열을 입력받는다. 
        int result = eval(string);
        if(result == -1) {
            fprintf(stdout, "no\n");
        }
       else if(result == 1) {
            fprintf(stdout,"yes\n");
        }
        top = -1;
    }
}
