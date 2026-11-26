#include "genetic_algorithm.h"
#include <math.h>
#include "error.h"
#include <string.h>
#include "logger.h"

#define FALSE 0
#define TRUE 1

PATH *MutationInsert(PATH *path) {
    size_t n = path->dimension;

    size_t curr_pos = rand() % n;
    size_t new_pos = rand() % (n - 1);
    if (new_pos >= curr_pos) new_pos++;

    int *nodes = path->nodes_index;

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

    return path;
}

PATH *MutationSwap(PATH *path) {
    size_t n = path->dimension;

    // Sorteia i e j garantindo i != j
    size_t i = rand() % n;
    size_t j = rand() % (n - 1);
    if (j >= i) j++;

    int temp = path->nodes_index[i];
    path->nodes_index[i] = path->nodes_index[j];
    path->nodes_index[j] = temp;

    return path;
}

PATH *MutationRandom(PATH *path) {
    if (rand() % 2 == 0) {
        return MutationInsert(path);
    } else {
        return MutationSwap(path);
    }
}

PATH *CrossoverOX(const PATH *parent1, const PATH *parent2, const float point1, const float point2){
    
    size_t N = (size_t) parent1->dimension;

    size_t cut1 = (size_t)(point1 * N);
    size_t cut2 = (size_t)(point2 * N);

    PATH *child = PathCopyPartial(parent1, cut1, cut2);

    size_t jump = 0;
    for (size_t i = 0; i < N; i++)
    {
        size_t idx = (cut2 + i) % N;

        if (cut1 <= idx && idx < cut2)
            continue;

        int element;
        int element_is_valid = FALSE;

        while (!element_is_valid)
        {
            int idx_jump = (idx + jump) % N;
            element = parent2->nodes_index[idx_jump];
            element_is_valid = TRUE;

            for (size_t j = cut1; j < cut2; j++)
            {
                if (element == child->nodes_index[j])
                {
                    element_is_valid = FALSE;
                    jump++;
                    break;
                }
            }            
        }

        child->nodes_index[idx] = element;
    }

    return child;
}


PATH *CrossoverCX(const PATH *parent1, const PATH *parent2){
    PATH *child = PathCopy(parent1);
    return child;
}

PATH *CrossoverPMX(const PATH *parent1, const PATH *parent2){
    PATH *child = PathCopy(parent1);
    return child;
}

PATH *CrossoverGNX(const PATH *parent1, const PATH *parent2){
    PATH *child = PathCopy(parent1);
    return child;
}

