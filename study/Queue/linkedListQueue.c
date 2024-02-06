/* 연결리스트 기반의 큐를 구현 */

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct queueNode {
    element item;
    struct queueNode *link;
} queueNode;

/*front와 rear는 큐노드 타입의 구조체를 가리키고 있는 포인터 변수이다. */
typedef struct {
    queueNode *front;
    queueNode *rear;
} queueType;

void error(char *message);
void init(queueType *q);
int queueEmpty(queueType *q);
void addQueue(queueType *q, element item);
element deleteQueue(queueType *q);
element peek(queueType *q);

int main(int argc, char *argv[]) {
    queueType q; //여기에는 front와 rear가 있음
    init(&q); //front와 rear를 다 초기화한다. 
    addQueue(&q,1);
    addQueue(&q,2);
    addQueue(&q,3);
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));

    return 0;
}
/*에러를 나타내는 함수*/
void error(char *message){
    fprintf(stderr, "%s\n, message");
    exit(1);
}
/*큐노드를 초기화하는 함수*/
void init(queueType *q) {
    q -> front = q-> rear = NULL;
}
/*큐가 비어있는지 아닌지를 확인하는 함수*/
int queueEmpty(queueType *q) {
    return (q -> front == NULL);
}
/*큐가 비어있는 상태라면 front와 rear를 다 처음 값으로 설정해주고, 
하나라도 노드가 들어와있는 상태라면 rear의 값을 변경해주고, rear를 마지막 노드로 변경해준다.*/
void addQueue(queueType *q, element item) {
    queueNode *temp = (queueNode *)malloc(sizeof(queueNode));
    if (temp == NULL)
        error("메모리를 할당할 수 없습니다. ");
    else {
        temp -> item = item;
        temp -> link = NULL; //새로 만든 것 뒤에는 NULL로 초기화시켜야함
        /*아직 큐에 아무런 값도 들어오지 않은 상태*/
        if (queueEmpty(q)) {
            q -> front = temp;
            q -> rear = temp;
        }
        else {
            q -> rear -> link = temp;
            q -> rear = temp;
        }
    }
}
element deleteQueue(queueType *q) {
    queueNode *temp = q -> front; //제일 첫번째 원소를 반환한다.
    element item;
    if (queueEmpty(q))
        error("큐가 비어 있습니다. ");
    item = temp -> item; //삭제할 노드의 값을 받아온다.
    q -> front = q -> front -> link; //front의 값을 그 다음 노드로 변경해준다.
    //값이 하나밖에 없었는데 그걸 삭제한 경우
    if (q -> front == NULL)
        q -> rear = NULL; // 맨 마지막 값도 없다는 것을 의미한다. 
    free(temp);
    return item; //삭제하려는 값을 반환한다. 
}
