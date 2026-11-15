#include <stdlib.h>
#include "polygon.h"

void AddEdge(POLYGON *polygon, EDGE *edge) {
    if (edge->a > edge->b) {
        int tmp = edge->a;
        edge->a = edge->b;
        edge->b = tmp;
    }

    if (polygon->count == polygon->capacity) {
        polygon->capacity = polygon->capacity == 0 ? 16 : polygon->capacity * 2;
        polygon->edges = realloc(polygon->edges, polygon->capacity * sizeof(EDGE));
        if (!polygon->edges) exit(1);
    }

    polygon->edges[polygon->count].a = edge->a;
    polygon->edges[polygon->count].b = edge->b;
    polygon->count++;
}


void unique_boundary_edges(POLYGON *polygon, int *unique_count) {
    int old_count = polygon->count;
    EDGE *old_edges = polygon->edges;

    polygon->edges = NULL;
    polygon->count = 0;
    polygon->capacity = 0;

    for (int i = 0; i < old_count; i++) {
        int repeats = 0;
        for (int j = 0; j < old_count; j++) {
            if (old_edges[i].a == old_edges[j].a &&
                old_edges[i].b == old_edges[j].b) repeats++;
        }
        if (repeats == 1) AddEdge(polygon, &old_edges[i]);
    }
    *unique_count = polygon->count;
    free(old_edges);
}