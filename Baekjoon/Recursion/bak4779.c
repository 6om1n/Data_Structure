/*백준-재귀, 알고리즘 수업 - 병합 정렬1 
n개의 서로 다른 양의 정수가 저장된 배열 A가 있을 때, 병합 정렬로 배열 A를 오름차순 정렬할 경우
배열 A에 k번째 저장되는 수를 구하자  -> 값이 3 이상일 때 문제가 해결이 안된다. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int cantorian(int, int);
void printCantorian(int);

char *cator_set;

int main (int argc, char *argv[]) {
    int N;
    scanf("%d", &N);
    cator_set = (char *)malloc(sizeof(char) * ((pow(3,N))+3)); // 문자열을 저장할 것을 동적배열로 할당
    int result =pow(3,N);

    for (int i=0; i< result; i++) {
        cator_set[i++] = '-'; 
    }
    cantorian(0, result-1); //인덱스 번호를 넘겨준다. 
    printCantorian (result);

    return 0;

}

int cantorian (int start, int end) {    
    int num = (end - start + 1) / 3;
    
    if (num == 0){
        return 0;
    }

    // 9~17까지 루프 , 3부터 5까지 루프, 1 루프돌기 , 가운데 부분만 0으로 만들기 
    for(int i=start + num; i<= end -num; i++) {
        cator_set[i] =' ';
    }
    //해당하는 종료조건
   
     if(num== 1) {
        return 0;
    }

    cantorian(start, num-1); //앞부분에 관한 부분   
    cantorian(2*num, end); // 뒷부분에 관한 부분
}   

void printCantorian(int result) {
        for (int i=0; i<result; i++)
            printf("%c", cator_set[i]); 
}