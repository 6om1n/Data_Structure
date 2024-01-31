//백준 9012번 문제 (스택)
/*회고 : 나는 이걸 2차원 배열로 문제를 풀고 동적배열을 사용하였지만, 1차원 배열만으로도 문제를 쉽게 풀 수 있었던 것 같다.
굳이 여러개의 배열에다가 다 내용을 담지 않고 하나의 배열에 계속 scanf로 입력받으면서 하는 방법이 있는 것 같음*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

int *result; // result 동적할당해주기
/*result의 값이 1이면 yes를, -1이면 no를 출력하도록 한다. */

/*복잡하게 생각하지 말고, 단순히 stack을 이용할 수 있는 char형을 하나 만들고, 
문자열 입력받는 것도 char형으로 받아서 stack 자료구조의 형식만 이용하면 될 것 같다. */

char stack[50];
int top = -1;
int capacity = 1;


//true는 1, false는 0을 반환한다.
int isEmpty(){
    if(top == -1){
        return true;
    }
    else{
        return false;
    }
}

//집어넣을 때 꽉 차있는 경우를 예외처리로
void push(char c) {
    stack[++top] = c;
}
char pop(int i) {
        return stack[top--]; // 스택에서 괄호의 값을 삭제하기
}

int main(void) {
int testcase;
scanf("%d", &testcase); // testcase에 해당하는 정수 입력받기
result = (int *)malloc(sizeof(int) * testcase);
//마지막 괄호 연산의 값을 1이랑 0의 값으로만 정하고, 나중에 1이면 yes, 0이면 no를 출력
while(getchar() != '\n'); // 버퍼 비우기
char **arr; //2차원 배열을 동적으로 생성
arr = (char **) malloc(sizeof(char *)*testcase);
//지금 이걸 아예 입력을 못받고 있는 상태인 것 같음

for (int i=0; i<testcase; i++) {
    int maxLength = 50; // 최대 문자열의 길이를 50으로 둔다고 했으
       arr[i] = (char *)malloc(sizeof(char) * maxLength);
        scanf("%s", arr[i]); // 민약 괄호의 값을 만난다면 다음으로 넘어가기
    //입력버퍼 지우기
}

//하나하나씩 arr[i][j]를 사용해서 비교해야할 것 같
//2중 for문을 사용해야 될 것 같음, 열린괄호일 때 집어넣고, 닫힌괄호일 때 꺼내는 방식으로 짝을 맞춘다. 
for(int i=0; i< testcase; i++) {
    for(int j=0; j<strlen(arr[i]); j++){
        if(arr[i][j]==('(')) {
            push('(');
        }
        else if (arr[i][j] == (')')) {
            if(isEmpty()){
                result[i] = -1;
                break;
            }
            pop(i);
            }
    }
    if(result[i] != -1 ) {
        if(!isEmpty()) {
            result[i] = -1;
        }
        else {
            result[i] = 1;
        }
    }
    top = -1; // stack을 사용하고 나서 초기화해주어야함
}

for(int i=0; i< testcase; i++) {
    if(result[i] ==1){
        fprintf(stdout, "YES\n");
    } 
    else if (result[i] ==-1){
        fprintf(stdout, "NO\n");
    }
} 
}

