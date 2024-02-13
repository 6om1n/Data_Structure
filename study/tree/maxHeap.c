#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct {
    int heap[MAX_ELEMENT];
    int heapSize; //현재 힘의 크기
} heapType;

heapType *createHeap();
void push(heapType *h, int item);
int pop(heapType *h);
void printHeap(heapType *h);

int main(int argc, char *argv[]) {
    int i, n, item;
    heapType *heap = createHeap(); //여기 구조체 안에서 힙을 관리한다.

    push(heap, 10);
    push(heap, 45);
    push(heap, 19);
    push(heap, 11);
    push(heap, 96);

    printHeap(heap);
    n = heap -> heapSize;

    for (i = 1; i<=n; i++) {
        item = pop(heap);
        fprintf(stdout, " \n delete : [%d] ", item);
    }
    return 0;
}
heapType *createHeap() {
    heapType *h = (heapType *)malloc(sizeof(heapType));
    h -> heapSize =0; //크기는 0으로 초기화한다.
    return h;
}
void push(heapType *h, int item) {
    int i;
    h -> heapSize = h -> heapSize +1; // 루트 인덱스인 1부터 값을 집어넣는다.
    i = h -> heapSize; //들어오려는 힙의 인덱스에 해당한다.
    // 루트가 아닐 때까지 while문을 반복시킨다.
    while ((i !=1) && item > h -> heap[i/2]) {
        h->heap[i] = h->heap[i/2]; //부모의 값을 현재 자신의 위치에 대입을 시키고
        i/=2; //자신의 위치는 부모의 위치로 올라간다.
    }
    h -> heap[i] = item;
}

int pop(heapType *h) {
    int parent, child;
    int item, temp;
    item = h -> heap[1]; //루트 노드의 값을 item에 저장해놓는다
    temp = h->heap[h->heapSize]; //마지막 노드의 값을 temp에 저장해놓는다
    h -> heapSize = h -> heapSize -1; //최종적으로 하나의 값을 제외시킬 것이기 때문에 빼놓는다.
    parent = 1; //처음에는 루트노드를 가리킨다.
    child = 2; // 그 다음 루트노드의 왼쪽자식을 가리킨다.
    
    while (child <= h-> heapSize) {
        if ((child < h-> heapSize) && (h-> heap[child]) <(h->heap[child+1]))
            child++; //더 큰 값을 갖는 자식의 값으로 변경한다.
        //temp가 맨 위에 루트의 자리에 있다고 생각을 하고, child보다 크다면 최대힙이 완성이 된 것이므로 함수를 종료시킨다.
        if (temp >= h->heap[child])
            break;
        h -> heap[parent] = h->heap[child];
        parent = child;
        child = child *2;
    }
    h -> heap[parent] = temp;
    return item; //어떤 값을 삭제하는지를 리턴해준다.
}

void printHeap(heapType *h) {
    int i;
    fprintf(stdout, " Heap : ");
    for (i =1; i<=h->heapSize; i++)
        fprintf(stdout, " [%d] ", h->heap[i]);
}