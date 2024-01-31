//이진 탐색 (시간 복잡도 = 로그 n)
//주의할 점 : 리스트 배열이 정렬이 되어있는 상태에서 이진 탐색을 사용해야한다. 
#include <stdio.h>

int compare(int x, int y){
    if(x < y)
        return -1;
    else if (x == y)
        return 0;
    else
        return 1;
}

int binSearch(int list[], int searchNum, int left, int right){
    int middle;
    while(left <= right){
        middle = (left + right) /2;
        switch(compare(list[middle], searchNum)){
            case -1:
                return binSearch(list, searchNum, middle+1, right);
            case 0:
                return middle;
            case 1:
                return binSearch(list, searchNum, left, middle-1);
        }
    }
}

int main(int argc, char* argv[]){
    int list[10]={1,5,8,11,15,20,27,33,50,100};
    fprintf(stdout, "%d", binSearch(list, 33, 0,9));

    return 0;
}