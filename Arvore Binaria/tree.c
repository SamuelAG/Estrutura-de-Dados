#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node {
    int data;
    Node *right;
    Node *left;
};

Node *newNode(int data);
Node *insert(Node *node, int data);
Node *delete(Node *root, int data);
Node *minValueNode(Node *node);
Node *search(Node *root, int data);
Node *display(Node *root);

int main() {
    Node *root = NULL;
    root = insert(root, 1);
    for(int i = 0; i < 10; i++){
        insert(root, i);
    }
    display(root);
    printf("\n");
    return 0;
}

Node *delete(Node *root, int data) {
    if(root == NULL) return root;

    if(data < root->data)
        root->left = delete(root->left, data);
    else if(data > root->data)
        root->right = delete(root->left, data);
    else {
        if(root->left == NULL){
            Node *aux = root->right;
            free(root);
            return aux;
        } else if(root->right == NULL) {
            Node *aux = root->left;
            free(root);
            return aux;
        }

        Node *aux = minValueNode(root->right);
        root->data = aux->data;
        root->right = delete(root->right, data);
    }
}

Node *newNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node *insert(Node *node, int data) {
    if(node == NULL) return newNode(data);

    if(data < node->data)
        node->left = insert(node->left, data);
    else if(data > node->data)
        node->right = insert(node->right, data);
    
    return node;
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while(current->left != NULL) {
        current = current->left;    
    }
    return current;
}

Node *search(Node *root, int data) {
    if(root == NULL || root->data == data) return root;

    if(data > root->data) return search(root->right, data);

    return search(root->left, data);
}

Node *display(Node *root) {
    if(root != NULL) {
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}