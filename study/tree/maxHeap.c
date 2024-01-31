#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

//하나의 구조체 안에 heap을 만들고, 그 안에서 움직인다.  
typedef struct{
    int heap[MAX_ELEMENT];
    int heapSize;
}heapType;

heapType *createHeap();
void push(heapType *h, int item);
int pop(heapType *h);
void printHeap(heapType *h);

//모든건 heap 포인터에서 처리한다. 왜냐면, heap안에 heap이라는 배열과 길이가 들어있기 때문이다. 
int main(int argc, char* argv[]) {
    int i, n, item;
    heapType *heap = createHeap();
    push(heap, 10);
    push(heap, 45);
    push(heap, 19);
    push(heap, 11);
    push(heap, 96);

    printHeap(heap);
    n = heap->heapSize;
    for (i=1; i<=n; i++){
        item = pop(heap);
        fprintf(stdout, " \n delete: [%d] ", item);
    }
    return 0;
}
heapType *createHeap(){
    heapType *h = (heapType *)malloc(sizeof(heapType));
    h->heapSize=0;
    return h;
}

void push(heapType *h, int item) {
    int i;
    h->heapSize = h->heapSize +1;
    i = h->heapSize;
    while ((i !=1) && (item > h->heap[i/2])) {
        h ->heap[i] = h ->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}
/*삭제할 때, 맨 위의 값을 가지고, 맨 아래의 값을 임시 저장하고, 하나씩 비교하기*/
int pop(heapType *h) {
    int parent, child;
    int item, temp;
    item = h->heap[1]; //루트노드를 가리키게끔 
    temp = h->heap[h->heapSize--]; //마지막 값을 반환하고 개수를 하나 줄여준다.
    parent =1;
    child = 2;
    while (child <= h->heapSize)
    {
        if((child < h->heapSize) && (h->heap[child]) < h->heap[child+1])
            child++;
        if (temp >= h->heap[child])
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp; //임시 저장한 마지막 값을 넣어줘야한다.
    return item;
}
void printHeap(heapType *h){
    fprintf(stdout, "Heap : ");
    for (int i=1; i<= h->heapSize; i++)
        fprintf(stdout, "[%d]  ", h->heap[i]);
}


