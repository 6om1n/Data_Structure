//백준 - 11286번 절댓값 힙

//push는 절댓값에 따라서 값이 잘 들어간다. pop하는 문제만 해결하면 될듯
#include <stdio.h>
#include <stdlib.h> //여기에 절댓값 함수도 들어있음

#define MAX_ELEMENT 100001

/*아예 구조체 배열을 만들어서 실제 데이터 값이랑 숫자를 셀 수 있는 거랑 같이 두기*/
typedef struct array {
    int data; // 실제의 값을 저장하고 있음
    int absolute_value; // 실제 그 수의 절댓값을 저장하고 있음
} arrayNode; 

typedef struct treeNode {
    arrayNode heap[MAX_ELEMENT];
    int heapSize;
} treeNode;

treeNode * createHeap();
int pop (treeNode *h);
void push(treeNode *h, int item);
void printHeap(treeNode *h);

int main (int argc, char *argv[]) {
    int N;
    treeNode *h = createHeap();
    scanf("%d", &N); getchar();
    for (int i=0; i<N; i++) {
        int number;
        scanf("%d", &number); getchar();
        if (number == 0) {
            if (h -> heapSize == 0)
                fprintf(stdout, "출력되는 값은 : 0\n");
            else   
                fprintf(stdout, "출력되는 값은 : %d\n", pop(h));
        }
        else {
            push(h, number);
        }
        printHeap(h);
    }
}

void push(treeNode *h, int item) {
    h->heapSize = h -> heapSize + 1;
    int i = h -> heapSize;
    while ((i != 1) && abs(item) < h->heap[i/2].absolute_value) {
       h->heap[i].data = h->heap[i/2].data;
       h->heap[i].absolute_value = h->heap[i/2].absolute_value;
       i /= 2;
    }
    h -> heap[i].data = item;
    h -> heap[i].absolute_value = abs(item); 
}
int pop (treeNode *h) {
    int parent, child;
    parent = 1;
    child = 2;
    int item = h->heap[1].data; //우선 제일 위의 값을 가지고 있다.
    int temp_abs = h -> heap[h->heapSize].absolute_value; //우선 제일 마지막 절댓값을 가지고 있다.
    int temp_value = h->heap[h->heapSize].data; //마지막 실제값을 가지고 있다. 
    h -> heapSize = h -> heapSize -1;
    int i=2;
    //제일 마지막에 가지고 있는 값이 양수인데 음수가 있을 경우
    if (item > 0) {
        while (h->heap[i].absolute_value <= abs(item)) {
            if (h->heap[i].data < 0) {
            item = h->heap[i].data;
             h->heap[i].data = abs(item);
            }
            i++;
        }
    }
    while (child <= h -> heapSize) {
        if ((child < h->heapSize) && (h->heap[child].absolute_value > h->heap[child+1].absolute_value))
            child++;
        if (temp_abs <= h->heap[child].absolute_value)
            break;

        h->heap[parent].absolute_value = h->heap[child].absolute_value;
        h->heap[parent].data = h->heap[child].data;
        parent = child;
        child *= 2;
    }
    h->heap[parent].data = temp_abs;
    return item;
}
//힙을 초기화한다.
treeNode * createHeap() {
    treeNode *root = (treeNode *)malloc(sizeof(treeNode));
    root -> heapSize =0;
    return root;
}
void printHeap(treeNode *h) {
    fprintf(stdout, "heap: ");
    for (int i=1; i<=h->heapSize; i++){
        fprintf(stdout, "([%d] [%d])   ", h->heap[i].data, h->heap[i].absolute_value);
    }
    fprintf(stdout, "\n");
}
