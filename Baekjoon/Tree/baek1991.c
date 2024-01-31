/*이진 트리를 입력받아 전위 순회, 중위 순회, 후위 순회한 결과를 출력하는 프로그램을 작성하라
알파벳 순서대로 노드의 이름이 매겨지고, 항상 A가 루트 노드가 된다. 자식 노드가 없는 경우에는 .으로 표현한다.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
    char data;
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

//여기서 생각해야 할 것이, .을 받는경우 NULL의 값으로 처리해야하는 것
//그 다음에는 이미 입력되어진 알파벳이 들어온경우 그 값을 찾아서 왼쪽과 오른쪽을 연결해야한다. 
treeNode * createNode(char node) {
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
    newNode -> data = node;   
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}
void findTree(treeNode * tree, treeNode *new){
    //트리에 아무런 값도 없을 경우 찾을 필요가 없다. 
   if(tree -> left != NULL){
        if(tree->left->data == new->data) {
            free(tree->left);
            tree->left = new;
        }
        else 
            findTree(tree->left, new);
   }
   if (tree->right != NULL) {
        if(tree->right->data == new->data){
            free(tree->right);
            tree->right = new;
        }
        else 
            findTree(tree->right, new);
   }
}
//전위 순회하는 함수(맨 위에 있는 루트를 받아서 )
void preorder(treeNode *tree) {
        fprintf(stdout, "%c", tree->data);
        if (tree->left != NULL)
            preorder(tree->left);
        if (tree->right != NULL)
            preorder(tree->right);
}
//중위 순회하는 함수
void inorder(treeNode *tree) {
    if (tree->left != NULL)
        inorder(tree->left);
    fprintf(stdout, "%c", tree->data);
    if (tree->right != NULL)
        inorder(tree->right);
}
//후위 순회하는 함수
void postorder(treeNode *tree) {
    if(tree->left != NULL)
        postorder(tree->left);
    if(tree->right != NULL)
        postorder(tree->right);
    fprintf(stdout, "%c", tree->data);
}
int main(int argc, char *argv[]) {
    int N; //이진 트리의 개수
    scanf("%d", &N); getchar();
    char node, left, right;
    scanf("%c %c %c", &node, &left, &right);
    getchar();

    treeNode *tree = createNode(node);
    if (left != '.'){
        treeNode *leftNode = createNode(left);
        tree -> left = leftNode;
    }
    if (right != '.') {
        treeNode *rightNode = createNode(right);
        tree -> right = rightNode;
    }
  
    //본인, 왼쪽노드, 오른쪽노드 이렇게 3개의 값을 입력받아야한다. 
    for (int i=1; i<N; i++) {
        scanf("%c %c %c", &node, &left, &right);
        getchar();
        treeNode *new = createNode(node);
        if(left != '.') {
            treeNode *leftNode = createNode(left);
            new -> left = leftNode;
        }
        if(right != '.'){
            treeNode *rightNode = createNode(right);
            new -> right = rightNode;
        }
        
        findTree(tree, new);
    }
    preorder(tree); //맨 위의 tree를 넘겨주고, 전위 순회
    printf("\n");
    inorder(tree); //중위 순회
    printf("\n");
    postorder(tree); //후위 순회
}


