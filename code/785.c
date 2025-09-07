#include <stdbool.h>
#include <stdlib.h>

bool dfs(int no, int cor, int *cores, int **grafo, int *tamanhoColunas)
{
    cores[no] = cor;
    for (int i = 0; i < tamanhoColunas[no]; i++)
    {
        int vizinho = grafo[no][i];
        if (cores[vizinho] == -1)
        {
            if (!dfs(vizinho, 1 - cor, cores, grafo, tamanhoColunas))
            {
                return false;
            }
        }
        else if (cores[vizinho] == cor)
        {
            return false;
        }
    }
    return true;
}

bool isBipartite(int **grafo, int tamanhoGrafo, int *tamanhoColunas)
{
    int *cores = (int *)malloc(sizeof(int) * tamanhoGrafo);
    for (int i = 0; i < tamanhoGrafo; i++)
    {
        cores[i] = -1;
    }

    for (int i = 0; i < tamanhoGrafo; i++)
    {
        if (cores[i] == -1)
        {
            if (!dfs(i, 0, cores, grafo, tamanhoColunas))
            {
                free(cores);
                return false;
            }
        }
    }

    free(cores);
    return true;
}
s