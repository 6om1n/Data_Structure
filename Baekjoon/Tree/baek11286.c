//백준 - 11286번 절댓값 힙

#include <stdio.h>
#include <stdlib.h> //여기에서 abs함수를 활용한다.

#define MAX_ELEMENT 100001

int resultArray[MAX_ELEMENT]; //마지막 출력 결과값을 담고 있는 배열

/*값을 저장하고 있는 구조체*/
typedef struct array {
    int data;
} arrayNode; 

typedef struct treeNode {
    arrayNode heap[MAX_ELEMENT];
    int heapSize;
} treeNode;

treeNode * createHeap();
int pop (treeNode *h);
void push(treeNode *h, int item);
void printHeap(treeNode *h);
void printResult(int);

int main (int argc, char *argv[]) {
    int N;
    int count = 0;
    treeNode *h = createHeap();
    scanf("%d", &N); getchar();
    for (int i=0; i<N; i++) {
        int number;
        scanf("%d", &number); getchar();
        if (number == 0) {
            if (h -> heapSize == 0)
                resultArray[count++] = 0;
            else   
                resultArray[count++] = pop(h);
        }
        else {
            push(h, number);
        }
        //printHeap(h);
    }
    printResult(count);
}
/*push할 때, 새로 들어오는 값의 절댓값이 부모의 절댓값보다 작거나 같은 경우 구조조정이 필요하다.
만약, 절댓값이 같은데 새로 들어오는 값이 더 크다면, 구조조정이 필요없기에 반복문을 벗어난다.
하지만 절댓값이 같은데 새로 들어오는 값이 더 작다면, 부모의 위치와 바꾼다. -> 구조조정이 필요하다. */
void push(treeNode *h, int item) {
    h->heapSize = h -> heapSize + 1;
    int i = h -> heapSize;
    while ((i != 1) && abs(item) <= abs(h->heap[i/2].data)) {
        if ((abs(item) == abs(h->heap[i/2].data)) && item > h->heap[i/2].data)
            break;
       h->heap[i].data = h->heap[i/2].data;
       i /= 2;
    }
    h -> heap[i].data = item;
}
/*push함수로 인해 루트에는 절댓값이 제일 작고, 실제값도 제일 작은 값이 들어가있다.
삭제할 때는 맨 위의 값을 받아, 리턴해주고, 맨 마지막 값을 루트 위치로 올려서 자식의 값과 비교한다.
왼쪽 자식과 오른쪽 자식 중에서 절댓값이 더 작은 값과 비교해주고, 같은 경우에는 실제 값이 더 작은 값과 비교해준다.
비교하다가 부모의 값(=위치상으로는 temp)이 자식의 절댓값보다 작게 되면 while문을 벗어나게되고,
절댓값이 같고, 부모의 실제 값이 자식 값보다 작은 경우 벗어나게된다.
그렇지 않은 경우 아래로 내려가면서 다시 비교하며, 구조조정을 한다. */
int pop (treeNode *h) {
    int parent, child;
    parent = 1;
    child = 2;
    int item = h->heap[1].data; //우선 제일 위의 값을 가지고 있다.
    int temp = h->heap[h->heapSize].data; //마지막 실제값을 가지고 있다. 
   
    int i = 2;
    h -> heapSize = h -> heapSize -1;
    while (child <= h -> heapSize) {
        if ((child < h->heapSize) && abs(h->heap[child].data) > abs(h->heap[child+1].data))
            child++;
        else if ((child < h->heapSize) && abs(h->heap[child].data) == abs(h->heap[child+1].data)
        && h->heap[child].data > h->heap[child+1].data)
            child++;
        
        if (abs(temp) < abs(h->heap[child].data))
            break;
        else if ((abs(temp) == abs(h->heap[child].data)) && (temp < h->heap[child].data))
            break;

        h->heap[parent].data = h->heap[child].data;
        parent = child;
        child *= 2;
    }
    h->heap[parent].data = temp;
    return item; //삭제하려는 실제 값
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
        fprintf(stdout, "([%d])   ", h->heap[i].data);
    }
    fprintf(stdout, "\n");
} 
void printResult(int count) {
     for (int i=0; i<count; i++) {
        fprintf(stdout, "%d\n", resultArray[i]);
     }
}
