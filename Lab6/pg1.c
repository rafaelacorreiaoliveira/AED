#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph
{
    int V;
    int A;
    int **adj;
} Graph;

int main(int argc, char *argv[])
{

    FILE *fp, *fp1;
    Graph *G;
    char *nome, *nome1;
    int i = 0, j = 0, k = 0, arestas = 0, grau = 0, grauAux = 0;
    double conta = 0.1, Aaux = 0;
    nome = argv[1];

    fp = fopen(nome, "r");

    i = strlen(nome);
    nome1 = (char *)calloc(i + 2, sizeof(char));
    for (j = 0; j < i - 4; j++)
        nome1[j] = nome[j];

    strcat(nome1, ".edge");

    fp1 = fopen(nome1, "w");

    G = (Graph *)calloc(1, sizeof(Graph));

    fscanf(fp, " %d ", &G->V);
    G->adj = (int **)calloc(G->V, sizeof(int *));
    for (i = 0; i < G->V; i++)
    {
        G->adj[i] = (int *)calloc(G->V, sizeof(int));
    }

    for (i = 0; i < G->V; i++)
    {
        grauAux = 0;
        for (j = 0; j < G->V; j++)
        {
            fscanf(fp, "%d", &k);
            if (k > 0)
            {
                grauAux++;
                G->adj[i][j] = k;
                arestas++;
            }
        }
        if (grauAux > grau)
            grau = grauAux;
    }
    Aaux = arestas;
    G->A = arestas / 2;
    conta = Aaux / G->V;
    printf("\n %f \n ", conta);
    printf("\n %d \n", grau);

    fprintf(fp1, "%d %d \n", G->V, G->A);
    k = 0;
    for (i = 0; i < G->V; i++)
    {
        for (j = k; j < G->V; j++)
        {
            if (G->adj[i][j] > 0)
            {
                fprintf(fp1, "%d %d %d\n", i, j, G->adj[i][j]);
            }
        }
        k++;
    }

    for (i = 0; i < G->V; i++)
        free(G->adj[i]);

    free(G->adj);
    free(G);
    free(nome1);
    fclose(fp);
    fclose(fp1);
    return 0;
}