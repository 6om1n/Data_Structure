/*정수를 저장하는 스택을 구현 
출력을 요구하는 명령이 주어질 때마다 결과를 한 줄에 하나씩 출력한다. 
* ->시간 초과 문제가 자주 발생했음 -> 여러 개의 함수를 사용하고, 배열로 값을 저장해서 넣어서 그런 것 같다. /

#include <stdio.h>
/*1번 명령어 : push
2번 명령어 : pop (정수를 빼고 출력한다. 없으면 -1을 대신 출력한다.)
3번 명령어 : 스택에 들어있는 개수 출력 -> top을 잘 활용
4번 명령어 : empty (비어있으면 1, 아니면 0을 출력)
5번 명령어 : peek 스택에 정수가 있다면 맨 위의 정수를 출력, 없으면 -1을 출력

*/
#include <stdio.h>
#include <stdlib.h>
int top = -1;

int *stack;

//1번 명령어
void push(int item){
    stack[++top] = item;
}

//2번 명령어
int pop() {
    if(top ==-1){
        return -1;
    }
    else {
        return stack[top--];
    }
}

int main(int argc, char *argv[]) {
    int N, number, item;
    scanf("%d",&N);
    stack = (int *)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++) {
        scanf("%d",&number);
        switch(number) {
            case 1:
                scanf("%d", &item); // push일 경우에는 집어넣을 숫자를 받고 넣는다.
                push(item);
                break;
            case 2:
                printf("%d\n", pop());
                break;
            case 3:
                printf("%d\n", top+1);
                break;
            case 4: {
                if (top == -1){
                    printf("1\n");
                }
                else {
                    printf("0\n");
                }
                break;
            }
            case 5: {
                if(top == -1)
                    printf("-1\n");
                else {
                    printf("%d\n", stack[top]);
                    }
                break;
            }
        } 
    }
}

