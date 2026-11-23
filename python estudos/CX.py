def cx_crossover(pai1, pai2):
    N = len(pai1)
    filho = [-1] * N  # -1 significa "nó ainda não visitado"

    # 1. Monta o índice invertido do pai1 (onde cada valor está)
    # (Se os valores forem 1..N, use tamanho N + 1)
    pos_no_pai1 = [0] * (N + 1)
    for i in range(N):
        pos_no_pai1[pai1[i]] = i

    # 2. Percorre o ciclo direto no grafo (para quando bater em um nó já visitado)
    idx = 0
    while filho[idx] == -1:
        filho[idx] = pai1[idx]          # Copia do pai1 e já marca como visitado
        idx = pos_no_pai1[pai2[idx]]    # Pula para o próximo nó do grafo em O(1)

    # 3. Todo nó não visitado (-1) recebe o gene do pai2
    for i in range(N):
        if filho[i] == -1:
            filho[i] = pai2[i]

    return filho


# --- TESTE PRÁTICO ---
pai2 = [1, 2, 3, 4, 5, 6, 7, 8]
pai1 = [8, 7, 6, 5, 3, 4, 2, 1]

resultado = cx_crossover(pai1, pai2)

print("\n" + "=" * 50)
print(f"Resultado Final (Filho CX): {resultado}")
print(
    f"Permutação válida (sem repetições)? {sorted(resultado) == sorted(pai1)}"
)