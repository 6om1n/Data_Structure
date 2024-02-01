/*재귀를 이용한 피보나치 수열 -> 첫째 및 둘째 항이 1이고, 그 뒤의 항들은 바로 앞 두 항의 합과 같다.
예를 들어, 1 1 2 3 5 8 13 21 ... 등등 보통 이렇게 나아가야 한다.
이 문제에서는 1 2 3 5 8 13 ... 과 같은 순서로 진행하였고, 들어오는 input값은 반복횟수이다. */
// 재귀 반복문을 이용해야 하는 경우이기 때문에 반드시 종료조건을 선택을 해야하고, 어떤 식으로 흐름이 흘러갈 것인지를 판단해야한다.
//n=10이면, 피보나치 10개의 숫자를 반환해준다. 
#include <stdio.h>


int fibo(int n);

int main(int argc, char *argv[]){
    int input;
    fprintf(stdout, "Input a non-negative integer : ");
    scanf("%d", &input);
    for (int i=0; i<input; i++) {
        fprintf(stdout, "%d ", fibo(i));
    }
    fprintf(stdout, "\n");
    return 0;
}

int fibo(int n){
    if(n==0)
        return 1;
    else if(n==1)
        return 2;
    return fibo(n-1) + fibo(n-2); 
}