#pragma once
#include "tsp.h"

double TwoOptTotalDistance(int *route, int n, TSP *tsp);
void TwoOptCopyRoute(int *dest, int *orig, int n);
void TwoOptShuffling(int *route, int n);
int TwoOptMutation(int *route, int n, TSP *tsp);
int ApplyTwoOpt(int *route, int n, TSP *tsp, int max_iter);