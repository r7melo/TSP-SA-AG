#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tsp.h"

TSP* ConstructTSP() {
    TSP *tsp = malloc(sizeof(TSP));
    tsp->nodes = NULL;
    tsp->dimension = 0;
    return tsp;
}

void ReadTSP(TSP *tsp, FILE *f) {
    char linha[256];
    int lendo_coords = 0;
    int i = 0;

    while (fgets(linha, sizeof(linha), f)) {

        if (strstr(linha, "NAME")) {
            sscanf(linha, "%*[^:]: %63s", tsp->name);
        }

        else if (strstr(linha, "DIMENSION")) {
            sscanf(linha, "%*[^:]: %d", &tsp->dimension);

            tsp->nodes = malloc(sizeof(Node) * tsp->dimension);
            if (!tsp->nodes) exit(1);
        }

        else if (strstr(linha, "NODE_COORD_SECTION")) {
            lendo_coords = 1;
        }

        else if (strstr(linha, "EOF")) {
            break;
        }

        else if (lendo_coords && tsp->nodes && i < tsp->dimension) {
            if (sscanf(linha, "%d %lf %lf",
                       &tsp->nodes[i].id,
                       &tsp->nodes[i].x,
                       &tsp->nodes[i].y) == 3) {
                i++;
            }
        }
    }
}

void DeconstructTSP(TSP *tsp) {
    free(tsp->nodes);
    free(tsp);
}

double TSPDistance(TSP *tsp, int a, int b) {
    double dx = tsp->nodes[a].x - tsp->nodes[b].x;
    double dy = tsp->nodes[a].y - tsp->nodes[b].y;
    return sqrt(dx*dx + dy*dy);
}