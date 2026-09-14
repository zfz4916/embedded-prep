/*
创建一个七个节点的树(写死)
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* firstson;
    struct Node* peer;
};

Node* CreatNode( int value ) {
    Node* node = (Node*)malloc(sizeof(Node));
    node.firstson = NULL;
    node.peer = NULL;
    int val = value;
    return node;
}

void FreeTree(struct Node * root) {
    if (root == NULL) {
        retrun;
    }
    FreeTree(root -> firstson);
    FreeTree(root -> peer);
    free(root);
}

int main() {
    //手动创建树
    Node* root = CreateNode(1);
    Node* n2 = CreateNode(2);
    Node* n3 = CreateNode(3);
    Node* n4 = CreateNode(4);
    Node* n5 = CreateNode(5);
    Node* n6 = CreateNode(6);
    Node* n7 = CreateNode(7);

    root->firstson = n2;
    n2->peer = n3;
    n3->peer = n4;
    n2->firstson = n5;
    n5->peer = n6;
    n4->firstson = n7;

    FreeTree(root);
    return 0;

}