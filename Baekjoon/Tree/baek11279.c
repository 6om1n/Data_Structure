/*백준 -최대 힙 11279번 (실버2) */
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100001
typedef struct maxHeap{
    int heap[MAX_ELEMENT];
    int heapSize;
}maxHeap;

maxHeap* createHeap();
void push(maxHeap *, int);
int pop(maxHeap *);
void printHeap(maxHeap*);

int main(int argc, char*argv[]) {
    int N;
    scanf("%d", &N); getchar();
    maxHeap *h = createHeap();
    for (int i=0; i<N; i++) {
        int number;
        scanf ("%d", &number);
        getchar();
        if (number == 0) {
            if (h -> heapSize == 0)
                fprintf(stdout, "0\n");
            else
                fprintf(stdout, "%d\n", pop(h));
        }
        else {
            push(h, number);
        }
       // printHeap(h);
    }
}

maxHeap* createHeap(){
    maxHeap *h = (maxHeap *)malloc(sizeof(maxHeap));
    h -> heapSize = 0;
    return h;
}
/*값을 집어넣을 때, 맨 마지막에 집어넣기 -> 부모의 값이랑 비교하면서 자신의 위치 찾아가기*/
void push(maxHeap *h, int item) {
    h -> heapSize = h-> heapSize +1;
    int i = h -> heapSize;
    while ((i != 1) && (item > h -> heap[i/2])) {
        h -> heap[i] = h -> heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}
//최대힙에서 제일 큰 값을 리턴해주는 함수
int pop(maxHeap *h) {
    int parent, child;
    parent = 1;
    child = 2;
    int item = h-> heap[1];
    int temp = h -> heap[h -> heapSize]; //temp에는 제일 마지막 값을 집어넣는다.
    h -> heapSize = h -> heapSize -1; //값을 하나를 삭제할 것이니까 하나를 뺀다.
    while (child <= h->heapSize) {
        if ((child < h-> heapSize) && h -> heap[child] < h->heap[child+1])
            child++;
        if (temp >= h-> heap[child]) 
            break;
        h -> heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h -> heap[parent] = temp;
    return item;
}
//힙에 제대로 값이 들어가있는지를 확인해주는 함수 (문제풀 때는 필요는 없지만 확인을 위함)
void printHeap(maxHeap *h) {
    fprintf(stdout, "heap: ");
    for (int i=1; i<=h->heapSize; i++){
        fprintf(stdout, "[%d] ", h->heap[i]);
    }
    fprintf(stdout, "\n");
}