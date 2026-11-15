#pragma once

#include "path.h"

PATH *InsertOperator(const PATH *path);
PATH *SwapOperator(const PATH *path);
PATH *RandomOperator(const PATH *path);
PATH *SimulatedAnnealing(
    TSP *tsp, 
    const PATH *initial_path, 
    double initial_temp, 
    double final_temp, 
    double cooling_rate, 
    int max_iter_per_temp
);