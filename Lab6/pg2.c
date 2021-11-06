#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct graph
{
    int V;
    LinkedList **adj;
} Graph;

int compareItems(Item it1, Item it2)
{
    int i1, i2;

    i1 = *((int *)it1);
    i2 = *((int *)it2);

    if (i1 < i2)
        return -1;
    if (i1 > i2)
        return 1;
    return 0;
}

void freeEntryItem(Item item)
{
    return; /* no mem actually allocated */
}

int main(int argc, char *argv[])
{
    LinkedList *aux;
    FILE *fp, *fp1;
    char *nome, *nome1;
    Graph *G;
    int *x, *y, *custo;
    int i = 0, V = 0, arestas = 0, err, j = 0, k = 0;
    nome = argv[1];

    fp = fopen(nome, "r");

    i = strlen(nome);
    nome1 = (char *)calloc(i + 2, sizeof(char));
    for (j = 0; j < i - 4; j++)
        nome1[j] = nome[j];

    strcat(nome1, "ladj");
    fp1 = fopen(nome1, "w");

    fscanf(fp, "%d %d", &V, &arestas);

    x = (int *)calloc(V, sizeof(int));
    y = (int *)calloc(V, sizeof(int));
    custo = (int *)calloc(V, sizeof(int));

    G = (Graph *)calloc(1, sizeof(Graph));
    G->V = V;

    G->adj = malloc(G->V * sizeof(LinkedList *));

    for (i = 0; i < G->V; i++)
    {
        G->adj[i] = NULL;
    }
    i = 0;
    while (i < arestas)
    {
        fscanf(fp, "%d %d %d", &x[i], &y[i], &custo[i]);
        G->adj[x[i]] = insertSortedLinkedList(G->adj[x[i]], (Item)&y[i], &custo[i], compareItems, &err);
        G->adj[y[i]] = insertSortedLinkedList(G->adj[y[i]], (Item)&x[i], &custo[i], compareItems, &err);
        i++;
    }

    fprintf(fp1, "%d\n", G->V);
    j = 0;
    while (j < G->V)
    {
        aux = G->adj[j];
        while (aux != NULL)
        {
            i = *((int *)getItemLinkedList(aux));
            k = *((int *)getcustoLinkedList(aux));
            fprintf(fp1, "%d:%d ", i, k);
            aux = getNextNodeLinkedList(aux);
        }
        fprintf(fp1, "-1\n");
        j++;
    }

    for (i = 0; i < G->V; i++)
    {
        aux = G->adj[i];
        freeLinkedList(aux, freeEntryItem);
    }
    free(G->adj);
    free(G);
    fclose(fp);
    fclose(fp1);
    free(x);
    free(y);
    free(nome1);
    free(custo);

    return 0;
}