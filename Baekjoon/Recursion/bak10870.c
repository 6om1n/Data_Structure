/*백준 재귀-피보나치 수 5
피보나치 수는 0과 1로 시작한다. 0번째 수는 0이고, 1번째 수는 1이다. 그 다음부터 수는 두 피보나치 수의 합이다.
n이 주어졌을 때 n번째 피보나치 수를 구하는 프로그램을 작성하시오. */

#include <stdio.h>

int fibo(int);

int main(void) {
    int n; // n번째 피보나치의 수
    scanf("%d",&n);
    int result =fibo(n);
    fprintf(stdout, "%d", result);
}

int fibo(int n){
    if (n==0) {
        return 0;
    }
    else if(n==1) {
        return 1;
    }
    else {
        return fibo(n-1)+ fibo(n-2);
    }
}