typedef struct fila {
    int vetor[50];
    int inicio, fim, quantidade;
} Fila;

Fila *criaFila()
{
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    fila->fim = fila->inicio = -1;
    fila->quantidade = 0;
}

bool vazia(Fila *fila)
{
    return fila->quantidade == 0;
}

int top(Fila *fila)
{
    return fila->vetor[fila->inicio];
}

void push(Fila *fila, int valor)
{
    fila->vetor[fila->fim++] = valor;
    fila->quantidade++;
}

int pop(Fila *fila)
{
    fila->quantidade--;
    return fila->vetor[fila->inicio++];
}

void mostraFila(Fila *fila)
{
    for(int i = fila->inicio; i < fila->fim; i++)
        printf("%d ", fila->vetor[i]);
    printf("\n");
}