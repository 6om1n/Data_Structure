#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int elements[MAX_SIZE];
    int size;
} MinHeap;

MinHeap* createMinHeap();
void swap(int *, int *);
void insert(MinHeap*, int);
int isEmpty(MinHeap*);
int deleteMin(MinHeap*);
void minHeapify (MinHeap* minHeap, int index);

MinHeap* createMinHeap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    return minHeap;
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
//원소를 삽입하는 함수
void insert(MinHeap* minHeap, int item) {
    if (minHeap-> size >= MAX_SIZE) {
        fprintf(stderr, "Priority queue is full. Cannot insert.\n");
        return;
    }
    minHeap -> elements[minHeap -> size++] = item; // 마지막 위치에 자신을 넣어주고
    int current = minHeap -> size -1;
    while (current >0 && (minHeap -> elements[current] < minHeap -> elements[(current -1) / 2]))
    {
        swap(&minHeap-> elements[current], &minHeap-> elements[(current-1) / 2]);
        current = (current - 1) / 2;
    }
}
int isEmpty(MinHeap* minHeap) {
    return minHeap -> size == 0;
}
int deleteMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        fprintf(stderr, "Priority queue is empty. Cannot delete\n");
        exit(EXIT_FAILURE);
    }
    int minItem = minHeap->elements[0]; // 제일 작은 루트의 값을 반환한다.
    minHeap->elements[0] = minHeap->elements[minHeap-> size -1]; //제일 루트자리에 마지막 값을 집어넣는다.
    minHeap->size--; // 루트의 값이 빠질 것이니 사이즈를 하나 줄여준다.
    minHeapify(minHeap,0);
    return minItem;
}
/*힙에서 값을 삭제할 때는 왼쪽 자식과 오른쪽 자식 중에서 더 작은 값이랑 바꾼다.*/
void minHeapify (MinHeap* minHeap, int index) {
    int smallest = index; //루트의 인덱스인 0을 가지고 있음
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    //부모보다 자식의 값이 더 큰 경우, 자식들 중 제일 작은 값과 교환하기 위해서 smallest 값을 갱신한다.
    if (left < minHeap->size && minHeap->elements[left] < minHeap->elements[smallest]) {
        smallest = left;
    }
    if (right < minHeap -> size && minHeap ->elements[right] < minHeap->elements[smallest]) {
        smallest = right;    
    }
    //부모의 값이랑 자식들 중 작은 값이랑 교환한 후 smallest에 대해서 다시 재귀적으로 함수를 불러온다. 
    if (smallest != index) {
        swap(&minHeap->elements[index], &minHeap->elements[smallest]);
        minHeapify(minHeap, smallest);
    }
}
int main() {
    MinHeap* minHeap = createMinHeap();
    insert(minHeap, 10);
    insert(minHeap, 45);
    insert(minHeap, 19);
    insert(minHeap, 11);
    insert(minHeap, 96);
    printf("Deleted elements in ascending order:\n");
    while (!isEmpty(minHeap)) {
        int item = deleteMin(minHeap);
        printf("%d ", item);
    }
    free(minHeap);
    return 0;
}