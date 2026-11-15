#include <stdbool.h>
#include <stdlib.h>
#include "optimizer.h"

// Calcula a distância total da rota atual
double TwoOptTotalDistance(int *route, int n, TSP *tsp)
{
    double total = 0;
    for (int i = 0; i < n; i++)
    {
        total += TSPDistance(tsp, route[i], route[(i + 1) % n]);
    }
    return total;
}

// Copia os elementos de um array para outro
void TwoOptCopyRoute(int *destino, int *origem, int n)
{
    for (int i = 0; i < n; i++)
    {
        destino[i] = origem[i];
    }
}

// Etapa de Embaralhamento 
void TwoOptShuffling(int *route, int n)
{
    // Escolhe um índice aleatório garantindo que existam 5 posições à frente
    int start = rand() % (n - 5);

    int b1_0 = route[start];
    int b1_1 = route[start + 1];
    int b1_2 = route[start + 2];

    route[start] = route[start + 3];
    route[start + 1] = route[start + 4];

    route[start + 2] = b1_0;
    route[start + 3] = b1_1;
    route[start + 4] = b1_2;
}

// 2-Opt Clássico
int TwoOptMutation(int *route, int n, TSP *tsp)
{
    int swaps_locais = 0;

    while (true)
    {
        bool improved = false;

        for (int i = 0; i < n - 2; i++)
        {
            for (int j = i + 2; j < n; j++)
            {
                if (i == 0 && j == n - 1)
                    continue;

                int a = route[i];
                int b = route[i + 1];
                int c = route[j];
                int d = route[(j + 1) % n];

                double before = TSPDistance(tsp, a, b) + TSPDistance(tsp, c, d);
                double after = TSPDistance(tsp, a, c) + TSPDistance(tsp, b, d);

                if (after + 1e-9 < before)
                {
                    // Inverte o segmento
                    int left = i + 1;
                    int right = j;
                    while (left < right)
                    {
                        int tmp = route[left];
                        route[left] = route[right];
                        route[right] = tmp;
                        left++;
                        right--;
                    }
                    swaps_locais++;
                    improved = true;
                }
            }
        }
        // Para a mutação local se não houver mais melhorias
        if (!improved)
            break;
    }

    return swaps_locais;
}

int ApplyTwoOpt(int *route, int n, TSP *tsp, int max_iter)
{
    if (n <= 5)
        return 0; // O embaralhamento precisa de pelo menos 5 nós

    int total_swaps = 0;

    // Aloca memória para rastrear a melhor rota global
    int *best_route = (int *)malloc(n * sizeof(int));
    TwoOptCopyRoute(best_route, route, n);
    double best_distance = TwoOptTotalDistance(best_route, n, tsp);

    // Loop de otimização
    for (int iter = 0; iter < max_iter; iter++)
    {

        // 1. Aplica o Shuffling (A partir da 2ª iteração)
        if (iter > 0)
        {
            TwoOptShuffling(route, n);
        }

        // 2. Aplica a Mutação Local (2-Opt) e soma os swaps realizados
        total_swaps += TwoOptMutation(route, n, tsp);

        // 3. Critério de Aceitação Global
        double current_distance = TwoOptTotalDistance(route, n, tsp);

        if (current_distance < best_distance)
        {
            // Encontrou uma rota melhor, atualiza a memória global
            best_distance = current_distance;
            TwoOptCopyRoute(best_route, route, n);
        }
        else
        {
            // Rota piorou. Reverte para o melhor estado conhecido antes do próximo shuffle
            TwoOptCopyRoute(route, best_route, n);
        }
    }

    free(best_route);
    return total_swaps;
}