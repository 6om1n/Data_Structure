#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
    char data;
    struct treeNode *leftNode;
    struct treeNode *rightNode;
}treeNode;

treeNode *makeRootNode (char ,treeNode*, treeNode*);
void preorder(treeNode *);
void inorder(treeNode *);
void postorder(treeNode *);

int main (int argc, char *argv[]){
    treeNode *n7= makeRootNode('D', NULL, NULL);
    treeNode *n6 = makeRootNode('C', NULL, NULL);
    treeNode *n5 = makeRootNode('B', NULL, NULL);
    treeNode *n4 = makeRootNode('A', NULL, NULL);
    treeNode *n3 = makeRootNode('/', n6, n7);
    treeNode *n2 = makeRootNode('*', n4, n5);
    treeNode *n1 = makeRootNode('-', n2, n3);

    fprintf(stdout, "preorder :   ");
    preorder(n1);
    fprintf(stdout, "\n");

    fprintf(stdout, "inorder :   ");
    inorder(n1);
    fprintf(stdout, "\n");

    fprintf(stdout, "postorder :  ");
    postorder(n1);
    fprintf(stdout, "\n");

    return 0;
}

treeNode *makeRootNode(char data, treeNode *leftNode, treeNode *rightNode) {
    treeNode *root = (treeNode *)malloc(sizeof(treeNode));
    root -> data = data;
    root -> leftNode = leftNode;
    root -> rightNode = rightNode;
    return root;
}
//전위순회, 본인데이터 출력, 왼쪽 서브트리, 오른쪽 서브트리
void preorder(treeNode *root ){
    if (root ){
        fprintf(stdout, "%c ", root -> data);
        preorder(root -> leftNode);
        preorder(root -> rightNode);
    }
}
//중위순회, 왼쪽 서브트리, 본인데이터 출력, 오른쪽 서브트리
void inorder(treeNode *root) {
    if (root) {
        inorder (root -> leftNode);
        fprintf(stdout, "%c ", root->data);
        inorder(root -> rightNode);
    }
}  
//후위순회, 왼쪽 서브트리, 오른쪽 서브트리, 본인 데이터 출력
void postorder (treeNode *root) {
    if (root) {
        postorder(root -> leftNode);
        postorder(root -> rightNode);
        fprintf(stdout, "%c ", root->data);
    }
}

