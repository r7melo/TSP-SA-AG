#pragma once
#include <stdio.h>

typedef struct {
    int id;
    double x, y;
} Node;

typedef struct {
    char name[64];
    int dimension;
    Node *nodes;
} TSP;


TSP* ConstructTSP();
void ReadTSP(TSP *tsp, FILE *f);
void DeconstructTSP(TSP* tsp);
double TSPDistance(TSP *tsp, int a, int b);
