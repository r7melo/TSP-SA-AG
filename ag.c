#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsp.h"
#include "tour.h"
#include "path.h"
#include "genetic_algorithm.h"
#include "logger.h"
#include <string.h>

#define AG_CUT1 0.4
#define AG_CUT2 0.8


static int ParseLogFlag(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) 
        if (strcmp(argv[i], "-log") == 0) 
            return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    LogSetEnabled(ParseLogFlag(argc, argv));

    // LEITURA DO ARQUIVO
    TSP *tsp = ConstructTSP();
    ReadTSP(tsp, stdin);

    PATH *path = ConstructPath(tsp);   

    PATH *best_path = GeneticAlgotithm(
        tsp,
        path,
        AG_CUT1,
        AG_CUT2
    );

    // MONTANDO O ARQUIVO
    TOUR *tour = ConstructTOUR(
        best_path->name,
        "Genetic Algorithm",
        "TOUR",
        best_path->dimension,
        best_path->total_weight,
        best_path->nodes_index
    );

    // ESCREVENDO O ARQUIVO FINAL
    WriteTOUR(tour, stdout);

    // LIMPANDO ENTIDADES
    DeconstructTOUR(tour);
    DeconstructTSP(tsp);

    return 0;
}
