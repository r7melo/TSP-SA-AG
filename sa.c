#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsp.h"
#include "tour.h"
#include "path.h"
#include "simulated_annealing.h"
#include "logger.h"
#include <string.h>

#define SA_INITIAL_TEMP      1000.0
#define SA_FINAL_TEMP        0.0001
#define SA_COOLING_RATE      0.993
#define SA_MAX_ITER_PER_TEMP 500

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

    PATH *best_path = SimulatedAnnealing(
        tsp,
        path,
        SA_INITIAL_TEMP,
        SA_FINAL_TEMP,
        SA_COOLING_RATE,
        SA_MAX_ITER_PER_TEMP
    );

    // MONTANDO O ARQUIVO
    TOUR *tour = ConstructTOUR(
        best_path->name,
        "Simulated Annealing",
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
