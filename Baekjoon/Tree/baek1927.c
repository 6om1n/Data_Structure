//백준 - 최소힙

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100001

typedef struct treeNode {
    int heap[MAX_ELEMENT];
    int heapSize;
}treeNode;

treeNode* createNode();
int pop(treeNode *);
void push(treeNode*, int);
void printHeap(treeNode *);

int main(int argc, char* argv[]) {
    treeNode *h = createNode();
    int N;
    scanf("%d", &N); getchar();
    for (int i=0; i< N; i++) {
        int number;
        scanf("%d", &number); getchar();
        if (number ==0) {
            if (h -> heapSize ==0)
                fprintf(stdout, "0\n");
            else
                fprintf(stdout, "%d\n" ,pop(h));
        }
        else {
            push(h, number);
        }
        //printHeap(h);
    }
}

treeNode* createNode() {
    treeNode* root = (treeNode *)malloc(sizeof(treeNode));
    root -> heapSize = 0;
    return root;    
}

//제일 작은 값을 출력시킨다.
int pop(treeNode *h) {
    int parent, child;
    parent = 1;
    child = 2;
    int item = h->heap[1]; //제일 작은 값 : 리턴시키고 싶은 값
    int temp = h->heap[h->heapSize]; //제일 마지막 값
    h -> heapSize = h -> heapSize -1;
    while (child <= h -> heapSize) {
        if ((child < h -> heapSize) && h->heap[child] > h ->heap[child+1])
            child++;
        if (temp < h->heap[child])
            break;
        h -> heap[parent] = h ->heap[child];
        parent = child;
        child *= 2;
    }
    h -> heap[parent] = temp; 
    return item;
}
//새로운 값이 들어올 떄 가장 작은 값이 부모의 값으로 가게끔 함수를 구현한다.
void push(treeNode *h, int item) {
    h -> heapSize = h -> heapSize +1;
    int i = h -> heapSize;
    while ((i != 1) && (item < h->heap[i/2])) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h-> heap[i] = item;
}

void printHeap(treeNode *h){
    fprintf(stdout, "heap : ");
    for (int i=1; i<=h->heapSize; i++)
        fprintf(stdout, "[%d] ", h->heap[i]);
    fprintf(stdout, "\n");
}