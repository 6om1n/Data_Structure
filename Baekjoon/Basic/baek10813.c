#include <stdio.h>
void swap(int *arr, int i, int j) {
    int temp; //임시로 저장 해 둘 변수
    temp = arr[i-1];
    arr[i-1] = arr[j-1];
    arr[j-1] = temp;
}
int main() {
    int N, M;
    int i,j;
    scanf("%d", &N);
    int array[N];
    for(int x=0; x<N; x++) {
        array[x] = x+1;
    }
    scanf("%d", &M);
    getchar();
    for (int x=0; x<M; x++) {
        scanf("%d %d", &i, &j);
        getchar();
        swap(&array,i,j);
    }
    for(int x=0; x<N; x++)
        fprintf(stdout, "%d ", array[x]);
}