#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsp.h"
#include "tour.h"
#include "path.h"

int main() {
    srand(time(NULL));

    // LEITURA DO ARQUIVO
    TSP *tsp = ConstructTSP();
    ReadTSP(tsp, stdin);

    PATH *path = ConstructPath(tsp);   

    // MONTANDO O ARQUIVO
    TOUR *tour = ConstructTOUR(
        tsp->name,
        "Simulated Annealing",
        "TOUR",
        path->dimension,
        CalculatePathTotalDist(tsp, path),
        path->nodes_index
    );

    // ESCREVENDO O ARQUIVO FINAL
    WriteTOUR(tour, stdout);

    // LIMPANDO ENTIDADES
    DeconstructTOUR(tour);
    DeconstructTSP(tsp);

    return 0;
}
