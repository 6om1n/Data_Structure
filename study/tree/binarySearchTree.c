/*이진 탐색 트리를 이용한 우선순위 큐 구현
이진탐색트리는 루트보다 작은 값이 왼쪽, 큰 값이 오른쪽에 넣는 방법이고
inorder로 검색하면 오름차순으로 출력할 수 있다. */
#include <stdio.h>
#include <stdlib.h>

//이진 탐색 트리 노드 구조체
typedef struct TreeNode {
    int data; 
    struct TreeNode *left;
    struct TreeNode *right;
} treeNode;

//이진 탐색 트리 구조체
typedef struct {
    treeNode* root;
} priorityQueue;

//우선순위 큐 생성 함수
priorityQueue* createPriorityQueue() {
    priorityQueue* pq = (priorityQueue*)malloc(sizeof(priorityQueue));
    pq -> root = NULL; //우선 생성될 때는 아무런 값도 가지고 있지 않는다.
    return pq;
}
//노드 생성 함수
treeNode* createNode(int data) {
    treeNode* newNode = (treeNode *)malloc(sizeof(treeNode));
    newNode -> data = data;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}
//노드 삽입 함수 (재귀적)
treeNode* insert(treeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data > root -> data) { 
        root -> right = insert(root -> right, data);
    } else {
        root -> left = insert(root->left, data);
    }
}
void enqueue(priorityQueue* pq, int data) {
    pq -> root = insert(pq -> root, data);
}
/*삭제할 때는 내림차순으로 출략, 제일 큰 값부터 찾을 수 있도록*/
int dequeue(priorityQueue* pq) {
    treeNode *current = pq -> root;
    treeNode *parent = NULL;
    /*삭제하려는 값이 없을 경우 예외처리*/
    if (current == NULL) {
        fprintf(stdout, "Queue is empty. Cannot dequeue. \n");
        exit(EXIT_FAILURE);
    }
    while (current->right != NULL) {
        parent = current;
        current = current -> right;
    }
    int maxItem =  current -> data;
    if (parent != NULL) {
        parent-> right = current -> left;
    }
    else {
        pq -> root = current -> left;
    }
    free(current);
    return maxItem;

}
void inorder (treeNode* root) {
    if (root != NULL) {
        inorder(root -> left);
        printf("%d ", root -> data);
        inorder(root -> right);
    }
}
int main() {
    priorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10);
    enqueue(pq, 45);
    enqueue(pq, 19);
    enqueue(pq, 11);
    enqueue(pq, 96);
    printf("Inorder traversal (ascending order): \n");
    inorder(pq -> root);
    printf("\nDequeue elements in descending order : \n");
    while (pq -> root != NULL) {
        int item = dequeue(pq);
        printf("%d ", item);
    }
    free(pq);
    return 0;
}