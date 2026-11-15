#include <stdlib.h>
#include "graph.h"




static void AdjlistAddValue(ADJLIST *list, int value) {

    // Verifica se o valor já existe
    for (int i = 0; i < list->count; i++) {
        if (list->items[i] == value) return;
    }

    // Expandir a memória se precisar
    if (list->count == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(int));
        if (!list->items) exit(1);
    }

    // Incrementa
    list->items[list->count++] = value;
}

static void GraphAddEdge(GRAPH *graph, int a, int b) {
    if (a == b) return;
    AdjlistAddValue(&graph->adj[a], b);
    AdjlistAddValue(&graph->adj[b], a);
}


GRAPH *ConstructGraph(TRIANGLES *triangles, int dimension) {
    GRAPH *graph = malloc(sizeof(GRAPH));

    if (!graph) exit(1);

    graph->size = dimension;
    graph->adj = calloc(graph->size, sizeof(ADJLIST));
    if (!graph->adj) exit(1);

    for (int i = 0; i < triangles->count; i++) {
        GraphAddEdge(graph, triangles->triangles[i].a, triangles->triangles[i].b);
        GraphAddEdge(graph, triangles->triangles[i].b, triangles->triangles[i].c);
        GraphAddEdge(graph, triangles->triangles[i].c, triangles->triangles[i].a);
    }

    DeconstructTriangles(triangles);
    return graph;
}

void DeconstructGraph(GRAPH *graph) {
    if (!graph) return;

    for (int i = 0; i < graph->size; i++) {
        free(graph->adj[i].items);
    }

    free(graph->adj);
    free(graph);
}