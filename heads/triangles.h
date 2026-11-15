#pragma once

#include "tsp.h"

typedef struct {
    int a;
    int b;
    int c;
} TRIANGLE;

typedef struct {
    TRIANGLE *triangles;
    int count;
    int capacity;
} TRIANGLES;

TRIANGLES *ConstructTriangles();
void DeconstructTriangles(TRIANGLES *triangles);
TRIANGLE GetTriangle(TRIANGLES triangles, int indice);
void AddTriangle(TRIANGLES *triangles, TRIANGLE triangle);
void AppendSuperTriangle(TSP *tsp);
void RemoveSuperTriangle(TSP *tsp);