/*소수 찾기 - 브론즈 2*/
#include <stdio.h>
int checkPrimeNumber(int);

int checkPrimeNumber(int number) {
    if (number == 1)
        return -1;
    for (int i=2; i<number; i++) {
        if (number % i == 0) {
            return -1;
        }
    }
    return 1;
}
int main () {
    int N;
    scanf ("%d", &N);
    int count = 0;
    getchar();
    int array[N];
    for (int i=0; i<N; i++) {
        scanf("%d", &array[i]);
        getchar();
        //printf("%d", array[i]);
        int check = checkPrimeNumber(array[i]);
        if (check == 1) {
            count++;
        }
    }
    fprintf(stdout, "%d", count);
}