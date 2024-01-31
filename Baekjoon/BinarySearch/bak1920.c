//백준 1920번 이분탐색
//이분탐색으로 값을 찾고 있으면 1을 출력, 해당 값이 없으면 0을 출력한다. 
#include <stdio.h>
#include <stdlib.h>

int A[100000];
int B[100000];

int compare (int x, int y) {
    if(x < y)
        return -1;
    else if(x == y)
        return 0;
    else if(x > y)
        return 1;
}

int binSearch(int A[], int searchNum, int left, int right) {
int middle;
while(left <= right) {
    middle = (left+right) / 2;
    switch(compare(A[middle], searchNum)) {
        case -1:
        return binSearch(A, searchNum, middle+1, right);

        case 0:
        return 1;

        case 1:
        return binSearch(A, searchNum, left, middle-1);
    }
}
return 0;

}
//배열을 정렬하는 것이 필요함
int main(int argc, char *argv[]) {
    printf("자연수를 입력하세요 : ");
    int n;
    scanf("%d",&n);
    //값들이 여기 리스트 안에 있는 지 확인하는 것 
    printf("배열에 들어 갈 숫자를 입력하세요 : ");
    for(int i=0; i<n; i++)
        scanf("%d",&A[i]);

    qsort(A,n,sizeof(int), compare); // 정렬하는 것만 해결하면 될 것 같음
    for(int i=0; i<n; i++) {
        fprintf(stdout, "%d ", A[i]);

    }
    int j,m; // 있는지 알아내려는 숫자들 (j=숫자의 총 개수, m= 알아내려는 개)
    printf("찾으려는 숫자의 총 개수를 입력하세요 : ");
    scanf("%d",&j); // 5입력
    //j개의 수가 주어지면 이들이 배열 안에 숫자가 있는지 없는지를 판단한다. 
    for(int i=0; i<j; i++) {
        scanf("%d",&B[i]);
    }

    for(int i=0; i<j; i++){
       fprintf(stdout, "%d\n", binSearch(A, B[i],0, n-1));
    }
    return 0;
}
