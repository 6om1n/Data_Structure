#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//puts(#x)는 x로 받은 값을 문자열로 그대로 출력하고, 그 다음 x를 입력받은대로 실행시킨다. 
#define noisy(x) (puts(#x),x);
//start부터 stop-1까지 반복문을 이용하여 출력하기
void printRangeIterative(int start, int stop){
    for(int i=start; i<stop; i++){
        printf("%d\n", i);
    }
}
//자기 자신을 먼저 출력한 후 1씩 큰 걸 재귀적으로 호출하면서 값을 출력함
void printRangeRecursive(int start, int stop){
    if (start < stop) {
        printf("%d\n", start);
        printRangeRecursive(start+1, stop);
    }
}
/*위에 구문이랑은 다르게 print구문의 위치를 재귀함수랑 바꾸었다. 
위의 식에서 start에 1씩 증가시킨 후에 if문을 만족시키면서 빠져나와 start가 역순으로 증가된다. */
void printRangeRecursiveReversed(int start, int stop){
   if (start < stop){
    printRangeRecursiveReversed(start+1, stop);
    printf("%d\n", start); 

   }
}

//반으로 쪼개서 재귀를 이용하여 출력한다. 
void printRangeRecursiveSplit(int start, int stop){
   int mid; //중간값에 해당하는 변수를 선언한다.
   if(start < stop) {
    mid = (start + stop) /2;
    printRangeRecursiveSplit(start, mid);
    printf("%d\n", mid);
    printRangeRecursiveReversed(mid+1, stop); //중간값 이후에 대해서도 값을 출력해야한다. 
   }
}

int main(int argc, char *argv[]) {
    noisy(printRangeIterative(0,10));
    noisy(printRangeRecursive(0,10));
    noisy(printRangeRecursiveReversed(0,10));
    noisy(printRangeRecursiveSplit(0,10));
}
