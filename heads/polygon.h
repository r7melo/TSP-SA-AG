#pragma once

typedef struct {
    int a;
    int b;
} EDGE;

typedef struct
{
    EDGE *edges;
    int count;
    int capacity;
} POLYGON;


void AddEdge(POLYGON *polygon, EDGE *edge);
void unique_boundary_edges(POLYGON *polygon, int *unique_count);