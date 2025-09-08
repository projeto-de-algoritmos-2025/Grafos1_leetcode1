#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void dfs(int u, int** graph, int n, int removed_node, bool* visited) {
    if (u == removed_node || visited[u]) {
        return;
    }
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (graph[u][v] == 1) {
            dfs(v, graph, n, removed_node, visited);
        }
    }
}

int minMalwareSpread(int** graph, int graphSize, int* graphColSize, int* initial, int initialSize) {
    qsort(initial, initialSize, sizeof(int), compare);

    int min_infected_count = graphSize + 1;
    int result_node = -1;

    for (int i = 0; i < initialSize; i++) {
        int node_to_remove = initial[i];
        bool visited[graphSize];
        memset(visited, false, sizeof(visited));
        
        for (int j = 0; j < initialSize; j++) {
            if (i == j) continue;
            int start_node = initial[j];
            if (!visited[start_node]) {
                dfs(start_node, graph, graphSize, node_to_remove, visited);
            }
        }
        
        int current_infected_count = 0;
        for (int k = 0; k < graphSize; k++) {
            if (visited[k]) {
                current_infected_count++;
            }
        }

        if (current_infected_count < min_infected_count) {
            min_infected_count = current_infected_count;
            result_node = node_to_remove;
        }
    }

    return result_node;
}
