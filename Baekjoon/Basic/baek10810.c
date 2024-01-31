/*바구니를 N개 가지고 있고, 바구니와 공에는 번호가 적혀있다. 가장 처음 바구니에는 공이 들어있지 않고
 바구니에는 공을 1개만 넣을 수 있다. 바구니는 연속되어있다. 공이 기존에 것이 있다면 빼고 다시 넣는다.
 공을 어떻게 넣을지 주어졌을 때, M번 공을 넣은 이후 바구니에 어떤 공이 들어있는 지를 구하는 프로그램 작성 */

#include <stdio.h>

int main() {
    int N;
    int M;
    int i,j,k;
    scanf("%d %d", &N, &M);
    getchar();
    //1번부터 공을 가지고 있기 때문에, 값을 출력할 때 +1을 해주어야한다. 
    int array[N];
    for(int i=0; i<N; i++) {
        array[i] =0; }
    //M번의 공을 넣으려고 한다. 
    for (int x=0; x<M; x++) {
        scanf("%d %d %d", &i, &j, &k);
        getchar();
        for (int m=i; m<=j; m++)
            array[m-1]=k;
    }
    for(int i=0; i<N; i++)
        fprintf(stdout, "%d ", array[i]);
}
