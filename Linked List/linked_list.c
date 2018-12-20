#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *push(Node *lista, int data);
Node *pop(Node *lista, int data);
bool vazia(Node *lista);
void display(Node *lista);
void libera(Node *lista);

int main(){
    Node *head = NULL;
    for(int i = 0; i < 5; i++){
        head = push(head, i);
    }
    display(head);
    head = pop(head, 3);
    printf("\n");
    return 0;
}

Node *push(Node *lista, int data){
    Node *linked_list = (Node *) malloc(sizeof(Node));
    linked_list->data = data;
    linked_list->next = lista;
    return linked_list;
}

Node *pop(Node *lista, int data){
    if(!vazia(lista)){
        Node *anterior = NULL, *indice = lista;
        while(indice->data != data && indice != NULL){
            anterior = indice;
            indice = indice->next;
        }
        anterior->next = indice->next;
        free(indice);
        return lista;
    } else {
        return lista;
    }
}

bool vazia(Node *lista){
    return lista == NULL;
}

void libera(Node *lista){
    if(!vazia(lista)){
        libera(lista);
        free(lista);
    }
}

void display(Node *lista){
    if(!vazia(lista)){
        printf("%d ", lista->data);
        display(lista->next);
    }
}