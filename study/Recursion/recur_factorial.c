#include <stdio.h>

int factorial(int n){
    if ( n==0 || n==1 )
        return 1;
    else {
        return n * factorial(n-1);
    }
}

//입력조건을 보니 0이랑 1은 입력받는다. 
int main() {
    int num;
    printf("Input a non-negative integer : ");
    scanf("%d",&num);
    if(num < 0 ) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        printf("Factorial of %d = %d\n", num, factorial(num));
    }
    return 0;
}