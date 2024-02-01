// 사이즈를 다르게해서 초과, empty일 때 어떤 값이 나오는 지 확인하기
#include <stdio.h>
#include <stdlib.h>
#define max_stack_size 100
#define max_expr_size 100

typedef enum{lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;

char expr[max_expr_size]={0,}; // 초기에 입력 받은 infix의 값을 저장하고 있는 배열
char postexpr[max_expr_size]={0.}; // postfix로 바뀐 것이 들어가 있는 배열
char *postfixExpr = postexpr;

precedence stack[max_stack_size]; // postfix로 바꿀 때 필요한 스택(연산자만 들어가있음)
int evalStack[max_stack_size]; // postfix로 바꾼 값을 계산할 때 필요한 스택 (숫자만 들어가있음)

int isp[]= {0,19,12,12,13,13,13,0}; // 기존 스택에 있는 연산자들의 우선순위
int icp[]={20,19,12,12,13,13,13,0}; // 스택에 들어올 연산자들의 우선순위, 이 값이 더 높으면 스택에 바로 들어온다.

int top=-1; // postfix로 바꾸기 위한 애들이 들어가있는 스택 인덱스 번호
int evalTop=-1; // 계산을 위한 정수값이 들어가 있는 스택 인덱스 번호

void stackFull(const char *type){
    fprintf(stderr, "%s stack is full cannot add element\n", type);
    exit(EXIT_FAILURE);
}
void stackEmpty(const char *type){
    fprintf(stderr, "%s stack is empty cannot delete element\n", type);
    exit(EXIT_FAILURE);
}
//postfix로 바꾸기 위한 연산자들을 집어넣는 함수
void push(precedence item){
    if(top >= max_stack_size-1){
        stackFull("token");
    }
    stack[++top] = item;
}
void evalPush(int item){
    if(evalTop >= max_stack_size-1){
        stackFull("eval");
    }
    evalStack[++evalTop] = item;
}

precedence pop(){
    if(top== -1)
        stackEmpty("token");
    return stack[top--];
}

int evalpop(){
    if(evalTop == -1)
        stackEmpty("eval");
    return evalStack[evalTop--];
}
//출력하고 싶은 애들을 배열에 하나씩 값을 저장해놓고, 나중에 한꺼번에 출력한다.
//증감후위연산자를 통해 현재 값을 얻어서 출력하고, 그 다음 인덱스로 포인터를 보낸다.
//해당하는 값을 집어넣을 때는 우리가 보는 수학 연산식의 기호로 집어넣는다.   
void printToken(precedence token){
    switch(token){
        case 2:
            *postfixExpr++ = '+';
            break;
        case 3:
            *postfixExpr++ = '-';
            break;
        case 4:
            *postfixExpr++ = '*';
            break;
        case 5:
            *postfixExpr++ = '/';
            break;
        case 6:
            *postfixExpr++ = '%';
            break;
    }
}

//token값을 얻는 함수인데, token값은 열거형에서 우리가 쓴 대로 보이기 때문에 해당하는 값을 리턴해준다. 
precedence getToken(char *symbol, int *n){
    *symbol = expr[(*n)++]; // symbol변수에 현재 자신의 위치에 있는 expr 배열의 값을 집어넣는다. 
    switch(*symbol){
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case '\0': return eos;
        default : return operand; // 숫자는 피연산자로 operand로 한번에 묶어서 처리한다.   
    }
}
int getEvalToken(char *symbol, int *n){
    *symbol = postexpr[(*n)++];
    switch(*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-': return minus;
        case '*': return times;
        case '/' : return divide;
        case '%' : return mod;
        case '\0' : return eos;
        default : return operand; 
    }
}
/*후위연산자로 바꿀 때는 입력받은 infix 연산자에서 숫자는 그대로 출력, 연산자는 우선순위에 따라 stack에 값을 넣고 뺀다. 
끝을 구분하기 위해 스택 맨 처음에 eos 값을 넣어놓는다. */
void postfix(){
    char symbol;
    int n=0;
    precedence token; // getToken으로 리턴받은 문자열이 들어있음
    top = 0;
    stack[0] = eos;
    for(token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)){
        if (token == operand) {
            //fprintf(stdout, "symbol : %d ", symbol);
            *postfixExpr++ = symbol;
        }
        //닫힌 괄호일 때, 열린 괄호가 나올 때까지 값을 빼고, 열린 괄호가 나오면 없앤다.
        else if(token == rparen) {
            while(stack[top] != lparen)
                printToken(pop()); //pop한 값을 postfix 배열에 넣는다.
            pop(); // 열린괄호는 그냥 빼버린다.
        }
        //미리 stack에 들어있는 값이 더 크면, 배열로 밖으로 꺼내준다.  
        else {
            while(isp[stack[top]] >= icp[token]) {
                printToken(pop());
            }
            push(token);
        }
    }
    while((token = pop())!= eos) {
        printToken(token); // 나머지 stack에 있는 값을 모두 출력한다. 
    }
    printf("postfix : %s\n", postexpr);
}
/*postfix를 담고 있는 postexpr에서 하나씩 꺼내와 계산하는 함수
 숫자면 push하고 연산자면 2개씩 꺼내서 pop한다. */
int eval(){
    precedence token;
    char symbol;
    int n=0;
    evalTop = -1; // 계산스택에 인덱스를 나타날 때 필요한 변수
    int op1, op2; // 두 개의 숫자를 pop할 때 필요한 변수

    token = getEvalToken(&symbol, &n);
    //문자열에는 무조건 마지막에 널 값이 들어가있기 때문에 끝이 존재한다. 
    while (token != eos){
    if(token == operand)
        evalPush(symbol-0x30); // 0번의 아스키코드가 48번 , 16진수로는 30이기에 값을 빼주어 실제값을 얻는다. 
    else {
        op2 = evalpop();
        op1 = evalpop();
        switch(token){
            case 2: evalPush(op1+op2);
            break;
            case 3: evalPush(op1-op2);
            break;
            case 4: evalPush(op1 * op2);
            break;
            case divide: evalPush(op1 / op2);
            break;
            case mod: evalPush(op1 % op2);
        }
    }
    token = getEvalToken(&symbol, &n);
    }
    return evalpop(); //최종적으로 계산 결과값을 pop해서 출력한다. 
}

int main(int argc, char *argv[]) {
    printf("input infix : ");
    scanf("%s", expr);
    postfix(); // 여기 함수에서 postfix 결과값을 아예 출력해준다. 
    printf("result : %d\n", eval()); // 최종 postfix를 계산 한 결과값을 출력해준다. 
}












