//재귀 - 팩토리얼
#include <stdio.h>

long long int factorial(int n){
    if(n==0 || n==1) {
        return 1;
    }
    else{
        return n * factorial(n-1);
    }
}
int main(void) {
    int N;
    scanf("%d",&N);
    printf("%ld", factorial(N));
    
}
