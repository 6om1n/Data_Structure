/*하노이탑에 대한 조건. a,b,c가 있을 때 a에서 c로 전부 옮긴다. b는 임시의 축을 나타낸다. 
1. 한 번에 하나의 원판만 움직일 수 있다. 
2. 작은 원판 위에 큰 원판이 올라갈 수 없다. 
3. 멘 위에 있는 원판만 움직일 수 있다. */

#include <stdio.h>
void hanoi(int n, char from, char temp, char to){
    //재귀의 종료조건 : 원판이 하나밖에 없을 경우 원하는 위치로 바로 이동시켜주면 된다.
    if(n==1) {
        printf("1번 원판을 %c축에서 %c축으로 옮긴다.\n", from, to);
    }
    else {
        hanoi(n-1, from, to, temp); //가장 큰 원판을 제외하고 나머지를 a->b로 옮긴다.
        printf("%d번 원판을 %c축에서 %c축으로 옮긴다.\n", n, from, to); //n번째 원판을 처음 위치에서 이동시키고 싶은 위치로 옮긴다.
        hanoi(n-1, temp, from, to); //n-1개의 원판을 다시 b->c로 위치를 옮긴다. 
    }
}

int main(void){
    int n;
    printf("원반의 개수를 입력하시오 : ");
    scanf("%d", &n);
    hanoi(n, 'A','B','C'); //원판은 A,B,C 이렇게 총 3개로 움직인다. 
}