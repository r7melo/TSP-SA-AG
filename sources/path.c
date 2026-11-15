#include <stdlib.h>
#include <math.h>
#include "path.h"
#include "tsp.h"
#include "error.h"

PATH *ConstructPath(TSP *tsp) {
    PATH *path = malloc(sizeof(PATH));
    CHECK_ALLOC(path);

    path->dimension = tsp->dimension;
    path->nodes_index = GenerateRandomPath(path->dimension);
    
    return path;
}

int* GenerateRandomPath(int dimension) {
    int *nodes_index = malloc(dimension * sizeof(int));
    CHECK_ALLOC(nodes_index);

    for (int i = 0; i < dimension; i++) {
        nodes_index[i] = i;
    }

    // Algoritmo Fisher-Yates
    for (int i = dimension - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = nodes_index[i];
        nodes_index[i] = nodes_index[j];
        nodes_index[j] = temp;
    }

    return nodes_index;
}

void DeconstructPath(PATH *path) {
    free(path->nodes_index);
    free(path);
}

int DistanceBetweenNodes(Node a, Node b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return (int)ceil(sqrt(dx * dx + dy * dy));
}

int CalculatePathTotalDist(TSP *tsp, PATH *path) {
    int total_dist = 0;

    for (size_t i = 0; i < path->dimension; i++)
    {
        int index_node_1 = path->nodes_index[i];
        int index_node_2;

        if (i+1 < path->dimension)
            index_node_2 = path->nodes_index[i+1];
        else
            index_node_2 = path->nodes_index[0];

        total_dist += DistanceBetweenNodes(
            tsp->nodes[index_node_1],
            tsp->nodes[index_node_2]
        );
    }

    return total_dist;
}