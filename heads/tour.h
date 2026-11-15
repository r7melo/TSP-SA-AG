#pragma once
#include <stdio.h>

typedef struct {
    char name[64];
    char comment[256];
    char type[32];
    int dimension;
    int total_weight;
    int *tour_section;
} TOUR;

TOUR* ConstructTOUR(const char *name, const char *comment, const char *type, int dimension, int total_weight, int *tour_section);
void WriteTOUR(TOUR *tour, FILE *f);
void DeconstructTOUR(TOUR *tour);