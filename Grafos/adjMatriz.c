#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

typedef struct grafo {
    int vertices;
    int arestas;
    int **adjMatriz;
    int **pesos;
} Grafo;

int **criaMatriz(int linha, int coluna, int chave);
Grafo *criaGrafo(int vertices);
void adicionaAresta(Grafo *gr, int inicio, int chegada, int peso);
void removerAresta(Grafo *gr, int inicio, int chegada);
void mostraGrafo(Grafo *gr);
void DFS(Grafo *gr, int inicio);
void GrafoDFS(Grafo *gr, int inicio);
void BFS(Grafo *gr, int inicio);
void caminhoMinimo(Grafo *gr, int inicio, int *dist, int *pa);


int main() {
    Grafo *gr = criaGrafo(6);
    adicionaAresta(gr, 0, 2, 1);
    adicionaAresta(gr, 0, 3, 1);
    adicionaAresta(gr, 0, 4, 1);
    adicionaAresta(gr, 1, 1, 1);
    adicionaAresta(gr, 1, 4, 1);
    adicionaAresta(gr, 2, 4, 1);
    adicionaAresta(gr, 3, 4, 1);
    adicionaAresta(gr, 3, 5, 1);
    adicionaAresta(gr, 4, 5, 1);
    adicionaAresta(gr, 5, 1, 1);

    int dist[gr->vertices], pa[gr->vertices];
    caminhoMinimo(gr, 0, dist, pa);
    BFS(gr, 0);
    GrafoDFS(gr, 0);

    printf("\n");
    return 0;
}

int **criaMatriz(int linha, int coluna, int chave) {
    int **matriz = (int **) malloc(sizeof(int *) * linha);
    for(int i = 0; i < coluna; i++)
        matriz[i] = (int *) malloc(sizeof(int) * coluna);

    for(int i = 0; i < linha; i++)
        for(int j = 0; j < coluna; j++)
            matriz[i][j] = chave;
    return matriz;
}

Grafo *criaGrafo(int vertices) {
    Grafo *gr = (Grafo *) malloc(sizeof(Grafo));
    gr->vertices = vertices;
    gr->arestas = 0;
    gr->adjMatriz = criaMatriz(vertices, vertices, 0);
    gr->pesos = criaMatriz(vertices, vertices, -1);
    return gr;
}

void adicionaAresta(Grafo *gr, int inicio, int chegada, int peso) {
    if(inicio < gr->vertices && chegada < gr->vertices && gr->adjMatriz[inicio][chegada] == 0) {
        gr->adjMatriz[inicio][chegada] = 1;
        gr->pesos[inicio][chegada] = peso;
        gr->arestas++;
    }
}

void removerAresta(Grafo *gr, int inicio, int chegada) {
    if(inicio < gr->vertices && chegada < gr->vertices && gr->adjMatriz[inicio][chegada] == 1) {
        gr->adjMatriz[inicio][chegada] = 0;
        gr->arestas--;    
    }
}

void mostraGrafo(Grafo *gr) {
    printf("Matriz de Adj:\n");
    for(int i = 0; i < gr->vertices; i++) {
        //printf("%d -> ", i);
        for(int j = 0; j < gr->vertices; j++) {
            printf("%2d ", gr->adjMatriz[i][j]);
        }
        printf("\n");
    }
}

int contador, profundidade, visitados[100], pa[100];

void DFS(Grafo *gr, int inicio) {

    visitados[inicio] = contador++;
    for(int v = 0; v < gr->vertices; v++) {       
        if(gr->adjMatriz[inicio][v] != 0 && visitados[v] == -1) {
            for(int i = 0; i < profundidade; i++)
                printf("  ");
            profundidade++;
            printf("%d-%d DFS(G,%d)\n", inicio, v, v);
            pa[inicio] = v;
            DFS(gr, v);
        } else if(gr->adjMatriz[inicio][v] != 0 && visitados[v] != -1) {
            for(int i = 0; i < profundidade; i++)
                printf("  ");
            printf("%d-%d\n", inicio, v);
        }
        
    }
    for(int i = 0; i < profundidade; i++)
        printf("  ");
    profundidade--;
    printf("%d\n", inicio);
}

void GrafoDFS(Grafo *gr, int inicio) {
    profundidade = 0;
    contador = 0;
    for(int i = 0; i < gr->vertices; i++)
        visitados[i] = -1;

    printf("Rastreamento da DFS:");

    for(int v = 0; v < gr->vertices; v++)
        if(visitados[v] == -1) {
            profundidade = 0;
            printf("\n");
            pa[v] = v;
            DFS(gr, v);
        }    

    
    for(int i = 0; i < gr->vertices; i++)
        printf("O vertice %d foi o %d a ser visitado.\n", i, visitados[i]);
    printf("\nPA[]: ");
    for(int i = 0; i < gr->vertices; i++)
        printf("%d ", pa[i]);
}

int arvoreBFS[100];

void BFS(Grafo *gr, int inicio) {
    int visitados[gr->vertices], ordem = 0;
    for(int i = 0; i < gr->vertices; i++)
        visitados[i] = -1;
    Fila *fila = criaFila();   
    visitados[inicio] = ordem++;
    arvoreBFS[inicio] = inicio;
    push(fila, inicio);

    while(!vazia(fila)) {
        int v = pop(fila);
        for(int w = 0; w < gr->vertices; w++) {
            if(gr->adjMatriz[v][w] == 1 && visitados[w] == -1) {
                visitados[w] = ordem++;
                arvoreBFS[w] = v;
                push(fila, w);
            }
        }
    }
    printf("BFS:\nVisitados[]: ");
    for(int i = 0; i < gr->vertices; i++)
        printf("%d ", visitados[i]);
    printf("\n");
}

void caminhoMinimo(Grafo *gr, int inicio, int *dist, int *pa) {
    // Inicialização
    const int infinito = gr->vertices;
    for(int v = 0; v < gr->vertices; v++) {
        pa[v] = -1;
        dist[v] = infinito;
    }
    pa[inicio] = inicio;
    dist[inicio] = 0;
    Fila *fila = criaFila();
    push(fila ,inicio);

    // Algoritmo
    while(!vazia(fila)) {
        int v = pop(fila);
        for(int w = 0; w < gr->vertices; w++) {
            if(gr->adjMatriz[v][w] == 1 && dist[w] == infinito) {
                dist[w] = dist[v] +1;
                pa[w] = v;
                push(fila, w);
            }
        }
    }

    // Printa os vetores de distancia
    printf("Caminho minimo\nDistancia: ");
    for(int i = 0; i < gr->vertices; i++)
        printf("%d ", dist[i]);
    printf("\nArvore BFS[]: ");
    for(int i = 0; i < gr->vertices; i++)
        printf("%d ", pa[i]);
    printf("\n");
}





