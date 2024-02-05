/*동적 배열을 이용한 큐의 구현
정적 배열을 이용한 원형 큐와는 다르게 하나의 큐를 남겨놓지 않고 전체 다 채운다.
따라서 용량을 나중에 조절할 때 front부터 하나씩 새로운 배열에 추가해주면 된다. */

#include <stdio.h>
#include <stdlib.h>

//환형 큐의 구조체 정의
typedef struct {
    int *data; //데이터 배열
    int front; // 큐의 앞 포인터
    int rear; // 큐의 뒷 포인터
    int size; // 큐의 현재 크기
    int capacity; //큐의 최대 용량
} CircularQueue;

/*처음에 초기화할 때 data를 용량 * int로 만들어서 최대 용량만큼 가지는 int형 배열을 만든다.*/
CircularQueue* initializeQueue(int capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue -> data = (int *)malloc(capacity * sizeof(int));
    queue -> front = 0;
    queue -> rear = -1;
    queue -> size = 0; // 아직 아무런 값도 들어가지 않음을 나타낸다. 
    queue -> capacity = capacity;
    return queue; 
}
//큐가 비어있는지 확인하는 함수, size가 0이라면 큐가 비어있다고 판단한다.
int isEmpty(CircularQueue* queue) {
    return queue -> size == 0;
}
/*큐가 가득찼는지 확인하는 함수, size가 용량과 같으면 가득찼다고 판단한다.*/
int isFull(CircularQueue* queue) {
    return queue->size == queue-> capacity;
}
/*큐에 원소를 삽입하는 함수*/
void enQueue(CircularQueue* queue, int item) {
    if (isFull(queue)) {
        int newCapacity = queue -> capacity * 2; //용량을 두 배로 늘림
        int *newData = (int *)malloc(newCapacity * sizeof(int));
        int i, j;
        for (i = 0, j = queue->front; i < queue->size; i++) {
            newData[i] = queue ->data[j];
            j = (j + 1) % queue->capacity;
        }
        free(queue -> data); //이전 데이터 배열 해제
        queue -> data = newData; //새로운 데이터 배열을 추가
        queue -> front = 0;
        queue -> rear = queue -> size -1; //rear는 맨 뒤를 가리킴
        queue -> capacity = newCapacity; //용량도 수정
    }
    queue -> rear = (queue -> rear + 1) % queue->capacity;
    queue -> data[queue->rear] = item;
    queue -> size++;
}
/*큐에서 원소를 삭제하고 반환하는 함수 */
int deQueue(CircularQueue* queue) {
    if (isEmpty(queue)){
        printf("큐가 비어 있다. \n");
        return -1; //에러 처리 혹은 다른 방법으로 처리
    }
    int item = queue -> data[queue -> front];
    queue->front = (queue -> front + 1) % queue -> capacity;
    queue -> size--;
    return item;
}
/*큐를 출력하는 함수*/
void displayQueue(CircularQueue* queue) {
    int i, j;
    printf("Queue: ");
    for (i=0, j = queue->front; i < queue->size; i++){
        printf("%d ", queue->data[j]);
        j = (j + 1) % queue->capacity;
    }
    printf("\n");
}
int main() {
    CircularQueue* queue = initializeQueue(5);

    enQueue(queue, 1);
    enQueue(queue, 2);
    enQueue(queue, 3);

    displayQueue(queue);

    deQueue(queue);

    displayQueue(queue);

    
    enQueue(queue, 4);
    enQueue(queue, 5);

    displayQueue(queue);

    enQueue(queue, 6);
    enQueue(queue, 7);
    enQueue(queue, 8);

    displayQueue(queue);
    
    free(queue -> data);
    free(queue);
    return 0;

}
