#include "simulated_annealing.h"
#include <math.h>
#include "error.h"
#include <string.h>
#include "logger.h"


PATH *InsertOperator(const PATH *path) {
    size_t n = path->dimension;

    size_t curr_pos = rand() % n;
    size_t new_pos = rand() % (n - 1);
    if (new_pos >= curr_pos) new_pos++;

    PATH *path_copy = PathCopy(path);
    int *nodes = path_copy->nodes_index;

    size_t start, end;
    int shift;

    if (curr_pos > new_pos) {
        start = new_pos;
        end = curr_pos;
        shift = 1;
    } else {
        start = curr_pos;
        end = new_pos;
        shift = -1;
    }

    int moved = nodes[curr_pos];

    size_t src_offset = (shift == 1) ? start : start + 1;
    size_t dst_offset = (shift == 1) ? start + 1 : start;

    memmove(nodes + dst_offset, nodes + src_offset, (end - start) * sizeof(int));
    nodes[new_pos] = moved;

    return path_copy;
}

PATH *SwapOperator(const PATH *path) {
    size_t n = path->dimension;

    // Sorteia i e j garantindo i != j
    size_t i = rand() % n;
    size_t j = rand() % (n - 1);
    if (j >= i) j++;

    PATH *path_copy = PathCopy(path);

    int temp = path_copy->nodes_index[i];
    path_copy->nodes_index[i] = path_copy->nodes_index[j];
    path_copy->nodes_index[j] = temp;

    return path_copy;
}

PATH *RandomOperator(const PATH *path) {
    if (rand() % 2 == 0) {
        return InsertOperator(path);
    } else {
        return SwapOperator(path);
    }
}

PATH *SimulatedAnnealing(
    TSP *tsp, 
    const PATH *initial_path, 
    double initial_temp, 
    double final_temp, 
    double cooling_rate, 
    int max_iter_per_temp
) {
    
    if (!tsp || !initial_path || initial_path->dimension < 2) {
        fprintf(stderr, "Erro em SimulatedAnnealing.\n");
        exit(EXIT_FAILURE);
    }

    PATH *current_path = PathCopy(initial_path);
    PATH *best_path = PathCopy(initial_path);

    int current_cost = CalculatePathTotalDist(tsp, current_path);
    int best_cost = current_cost;
    double temp = initial_temp;
    int step = 0;

    while (temp > final_temp) {
        for (int iter = 0; iter < max_iter_per_temp; iter++) {
            PATH *neighbor_path = RandomOperator(current_path);
            int neighbor_cost = CalculatePathTotalDist(tsp, neighbor_path);

            int delta = neighbor_cost - current_cost;

            // Critério de Metropolis
            if (delta < 0 || ((double)rand() / RAND_MAX) < exp(-(double)delta / temp)) {
                DeconstructPath(current_path);
                current_path = neighbor_path;
                current_cost = neighbor_cost;

                if (current_cost < best_cost) {
                    DeconstructPath(best_path);
                    best_path = PathCopy(current_path);
                    best_cost = current_cost;
                }
            } else {
                DeconstructPath(neighbor_path);
            }
        }

        PrintLog("%d\ttemp=%.6f current_cost=%d best_cost=%d\n", ++step, temp, current_cost, best_cost);

        best_path->total_weight = best_cost;
        temp *= cooling_rate;
    }

    DeconstructPath(current_path);
    return best_path;
}