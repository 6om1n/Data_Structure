#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int N;
    scanf("%d", &N);
    N /=4;
    for (int i=0; i<N; i++) {
        fprintf(stdout, "long ");
    }
    fprintf(stdout, "int");
    return 0;
}