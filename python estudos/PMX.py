def pmx_crossover(pai1, pai2, cut1, cut2):
    tamanho = len(pai1)
    filho = [None] * tamanho

    # 1. Copia a fatia do Pai 1 para o filho (preserva a posição absoluta)
    filho[cut1:cut2] = pai1[cut1:cut2]

    # 2. Cria a tabela de mapeamento do corte (Pai 1 -> Pai 2)
    # Mapeia qual elemento do Pai 1 ocupou a vaga de qual elemento do Pai 2
    mapeamento = {}
    for i in range(cut1, cut2):
        mapeamento[pai1[i]] = pai2[i]

    print(f"1. Fatia do Pai 1 copiada: {filho}")
    print(f"2. Tabela de Mapeamento: {mapeamento}\n")

    # 3. Preenche as posições fora do corte usando os elementos do Pai 2
    for i in range(tamanho):
        # Pula as posições centrais que já foram preenchidas
        if cut1 <= i < cut2:
            continue

        val = pai2[i]

        # Se o valor já está na fatia central do filho, resolve o conflito em cadeia
        while val in filho[cut1:cut2]:
            val_antigo = val
            val = mapeamento[val]
            print(f"   ⚠️ Conflito na pos {i}: {val_antigo} já existe -> Mapeado para {val}")

        filho[i] = val
        print(f"   Posição {i} preenchida com {val} -> Estado: {filho}")

    return filho


# --- TESTE PRÁTICO ---
pai1 = [1, 5, 4, 7, 8, 2, 3, 6]
pai2 = [1, 8, 3, 4, 5, 6, 2, 7]

# TESTE PARA SEQUENCIA DE CONFLITOS
# pai1 = [1, 5, 4, 2, 3, 7, 8, 6]
# pai2 = [1, 8, 6, 3, 7, 5, 2, 4]

# Pontos de corte: índices 3 a 6 (posições 4, 5 e 6 do vetor)
cut1, cut2 = 3, 6

print(f"Pai 1: {pai1}")
print(f"Pai 2: {pai2}\n")

resultado = pmx_crossover(pai1, pai2, cut1, cut2)

print("\n" + "=" * 45)
print(f"Resultado Final (Filho 1): {resultado}")
print(f"É uma permutação válida? {sorted(resultado) == sorted(pai1)}")  # Deve ser True