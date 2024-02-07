#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100001
//전역변수로 선언을 했기 때문에 자동적으로 0의 값이 들어가있음
int stack[MAX_STACK_SIZE];
int top = -1;

void push(int item) {
    stack[++top] = item;
    fprintf(stdout, "+\n");
}
void pop() {
    stack[top--];
    fprintf(stdout, "-\n");
}

/*배열의 값이 제일 큰 수가 아닐 때 까지 계속 반복문을 돌면서 비교한다.*/
int checkNo(int *sequenceArray, int n) { 
    int k = 0, j = 0;
    while (sequenceArray[j] != n) {
        if (sequenceArray[j] > sequenceArray[j+1] + 1)
            return -1;
        j++;
    }
    while (sequenceArray[j] != 0) {
        if (sequenceArray[j+1] < sequenceArray[j+2])
            return -1;
        j++;
    }
    return 1;
}
void deriveResult(int *sequenceArray, int *n) {
    int count = 0;
    int k = 0;
    int j = 0;
    for (int i=0; i<sequenceArray[0]; i++){
        push(++count);
    }
    pop();
    while(sequenceArray[j] != (*n)){
        /*만약 두개 씩 비교를 해서 뒤의 숫자가 더 작은경우에는 pop을 한다.
        뒤에 있는 것이 더 큰 경우는 차이만큼 push해준다. */
            if (sequenceArray[j] > sequenceArray[j+1])
                pop();
            else {
                k = (sequenceArray[j+1] - count);
                for (int i=0; i<k; i++)
                    push(++count);
                pop();                
            }
            j++;   
    }
    while (top != -1) {
        pop();
    }
}
/*맨 처음으로 yes인지와 no를 판별하기 위해 -> 기존 배열을 보면서 판별한다.*/
int main() {
    int n;
    int k =0;
    int result =0;
    scanf("%d", &n);
    getchar();
    int *sequenceArray = ((int *)malloc(sizeof(int) * n));
    for (int i=0; i<n; i++) {
        scanf("%d", &sequenceArray[i]);
        getchar();
    }
    result = checkNo(sequenceArray, n);
    if (result == -1) {
        fprintf(stdout, "NO");
        return 0;
    }
    else {
        deriveResult(sequenceArray, &n);
    }
}