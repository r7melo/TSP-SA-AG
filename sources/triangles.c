#include <stdlib.h>
#include "triangles.h"

TRIANGLES *ConstructTriangles() {
    TRIANGLES *triangles = malloc(sizeof(TRIANGLES));
    if (!triangles) exit(1);
    triangles->capacity = 16;
    triangles->count = 0;
    
    triangles->triangles = malloc(16 * sizeof(TRIANGLE));
    if (!triangles->triangles) exit(1);

    return triangles;
}

void DeconstructTriangles(TRIANGLES *triangles) {
    free(triangles->triangles);
    free(triangles);
}

void AddTriangle(TRIANGLES *triangles, TRIANGLE triangle) {
    if (triangles->count == triangles->capacity) {
        triangles->capacity = triangles->capacity == 0 ? 16 : triangles->capacity * 2;
        triangles->triangles = realloc(triangles->triangles, triangles->capacity * sizeof(TRIANGLE));
        if (!triangles->triangles) exit(1);
    }

    triangles->triangles[triangles->count].a = triangle.a;
    triangles->triangles[triangles->count].b = triangle.b;
    triangles->triangles[triangles->count].c = triangle.c;
    triangles->count++;
}

void AppendSuperTriangle(TSP *tsp) {
    int n = tsp->dimension;
    double xmin = tsp->nodes[0].x;
    double xmax = tsp->nodes[0].x;
    double ymin = tsp->nodes[0].y;
    double ymax = tsp->nodes[0].y;

    for (int i = 1; i < n; i++) {
        if (tsp->nodes[i].x < xmin) xmin = tsp->nodes[i].x;
        if (tsp->nodes[i].x > xmax) xmax = tsp->nodes[i].x;
        if (tsp->nodes[i].y < ymin) ymin = tsp->nodes[i].y;
        if (tsp->nodes[i].y > ymax) ymax = tsp->nodes[i].y;
    }

    double dx = xmax - xmin;
    double dy = ymax - ymin;
    double delta = dx > dy ? dx : dy;
    double midx = (xmin + xmax) / 2.0;
    double midy = (ymin + ymax) / 2.0;

    if (delta <= 0.0) delta = 1.0;

    tsp->nodes = realloc(tsp->nodes, (n + 3) * sizeof(Node));
    if (!tsp->nodes) exit(1);

    tsp->nodes[n].id = -1;
    tsp->nodes[n].x = midx - 20.0 * delta;
    tsp->nodes[n].y = midy - delta;

    tsp->nodes[n + 1].id = -2;
    tsp->nodes[n + 1].x = midx;
    tsp->nodes[n + 1].y = midy + 20.0 * delta;

    tsp->nodes[n + 2].id = -3;
    tsp->nodes[n + 2].x = midx + 20.0 * delta;
    tsp->nodes[n + 2].y = midy - delta;
}

void RemoveSuperTriangle(TSP *tsp) {
    tsp->nodes = realloc(tsp->nodes, tsp->dimension * sizeof(Node));
    if (!tsp->nodes) exit(1);
}