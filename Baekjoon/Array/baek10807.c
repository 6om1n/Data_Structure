//정수 v가 몇 개인지 구하는 프로그램
#include <stdio.h>
int main() {
    int N;
    int count =0;
    unsigned int v;
    scanf("%d", &N); 
    getchar();
    int array[N];
    for (int i=0; i<N; i++){
        int data;
        scanf("%d", &data);
        array[i] =data;
        getchar();
    }
    scanf("%u", &v );
    for(int i=0; i<N; i++) {
        if (array[i]==v)
            count++;
    }
    fprintf(stdout, "%d", count);
}