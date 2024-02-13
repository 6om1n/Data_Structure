#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

treeNode *makeRootNode(char data, treeNode *leftNode, treeNode *rightNode);
void preorder(treeNode *root);
void inorder(treeNode *root);
void postorder(treeNode *root);

int main(int argc, char *argv[]){
    treeNode *n7 = makeRootNode('D', NULL, NULL);
    treeNode *n6 = makeRootNode('C', NULL, NULL);
    treeNode *n5 = makeRootNode('B', NULL, NULL);
    treeNode *n4 = makeRootNode('A', NULL, NULL);
    treeNode *n3 = makeRootNode('/', n6, n7);
    treeNode *n2 = makeRootNode('*', n4, n5);
    treeNode *n1 = makeRootNode('-', n2, n3);

    fprintf(stdout, "\n preorder : ");
    preorder(n1);

    fprintf(stdout, "\n inorder : ");
    inorder(n1);

    fprintf(stdout, "\n postorder : ");
    postorder(n1);

    return 0;

}

treeNode *makeRootNode(char data, treeNode *leftNode, treeNode *rightNode) {
    treeNode *root = (treeNode *)malloc(sizeof(treeNode));
    root -> data = data;
    root -> left = leftNode;
    root -> right = rightNode;
    return root;
}
//전위순회 (본인꺼 출력 -> 왼쪽노드 탐색 -> 오른쪽 노드 탐색)
//root가 NULL이 아닌 경우에만 출력이 된다. 
void preorder(treeNode *root) {
    if (root) {
        fprintf(stdout, " %c ", root->data);
        preorder(root -> left);
        preorder (root -> right);
    }
}
/*중위순회 -> 왼쪽꺼 출력, 본인꺼출력 -> 오른쪽꺼 출력*/
void inorder(treeNode *root) {
    if (root) {
        inorder(root ->left);
        fprintf(stdout, "%c ", root -> data);
        inorder (root -> right);
    }
}
void postorder(treeNode *root) {
    if (root) {
        postorder(root-> left);
        postorder(root -> right);
        fprintf(stdout, "%c ", root-> data);
    }
}