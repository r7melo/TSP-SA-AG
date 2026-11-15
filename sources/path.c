#include <stdlib.h>
#include <math.h>
#include "path.h"


static void path_append(PATH *path, int node) {
    if (path->count == path->capacity) {
        path->capacity = path->capacity == 0 ? 8 : path->capacity * 2;
        path->nodes = realloc(path->nodes, path->capacity * sizeof(int));
        if (!path->nodes) exit(1);
    }
    path->nodes[path->count++] = node;
}


void DeconstructPath(PATH *path) {
    free(path->nodes);
    free(path);
}

PATH *BuildTour(TSP *tsp, GRAPH *graph) {
    PATH *path = malloc(sizeof(PATH));
    if (!path) exit(1);
    path->nodes = NULL;
    path->count = 0;
    path->capacity = 0;
    path->total_dist = 0.0;

    int *visited = calloc(graph->size, sizeof(int));
    if (!visited) exit(1);

    int current = 0;

    while (path->count < graph->size) {
        visited[current] = 1;
        path_append(path, current);

        int best = -1;
        double best_dist = 1e18;

        for (int j = 0; j < graph->adj[current].count; j++) {
            int neighbor = graph->adj[current].items[j];
            if (visited[neighbor]) continue;

            double d = TSPDistance(tsp, current, neighbor);
            if (d < best_dist) {
                best_dist = d;
                best = neighbor;
            }
        }

        if (best == -1) {
            for (int i = 0; i < graph->size; i++) {
                if (visited[i]) continue;

                double d = TSPDistance(tsp, current, i);
                if (d < best_dist) {
                    best_dist = d;
                    best = i;
                }
            }
        }

        if (best != -1) {
            path->total_dist += best_dist;  // acumula a distância do passo
            current = best;
        }
    }

    // Fecha o ciclo voltando ao nó inicial
    path->total_dist += TSPDistance(tsp, current, path->nodes[0]);

    free(visited);
    return path;
}