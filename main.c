#include <stdio.h>
#include <stdlib.h>
#include "tsp.h"
#include "tour.h"
#include "delaunay.h"
#include "triangles.h"
#include "graph.h"
#include "path.h"
#include "optimizer.h"

#define TWO_OPT_MAX_ITER 100

int main() {

    TSP *tsp = ConstructTSP();
    ReadTSP(tsp, stdin);


    // PROCESSAR DALEUNAY (Bawyer-Wotson)
    // Entrada: TSP
    // Saída: TRIANGLES
    TRIANGLES *triangles = BuildDelaunay(tsp);

    // CONSTRUIR GRAFO
    // Entrada: TRIANGLES
    // Saída: GRAPH
    GRAPH *graph = ConstructGraph(triangles, tsp->dimension);


    // PROCESSAR CAMINHO
    // Entrada: TSP e GRAFO
    // Saída: PATH
    PATH *path = BuildTour(tsp, graph);

    // OTIMIZAR ROTA
    // Entrada: PATH
    // Processa: rota otimizada
    ApplyTwoOpt(path->nodes, path->count, tsp, TWO_OPT_MAX_ITER);

    // Recalcula a distância total após a otimização
    path->total_dist = TwoOptTotalDistance(path->nodes, path->count, tsp);


    // MONTANDO O ARQUIVO
    TOUR *tour = ConstructTOUR(
        tsp->name,
        "KNN + Delaunay",
        "TOUR",
        path->count,
        (int)path->total_dist,
        path->nodes
    );

    // ESCREVENDO O ARQUIVO FINAL
    WriteTOUR(tour, stdout);

    // LIMPANDO ENTIDADES
    DeconstructTOUR(tour);
    DeconstructPath(path);
    DeconstructGraph(graph);
    DeconstructTSP(tsp);

    return 0;
}
