#pragma once

#include "path.h"

PATH *MutationInsert(const PATH *path);
PATH *MutationSwap(const PATH *path);
PATH *MutationRandom(const PATH *path);

PATH *CrossoverOX(const PATH *parent1, const PATH *parent2, const float point1, const float point2);
PATH *CrossoverCX(const PATH *parent1, const PATH *parent2);
PATH *CrossoverPMX(const PATH *parent1, const PATH *parent2);
PATH *CrossoverGNX(const PATH *parent1, const PATH *parent2);

PATH *GeneticAlgotithm(
    TSP *tsp, 
    const PATH *initial_path,
    float cut1,
    float cut2
);