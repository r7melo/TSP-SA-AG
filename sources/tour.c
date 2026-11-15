#include <stdio.h>
#include <stdlib.h>
#include "tour.h"

TOUR* ConstructTOUR(const char *name, const char *comment, const char *type, int dimension, int total_weight, int *tour_section) {
    
    // Alocando TOUR
    TOUR *tour = malloc(sizeof(TOUR));

    // Alocando TOUR_SECTION
    tour->tour_section = malloc(sizeof(int) * dimension);

    // Definindo variáveis
    snprintf(tour->name, sizeof(tour->name), "%s", name);
    snprintf(tour->comment, sizeof(tour->comment), "%s", comment);
    snprintf(tour->type, sizeof(tour->type), "%s", type);
    tour->dimension = dimension;
    tour->total_weight = total_weight;

    // Montagem do TOUR_SECTION
    for (int i = 0; i < dimension; i++) {
        tour->tour_section[i] = tour_section[i];
    }

    return tour;
}

void DeconstructTOUR(TOUR *tour) {
    free(tour->tour_section);
    free(tour);
}

void WriteTOUR(TOUR *tour, FILE *f) {
    fprintf(f, "NAME: %s\n", tour->name);
    fprintf(f, "COMMENT: %s\n", tour->comment);
    fprintf(f, "TYPE: %s\n", tour->type);
    fprintf(f, "DIMENSION: %d\n", tour->dimension);
    fprintf(f, "TOTAL_WEIGHT: %d\n", tour->total_weight);
    fprintf(f, "TOUR_SECTION\n");

    for (int i = 0; i < tour->dimension; i++) {
        fprintf(f, "%d\n", tour->tour_section[i]);
    }

    fprintf(f, "EOF\n");
}