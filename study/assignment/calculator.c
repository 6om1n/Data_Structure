/*스택 계산기 - 수식을 모두 argv[1]로 입력 받기 위해서 수식 전체를 따옴표 안에 입력한다.
처음에 수식을 argv[1]에 입력을 받고, 그 이후에는 키보드로부터 수식을 입력받을 수 있도록 해야한다.
연산자와 피연산자는 공백으로 구분한다 -
피연산자는 실수, 정수만 가능하다. 그 외에는 예외처리 후 다시 입력받아야한다. 정수 실수를 만나면 실수값을 반환한다.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_EXPR_SIZE 100
int n = 0,  infixNumber = 0, prefixNumber = 0, postfixNumber = 0;
int calculation_result =0;
// 사용자가 입력하는 값이 들어있는 배열 - 공백을 포함한다.
char expr[MAX_EXPR_SIZE] = {
    0,
};
// 공백 없이 연산자와 피연산자만 들어있는 배열, 처음 받아온 값이 저장되어있다. 
char *newexpr[MAX_EXPR_SIZE] = {0,};
//전위를 중위로 바꾸고 나서의 공백 없는 배열
char *newPreInfixExpr[MAX_EXPR_SIZE];
//후위를 중위로 바꾸고 나서의 공백 없는 배열
char *newPostInfixExpr[MAX_EXPR_SIZE];

// 중위 수식이 들어왔을 떄 후위수식을 저장할 수 있는 배열
char postExpr[MAX_EXPR_SIZE][MAX_EXPR_SIZE] = {
    0,
};
char *postfixExpr = postExpr;
// 들어갈 수 있는 연산자를 열거형으로 정의한다.
typedef enum
{
    lparen,
    rparen,
    plus,   // 2
    minus,  // 3
    times,  // 4
    divide, // 5
    mod,    // 6
    power,  // 7
    eos,
    operand
} precedence;

// isp : 스택에 이미 들어간 것의 우선순위, icp: 스택에 들어오려는 연산자의 우선순위
int isp[] = {0, 0, 12, 12, 13, 13, 13, 15, 0};
int icp[] = {20, 17, 12, 12, 13, 13, 13, 15, 0};

// 들어오는 값이 오직 정수가 아니라 실수의 값도 들어올 수 있기 때문에 두 가지의 값을 다 추가한다.
// push, pop과 같은 경우는 연결리스트를 사용해서 stack을 구현한다.

typedef struct prefixNode{
    struct prefixNode *prev;
    char* value; // 숫자 중에서 두자리 혹은 세자리도 나올 수 있으므로
    struct prefixNode *next;
}prefixNode;

typedef struct stack
{
    char *value; //연산자를 저장할 수 있는 변수
    int length;
    precedence data; // 우선순위를 저장할 수 있는 변수
    struct stack *link; // 다음 링크를 가리키는 포인터
} stack;

typedef struct evalStack {
    int item;
    struct evalStack *link;
} evalStack;

typedef stack *stackPointer;
typedef evalStack * evalStackPointer;
typedef prefixNode *infixPrefixPointer;

// postfix로 바뀐 최종 수식을 집어넣을 수 있는 연결리스트
stackPointer infix_postfix;
stackPointer infix_prefix;
stackPointer postfix_infix;
stackPointer prefix_infix;
stackPointer top;
stackPointer temp; // 위치를 임시로 저장할 수 있는 변수
stackPointer top_result;
evalStackPointer eval;
infixPrefixPointer prefixFormula;
infixPrefixPointer newtemp;

void inputExpression();
int insertExpression();
int isValidExpression(char *);
void checkExit(char *);
precedence getToken(char *);
void infix();
void prefix();
void postfix();
void push(stackPointer *, precedence);
precedence pop(stackPointer *);
void infixToPostfix();
void infixToPrefix();
int postEvaluation();
void printToken(precedence);
void insertDoubleList(char *);
void printDoubleToken(precedence);
void postfixToInfix();
void infixPush();
void prefixToInfix();
char * makeExpression(char*, char*, char*);
char * makeFinalExpression(char*, char*, char*);

void infixPush(stackPointer *top, char *symbol) {
    stackPointer temp;
    temp = (stackPointer)malloc(sizeof(stack));
    if (temp == NULL)
    {
        fprintf(stdout, "메모리 할당 에러 \n");
        exit(1);
    }
    temp-> value = symbol;
    temp-> link = *top;
    (*top) = temp;  
}
char * infixPop(stackPointer *top) {
    stackPointer temp = *top;
    *top = (*top) -> link;
    char *result = temp -> value; //맨 위에 있는 문자열을 전달받는다.
    free(temp);
    return result;
}

void push(stackPointer *top, precedence item)
{
    stackPointer temp;
    temp = (stackPointer)malloc(sizeof(stack));
    if (temp == NULL)
    {
        fprintf(stdout, "메모리 할당 에러 \n");
        exit(1);
    }
    temp->data = item;
    temp->link = *top;
    (*top) = temp;
}
precedence pop(stackPointer *top)
{
    if (*top == NULL)
        return eos;
    stackPointer temp = *top;
    precedence result = temp->data;
    *top = (*top)->link; // 한 칸 뒤로 움직인다.
    free(temp);
    return result;
}

/*후위연산자를 계산할 수 있도록 하는 함수 */
void evalPush(evalStackPointer *eval, int item) {
    evalStackPointer temp;
    temp = (evalStackPointer)malloc(sizeof(evalStack));
    if(temp == NULL) {
        fprintf(stderr, "메모리 할당 에러 \n");
        exit(1);
    }
    temp -> item = item;
    temp -> link = *eval;
    (*eval) = temp;
}
int evalPop(evalStackPointer *eval){
    evalStackPointer temp = *eval;
    *eval = (*eval) -> link;
    int result = temp -> item; //정수의 값이 들어온다. 
    free(temp);
    return result;
}

void inputExpression()
{
    fprintf(stdout, "input expression : ");
    fgets(expr, sizeof(expr), stdin); // 우선 한 번을 입력을 받는다.
    fprintf(stdout, "\n");
}
// 사용자가 입력한 값을 토큰 단위로 분리하고, isValidExpression 함수를 호출하여 올바른 수식인지 확인한다.
int insertExpression(char *expr, char *newexpr[])
{
    n = 0;
    int sum = 0;
    int check = 0;
    char *delimiters = " \t\n";
    //전역변수를 초기화하여 
    for (int i=0; i<MAX_EXPR_SIZE; i++)
        newexpr[i] = NULL;
    
    char *token = strtok(expr, delimiters);

    while (token != NULL)
    {
        // fprintf(stdout, "%s\n", token);
        check = isValidExpression(token);
        // fprintf(stdout, "%d\n", check);

        if (check == -1)
            return -1;

        newexpr[n++] = strdup(token);
        token = strtok(NULL, delimiters);
    }
    // for (int i=0; i<n; i++)
    // fprintf(stdout, "%s", newexpr[i]);
    // fprintf(stdout, "\n\n%d\n%d", strlen(newexpr), n);
    return 0;
}
/*수식이 올바르지 않을 경우 -1을 리턴하는 함수.
숫자일경우 3을 리턴하고, 괄호일경우 2를 리턴하고, 연산자일 경우 1을 리턴하고, 아무것도 아닐 때 -1을 리턴하여 예외처리해준다. */
int isValidExpression(char *token)
{
    char *endptr;
    char *endptr2;
    long result = strtol(token, &endptr, 10);
    double result2 = strtod(token, &endptr2);
    // 전달 받은 token이 정수인지 아닌지를 판별한다.
    if (*endptr == '\0')
        return 3;
    // 전달 받은 token이 실수인지 아닌지를 판별한다.
    else if (token != endptr2 && *endptr2 == '\0')
        return 3;
    // token이 연산자인지 아닌지를 판별한다.
    else if (strcmp(token, "(") == 0 || strcmp(token, ")") == 0)
        return 2;
    else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 ||
             strcmp(token, "/") == 0 || strcmp(token, "%") == 0 || strcmp(token, "^") == 0)
        return 1;
    else
    {
        return -1;
    }
}

// 전달 받은 문자열이 exit인지 아닌지를 검사한다.
void checkExit(char *expr)
{
    if (strncmp(expr, "exit", 4) == 0)
    {
        fprintf(stdout, "exit program.. ");
        exit(0);
    }
}
/*입력 받은 수식이 전위, 중위, 후위인지 판별한다.
괄호가 나오거나, 맨 앞이 숫자, 연산자인 경우 -> 중위
숫자가 연달아서 나오는 경우 -> 후위
맨 앞에 연산자가 나오는 경우 -> 전위 */
void evaluation()
{
    infixNumber = 0, prefixNumber = 0, postfixNumber = 0;
    int check = 0, sum = 0;
    //값이 하나만 들어오는 경우 세 가지의 연산을 전부 실행한다. 
    if (newexpr[1] == NULL) {
        int n=0;
        fprintf(stdout, "infix : possible \n");
        fprintf(stdout, "- IN : ");
        while(newexpr[n] != NULL)
            fprintf(stdout, "%s ", newexpr[n++]);
        printf("\n");
        infixToPrefix(newexpr);
        infixToPostfix(newexpr);
        fprintf(stdout, "prefix : possible \n");
        fprintf(stdout, "postfix : possible \n\n");
        fprintf(stdout, "result : %d\n\n", calculation_result);
        return;
    }
    //맨 처음으로 들어온 값이 피연산자인지 연산자인지를 판단하여 중위, 전위, 후위수식을 구분한다.
    check = isValidExpression(newexpr[0]);
    sum += check;
    // fprintf(stdout, "%d\n", sum);
    if (sum == 1)
        prefixNumber = 1;
    else if (sum == 2)
        infixNumber = 1;
    else
    {
        //맨 처음으로 확인이 되지 않는 경우에는 그 다음을 확인하여 구분한다.
        check = isValidExpression(newexpr[1]);
        sum += check;
        // fprintf(stdout, "%d\n", sum);
        if (sum == 4)
            infixNumber = 1;
        else if (sum == 6)
            postfixNumber = 1;
    }
    if (infixNumber == 1)
        infix();
    else if (prefixNumber == 1)
        prefix();
    else if (postfixNumber == 1)
        postfix();
}
/*전위수식일 때*/
void prefix()
{
    int x=0;
    fprintf(stdout, "infix : impossible\n");
    fprintf(stdout, "prefix : possible \n");
    prefixToInfix();
    fprintf(stdout, "- PR : ");
    //fprintf("내가 출력하고 싶은 배열의 크기는 : %d \n", n);
    while (newexpr[x] != NULL)
        fprintf(stdout, "%s ", newexpr[x++]);
    printf("\n");
    infixToPostfix(newPreInfixExpr);
    fprintf(stdout, "postfix : impossible\n\n\n");
    if (calculation_result == -500)
        fprintf(stdout, "result : Arithmetic error(cannot devide by zero)\n\n");
    else
        fprintf(stdout, "result : %d\n\n", calculation_result);
}
/*후위수식일 때*/
void postfix()
{
    int n =0;
    fprintf(stdout, "infix : impossible\n");
    fprintf(stdout, "prefix : impossible\n");
    fprintf(stdout, "postfix : possible\n");
    postfixToInfix();
    infixToPrefix(newPostInfixExpr);
    infixToPostfix(newPostInfixExpr);
    fprintf(stdout, "\n\n");
    if (calculation_result == -500)
        fprintf(stdout, "result : Arithmetic error(cannot devide by zero)\n\n");
    else
        fprintf(stdout, "result : %d\n\n", calculation_result);

}
/*중위수식일 때 */
void infix()
{
    int n=0;
    fprintf(stdout, "infix : possible \n");
    fprintf(stdout, "- IN : ");
    // fprintf(stdout, "%d", n);
    while(newexpr[n] != NULL)
        fprintf(stdout, "%s ", newexpr[n++]);
    printf("\n");
    infixToPrefix(newexpr);
    infixToPostfix(newexpr);
    fprintf(stdout, "prefix : impossible \n");
    fprintf(stdout, "postfix : impossible \n\n\n");
    if (calculation_result == -500)
        fprintf(stdout, "result : Arithmetic error(cannot devide by zero)\n\n");
    else
        fprintf(stdout, "result : %d\n\n", calculation_result);
}
/*중위수식을 전위수식으로 만들어주는 함수*/
void infixToPrefix(char *newexpr[]) {
    char *symbol;
    precedence token, value;
    push(&infix_prefix,  eos);
    for (int i=n; i>0; i--) {
        symbol = newexpr[i-1];
        token = getToken(symbol);
        //피연산자이면 스택에 집어넣기
        if (token == operand) {
            insertDoubleList(symbol);            
        }
        //닫힌괄호가 나오면 무조건 넣기
        else if (token == rparen) {
            push(&infix_prefix, token);
        }
        //열린괄호가 나오면 닫힌 괄호가 나올 때까지 pop하기
        else if (token == lparen) {
            value = infix_prefix -> data;
            while(value != rparen) {
                printDoubleToken(pop(&infix_prefix));
                value = infix_prefix -> data;
            }
            pop(&infix_prefix); //하나 더 꺼내서 닫힌괄호도 꺼낸다. 
        }
        //연산자가 나오면 우선순위에 따라서 pop을 하고 stack에 다시 넣기
        else {
            while(isp[infix_prefix -> data] >= icp[token]){
                printDoubleToken(pop(&infix_prefix));
            }
            push(&infix_prefix, token);
        }
    }
    while ((token = pop(&infix_prefix)) != eos) {
        printDoubleToken(token);
    }
    printf("- PR : ");
    while(newtemp != NULL) {
        fprintf(stdout, "%s ", newtemp ->value);
        newtemp = newtemp -> prev;
    }
    fprintf(stdout, "\n");
}
/*후위수식을 중위수식으로 바꾸기
연산자일경우 스택에 집어넣고, 문자인경우 2개를 pop해서 다시 스택에 집어넣는다.
후위수식에는 괄호가 없으므로 괄호의 경우는 생각하지 않아도 된다. */
void postfixToInfix() {
    char *symbol;
    char *op1, *op2; //두 개를 pop을 했을 때 받아올 수 있는 것
    char *new; //pop을 한 뒤에 새롭게 꺼낼 연산자에서 만들어지는 수식을 받아오는 값을 저장한다.
    char *finalnew = (char *)malloc(sizeof(char) * 100);
    precedence token;
    for (int i=0; i<n; i++) {
        symbol = newexpr[i];
        token = getToken(symbol);
        if (token == operand) {
            infixPush(&postfix_infix, symbol);
        }
        else {
            token = getToken(symbol);
            op2 = infixPop(&postfix_infix);
            op1 = infixPop(&postfix_infix);
            if (i == n-1) {
                new = makeFinalExpression(symbol, op1, op2);   
            }
            else{
                new = makeExpression(symbol, op1, op2);
            }
            infixPush(&postfix_infix, new);
        }
    }

    printf("- IN : %s\n", postfix_infix ->value);
    insertExpression(postfix_infix->value, newPostInfixExpr);
}
/*전위수식을 중위수식으로 바꾸기 => 결과적으로 나온 값을 괄호를 제외하고 다시 저장해놔야한다. */
void prefixToInfix() {
    char *symbol;
    char *op1, *op2;
    char *new;
    char *finalnew = (char *)malloc(sizeof(char));
    precedence token;
    for (int i=n; i>0; i--) {
        symbol = newexpr[i-1];
        token = getToken(symbol);
        if (token == operand) {
            infixPush(&prefix_infix, symbol);
        }
        else {
            token = getToken(symbol);
            op1 = infixPop(&prefix_infix);
            op2 = infixPop(&prefix_infix);
            if (i == 1) {
                new = makeFinalExpression(symbol, op1, op2);
            }
            else {
                new = makeExpression(symbol, op1, op2);
            }
            infixPush(&prefix_infix, new);
        }
    }
    printf("- IN : %s\n", prefix_infix -> value);
    /*받아 온 값을 공백 단위로 구분해서 다시 배열에 넣기*/
    insertExpression(prefix_infix -> value, newPreInfixExpr);
    //for (int i=0; i<n; i++)
     //   printf("제발 잘 되라 : %s\n", newPreInfixExpr[i]);

}
//최종 결과식을 마지막에 뒤에서부터 읽어와야하므로 이중 연결리스트가 필요하다.
//항상 맨 앞의 결과를 가리키고 있는건 prefixFormula 
void insertDoubleList(char *symbol) {
    infixPrefixPointer newNode = (infixPrefixPointer)malloc(sizeof(prefixNode));
    //이중 연결리스트에 아무런 값도 들어오지 않은 상태라면
    if (prefixFormula == NULL) {
        newNode -> value = symbol;
        newNode -> prev = NULL;
        newNode-> next = NULL;
        prefixFormula = newNode;
        newtemp = newNode; 
    }
    else {
        newNode -> value = symbol;
        newNode -> next = NULL;
        newNode -> prev = newtemp;
        newtemp -> next = newNode;
        newtemp = newNode;
    }
}

char * makeExpression(char *symbol, char *op1, char *op2) {
    char *result = (char *)malloc(sizeof(char)*100);
    strcpy(result, "(");
    strcat(result, " ");
    strcat(result, op1);
    strcat(result, " ");
    strcat(result, symbol);
    strcat(result, " ");
    strcat(result, op2);
    strcat(result, " ");
    strcat(result, ")");
    return result;
}
char * makeFinalExpression(char *symbol, char *op1, char *op2) {
    char *result = (char *)malloc(sizeof(char)*100);
    strcpy(result, op1);
    strcat(result, " ");
    strcat(result, symbol);
    strcat(result, " ");
    strcat(result, op2);
    return result;
}
precedence getToken(char *symbol)
{
    switch (*symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '*':
        return times;
    case '/':
        return divide;
    case '%':
        return mod;
    case '^':
        return power;
    case '\0':
        return eos;
    default:
        return operand;
    }
}
//단일 연결리스트로 구현된 식
void insertList(char *symbol)
{
    // printf("%s", symbol);
    stackPointer newtemp = (stackPointer)malloc(sizeof(stack));
    // 처음에 아무런 값도 없었을 때
    if (infix_postfix == NULL)
    {
        newtemp->value = strdup(symbol);
        newtemp->link = NULL;
        infix_postfix = newtemp;
        temp = newtemp;
        infix_postfix -> length = 1;
    }
    else
    {
        newtemp->value = strdup(symbol);
        newtemp->link = NULL;
        temp->link = newtemp;
        temp = newtemp;
        infix_postfix -> length = infix_postfix -> length +1;
    }
    // printf("%s\n", infix_postfix -> value);
}
void printDoubleToken(precedence token) {
    switch (token)
    {
    case 2:
        insertDoubleList("+");
        break;
    case 3:
        insertDoubleList("-");
        break;
    case 4:
        insertDoubleList("*");
        break;
    case 5:
        insertDoubleList("/");
        break;
    case 6:
        insertDoubleList("%");
        break;
    case 7:
        insertDoubleList("^");
        break;
    }
}
void printToken(precedence token)
{
    switch (token)
    {
    case 2:
        insertList("+");
        break;
    case 3:
        insertList("-");
        break;
    case 4:
        insertList("*");
        break;
    case 5:
        insertList("/");
        break;
    case 6:
        insertList("%");
        break;
    case 7:
        insertList("^");
        break;
    }
}
/*중위 수식을 후위수식으로 바꾸는 연산*/
void infixToPostfix(char *newexpr[])
{
    // n에는 총 배열의 크기만큼이 저장되어있다.
    char *symbol;
    int x = 0;
    precedence token, value;
    push(&top, eos); // 여기까지는 잘 push 되어지고 있다.

    for (int i = 0; i < n; i++)
    {
        symbol = newexpr[i];
        token = getToken(symbol);

        if (token == operand) {
            insertList(symbol);
        }
        else if (token == rparen)
        {
            value = top->data;
            while (value != lparen)
            {
                printToken(pop(&top));
                value = top->data;
            }
            pop(&top);
        } 
        else {
            while (isp[top->data] >= icp[token])
            {
                printToken(pop(&top));
            }
            push(&top, token);
        }
    }
    while ((token = pop(&top)) != eos)
    {
        printToken(token);
    }
    //최종적으로 값을 삽입 후에 처음으로 되돌린다. 따라서 infix_postfix는 처음을 가리킨다.
    temp = infix_postfix; 
    fprintf(stdout, "- PO : ");
    while (temp != NULL)
    {
        fprintf(stdout, "%s ", temp->value);
        temp = temp->link;
    }
    temp = infix_postfix;
    fprintf(stdout, "\n");
    calculation_result = postEvaluation();
    //printf("계산 결과는 : %d ", calculation_result);
}
/*후위연산의 값을 계산하는 식
-> 후위연산의 길이만큼 반복해서 값을 얻어온다. 혹은 NULL일 때까지 값을 얻어온다.
연산자인 경우에는 숫자가 들어갈 수 있는 곳에 넣어준다.*/
int postEvaluation() {
    precedence token;
    char *symbol;
    int result=0;
    int op1, op2;
    while(temp != NULL) {
        symbol = temp -> value;
        token = getToken(symbol);
        //printf("token의 값 : %d ",token);
        //하나씩 값을 읽었을 때 피연산자 (숫자) 일 경우
        if (token == operand) {
            result = atoi(symbol); // 실제 정수값으로 변환해준다.
            evalPush(&eval, result);
        }
        //연산자 일 경우 두 개를 pop해서 계산 한 결과를 다시 집어넣는다.
        else {
            op2 = evalPop(&eval);
            op1 = evalPop(&eval);
            switch(token){
                case 2: evalPush(&eval, op1+op2);
                    break;
                case 3: evalPush(&eval, op1 - op2);
                    break;
                case 4: evalPush(&eval, op1 * op2);
                    break;
                case 5:
                    if(op2 == 0)
                         return -500;
                    evalPush(&eval, op1 / op2);
                    break;
                case 6: evalPush(&eval, op1 % op2);
                    break;
                case 7: evalPush(&eval, pow(op1, op2));
            }
        }
        temp = temp -> link;
    }
    return evalPop(&eval);
}

// 명령형 인자로 전달을 받을 때와 그렇지 않을 때를 구분하여 따로 수식을 입력받는다.
int main(int argc, char *argv[])
{
    int check = 0;
    char *token;
    if (argc == 2)
    {
        check = insertExpression(argv[1], newexpr);
        if (check == -1)
            fprintf(stdout, "error : wrong token input\n");
        else {
            evaluation();
        }
    }
    // 명령형 인자로 수식을 받지 않고 따로 입력받을 때의 경우를 저장하는 부분 (공백을 입력할 때 계속 반복되서 돈다.)
    else
    {
        while (1)
        {
            top = NULL, infix_postfix = NULL, infix_prefix=NULL;
            temp = NULL, top_result = NULL, eval = NULL;
            prefixFormula = NULL, postfix_infix = NULL, prefix_infix = NULL;
            //newexpr[0] = '\0';
            *newPreInfixExpr = NULL, *newPostInfixExpr = NULL;
            inputExpression();
            checkExit(expr);
            //맨 처음이 공백이 아닐경우, 즉 공백인 경우에는 계속 루프를 돌린다.
            if (expr[0] != '\n')
            {
                check = insertExpression(expr, newexpr);
                // 수식에 문제가 발생한 경우
                if (check == -1)
                {
                    fprintf(stdout, "error : wrong token input\n");
                    continue;
                }
                // 문제가 발생하지 않은 경우 -> infix, prefix, postfix를 구분하고 바꿔야한다.
                else
                {
                    evaluation();
                    
                }
            }
        }
    }
}
