#pragma once

#include "tsp.h"
#include "triangles.h"

typedef struct {
    int *items;
    int count;
    int capacity;
} ADJLIST;

typedef struct {
    int size;
    ADJLIST *adj;
} GRAPH;

static void GraphAddEdge(GRAPH *graph, int a, int b);
static void AdjlistAddValue(ADJLIST *list, int value);
GRAPH *ConstructGraph(TRIANGLES *triangles, int dimension);
void DeconstructGraph(GRAPH *graph);
