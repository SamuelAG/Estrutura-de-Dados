#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

#define vertex int

typedef struct node {
    vertex w;
    int custo;
    struct node *prox;
} Node;

typedef struct grafo {
    int vertices;
    int arestas;
    Node **adj;
} Grafo;

Node *newNode(vertex w, Node *prox, int custo);
Grafo *criaGrafo(int vertices);
void insereAresta(Grafo *gr, vertex v, vertex w, int custo);
void printarGrafo(Grafo *gr);
void BFS(Grafo *g, vertex s);
void caminhoMinimo(Grafo *g, vertex s, vertex *dist, vertex *pa);
void DFS(Grafo *g, vertex s);
void GrafoDFS(Grafo *g, vertex inicio);
void dijkstra(Grafo *gr, vertex s, vertex *pa, vertex *dist);

int main()
{
    Grafo *gr = criaGrafo(6);
    insereAresta(gr, 0, 2, 1);
    insereAresta(gr, 0, 3, 1);
    insereAresta(gr, 0, 4, 1);
    insereAresta(gr, 1, 2, 1);
    insereAresta(gr, 1, 4, 1);
    insereAresta(gr, 2, 4, 1);
    insereAresta(gr, 3, 4, 1);
    insereAresta(gr, 3, 5, 1);
    insereAresta(gr, 4, 5, 1);
    insereAresta(gr, 5, 1, 1);
    
    vertex dist[gr->vertices], pa[gr->vertices];
    printarGrafo(gr);
    GrafoDFS(gr, 0);
    BFS(gr, 0);
    caminhoMinimo(gr, 0, dist, pa);
    dijkstra(gr, 0, pa, dist);
    return 0;
}

Node *newNode(vertex w, Node *prox, int custo)
{
    Node *novo = (Node *) malloc(sizeof(Node));
    novo->w = w;
    novo->prox = prox;
    novo->custo = custo;
    return novo;
}

Grafo *criaGrafo(int vertices)
{
    Grafo *gr = (Grafo *) malloc(sizeof(Grafo));
    gr->vertices = vertices;
    gr->arestas = 0;
    gr->adj = (Node **) malloc(sizeof(Node *) * vertices);
    for(vertex v = 0; v < vertices; v++)
        gr->adj[v] = NULL;
    return gr;
}

void insereAresta(Grafo *gr, vertex v, vertex w, int custo)
{
    Node *i = gr->adj[v];
    while(i != NULL) i = i->prox;
    gr->adj[v] = newNode(w, gr->adj[v], custo);
    gr->arestas++;
}

void printarGrafo(Grafo *gr) {
    for(vertex v = 0; v < gr->vertices; v++)
    {
        Node *indice = gr->adj[v];
        printf("%d:", v);
        while(indice != NULL)
        {
            printf("-> %d(%d) ", indice->w, indice->custo);
            indice = indice->prox;
        }
        printf("\n");
    }
}

vertex pa[1000];
vertex visitados[1000];
void BFS(Grafo *g, vertex s)
{
    printf("\nBFS:\n");
    int visitados[g->vertices], ordem = 0;
    for(vertex v = 0; v < g->vertices; v++)
        visitados[v] = -1;
    Fila *fila = criaFila();
    visitados[s] = ordem++;
    pa[s] = s;
    push(fila, s);

    while(!vazia(fila))
    {
        int v = pop(fila);
        for(Node *i = g->adj[v]; i != NULL; i = i->prox)
        {
            vertex w = i->w;
            if(visitados[w] ==-1)
            {
                visitados[w] = ordem++;
                pa[w] = v;
                push(fila, w);
            }
        }
    }
    printf("Visitados[]: ");
    for(int i = 0; i < g->vertices; i++)
        printf("%d ", visitados[i]);
    printf("\nArvore BFS[]: ");
    for(int i = 0; i < g->vertices; i++)
        printf("%d ", pa[i]);
    printf("\n");
}

void caminhoMinimo(Grafo *g, vertex s, vertex *dist, vertex *pa)
{
    const int infinito = g->vertices;
    for (vertex v = 0; v < g->vertices; ++v)
    { 
        pa[v] = -1;
        dist[v] = infinito;
    }
   pa[s] = s, dist[s] = 0;
   Fila *fila = criaFila();
   push(fila, s);

    while (!vazia(fila)) {
        vertex v = pop(fila); 
        for(Node *i = g->adj[v]; i != NULL; i = i->prox){
            vertex w = i->w;
            if(dist[w] == infinito) 
            { 
                dist[w] = dist[v] + 1;
                pa[w] = v;
                push(fila, w); 
            }
        }
   }

   // Printa os vetores de distancia
    printf("\nCaminho minimo:\nDistancia: ");
    for(int i = 0; i < g->vertices; i++)
        printf("%d ", dist[i]);
    printf("\nArvore BFS[]: ");
    for(int i = 0; i < g->vertices; i++)
        printf("%d ", pa[i]);
    printf("\n");
}

int count, profundidade;
void DFS(Grafo *g, vertex s)
{
    visitados[s] = count++;
    for(Node *i = g->adj[s]; i != NULL; i = i->prox)
    {
        vertex w = i->w;
        if(visitados[w] == -1)
        {
            pa[w] = s;
            DFS(g, w);
        }
    }
}

void GrafoDFS(Grafo *g, vertex inicio)
{
    printf("DFS:\n");   
    count = 0;   
    for(vertex v = 0 ; v < g->vertices; v++)
        visitados[v] = -1;

    for(vertex v = 0; v < g->vertices; v++)
        if(visitados[v] == -1){
            pa[v] = v;
            DFS(g, v);
        }

    printf("PA[]: ");
    for(int i = 0; i < g->vertices; i++)
        printf("%d ", pa[i]);
    printf("\n");
}


void dijkstra(Grafo *gr, vertex s, vertex *pa, vertex *dist)
{
    vertex hook[gr->vertices], infinito = 100;

    // Inicialização
    for(vertex v = 0; v < gr->vertices; v++)
    {
        pa[v] = -1;
        dist[v] = infinito;
        hook[v] = -1;
    }
    pa[s] = s, dist[s] = 0;
    for(Node *i = gr->adj[s]; i != NULL; i = i->prox)
    {
        dist[i->w] = i->custo;
        hook[i->w] = s;
    }

    while(true)
    {
        vertex y;
        int mindist = infinito;
        for(vertex z = 0; z < gr->vertices; z++)
        {
            if(pa[z] == -1 && dist[z] < mindist)
            {
                mindist = dist[z];
                y = z;
            }
        }
        if(mindist == infinito) break;
        pa[y] = hook[y];
        // atualização de dist[]:
        for(Node *i = gr->adj[y]; i != NULL; i = i->prox)
        {
            vertex w = i->w;
            int custo = i->custo;
            if(!(dist[y] + custo >= dist[w]))
            {
                dist[w] = dist[y] + custo;
                hook[w] = y;
            }
        }

    }
    printf("\nDijkstra:\nArvore BFS[]: ");
    for(int i = 0; i < gr->vertices; i++)
        if(pa[i] == -1)
            printf("* ");
        else
            printf("%d ", pa[i]);
    printf("\nHOOK[]: ");
    for(int i = 0; i < gr->vertices; i++)
        if(hook[i] == -1)
            printf("* ");
        else
            printf("%d ", hook[i]);
    printf("\nDIST[]: ");
    for(int i = 0; i < gr->vertices; i++)
        if(dist[i] == 100)
            printf("* ");
        else
            printf("%d ", dist[i]);        
    printf("\n");

}

