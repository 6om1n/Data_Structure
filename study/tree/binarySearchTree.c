/*이진 탐색 트리를 이용한 우선순위 큐 구현
이진탐색트리는 루트보다 작은 값이 왼쪽, 큰 값이 오른쪽에 넣는 방법이고
inorder로 검색하면 오름차순으로 출력할 수 있다. */

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} treeNode;

typedef struct {
    treeNode* root;
} priorityQueue;

treeNode* createNode (int data) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
priorityQueue* createPriorityQueue() {
    priorityQueue* pq = (priorityQueue*)malloc(sizeof(priorityQueue));
    pq -> root = NULL;
    return pq;
}
treeNode* insert(treeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data > root -> data) {
        root -> right = insert(root->right, data);
    } else {
        root -> left = insert(root->left, data);
    }
}
void enqueue(priorityQueue* pq, int data) {
    pq -> root = insert(pq->root, data);
}
//가장 큰 원소를 찾아서 삭제한다. 
int dequeue(priorityQueue* pq) {
    treeNode* current = pq -> root;
    treeNode* parent = NULL;
    if (current == NULL) {
        fprintf(stderr, "Queue is empty. Cannot dequeue. \n");
        exit (EXIT_FAILURE);
    }
    //가장 오른쪽에 있는 값이 제일 크니까 오른쪽으로만 이동한다
    while (current -> right != NULL) {
        parent = current;
        current = current -> right;
    }
    int maxItem = current->data;
    //제일 큰 값에 왼쪽에 있는 값이나, 널 값을 부모의 오른쪽에 옮긴다. 
    if (parent != NULL) {
        parent -> right = current -> left;
    } else {
        pq -> root = current -> left;
    }
    free(current);
    return maxItem;
}
void inorder(treeNode* root) {
    if (root != NULL) {
        inorder(root->left);
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
    printf("Inorder traversal (ascending order:) \n");
    inorder(pq -> root);
    printf("\nDequeue elements in descending order:\n");
    while (pq -> root != NULL) {
        int item = dequeue(pq);
        printf("%d ",item);
    }
    free(pq);
    return 0;
}