#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node Node;
struct node {
    int data;
    Node *next;
};

void init();
Node *push(Node *head, int data);
Node *pop(Node *head);
Node *peek(Node *head);
void display(Node *head);

int main(){
    Node *head;
    init(head);
    head = push(head, 0);
    head = push(head, 1);
    head = push(head, 2);
    head = push(head, 3);
    head = push(head, 4);
    display(head);
    head = pop(head);
    head = pop(head);
    display(head);
    return 0;
}

void init(Node *head){
    head = NULL;
}

Node *push(Node *head, int data){
    Node *novo = (Node *) malloc(sizeof(Node));
    novo->data = data;
    novo->next = head;
    head = novo;
    return head;
}

Node *pop(Node *head){
    Node *aux = head;
    head = head->next;
    free(aux);
    return head;
}

Node *peek(Node *head){
    return head;
}

void display(Node *head){
    Node *indice;
    for(indice = head; indice != NULL; indice = indice->next){
        printf("%d ", indice->data);
    }
    printf("\n");
}
