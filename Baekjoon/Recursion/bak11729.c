//백준 11729번 문제. (재귀) 하노이탑
/*세 개의 장대가 존재하고, 크기가 다른 n개의 원판이 쌓여 있다. 여기에 필요한 순서를 출력하는 프로그램을 작성하라
-> 이동횟수는 최소가 되어야한다. 
이 문제는 원판의 개수가 20개 이하로 주어져있기 때문에 자료형에 상관없이 문제가 풀린다. */
#include <stdio.h>
#include <math.h>

int hanoi(int N, int from, int temp, int to){

    //옮길 원판의 개수가 1개라면 -> 재귀의 종료 조건이 된다. 
    if(N==1) {
        printf("%d %d\n", from,to);
    }
    else {
        hanoi(N-1, from, to, temp); // 임시 장대에 넣는다.  
        printf("%d %d\n", from, to); //n번째로 큰 원판을 옮겨야 할 위체에 넣는다. 
        hanoi(N-1, temp, from,to); // 나머지 원판들을 원래 위치로 옮긴다. 
    }
}

int main(int argc, char *argv[]) {
    int N, j; //원판의 개수
    scanf("%d", &N);
    int count = pow(2,N)-1;
    printf("%d\n", count);
    hanoi(N, 1,2,3);
}