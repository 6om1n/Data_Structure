//순환 순열(시간 복잡도 n팩토리얼)
#include <stdio.h>

#define swap(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

//i는 순열 시작, n은 순열의 끝
void perm(char *list, int i, int n){
    int j,temp;
    //순열이 완성되었을 경우
    if(i==n){
        for(j=0; j<=n; j++){
            fprintf(stdout, "%c", list[j]);
        }
        fprintf(stdout, "  ");
    }
    else {
        for(j=i; j<=n; j++){
            swap(list[i], list[j], temp);
            perm(list, i+1, n);
            swap(list[i], list[j], temp);
        }
    }
}

int main (int argc, char * argv[]) {
    char txt[4]={'a','b','c'};
    perm(txt,0,2);
    return 0;
}