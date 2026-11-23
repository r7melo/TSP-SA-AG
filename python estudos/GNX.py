import random

def preencher_segmentos(filho, pai1, pai2, fatias, pais_por_segmento):
    tamanho = len(pai1)
    num_segmentos = len(fatias)
    
    for f in range(num_segmentos):
        inicio, fim = fatias[f]
        n_pai = pais_por_segmento[f]
        pai = pai1 if n_pai == 1 else pai2
    
        print(f"Pai{n_pai} sorteado")
        for i in range(inicio, fim):
            if filho[i] != None: continue
                
            gene = pai[i]
    
            gene_valido = True
            for j in range(tamanho):
                if gene == filho[j]:
                    gene_valido = False
                    print(f"\tGene {gene} do pai{n_pai} é invalido")
                    break
    
            if gene_valido:
                filho[i] = gene
                print(f"Copia o gene {gene} do pai{n_pai} para o filho")
        

def gnx_crossover(pai1, pai2, cut_points):
      

    tamanho = len(pai1)
    filho = [None] * tamanho

    pontos = [0] + sorted(cut_points) + [tamanho]
    fatias = [(pontos[i], pontos[i + 1]) for i in range(len(pontos) - 1)]
    num_segmentos = len(fatias)
    pais_fase1 = [random.choice([1, 2]) for _ in range(num_segmentos)]
    pais_fase2 = [2 if p == 1 else 1 for p in pais_fase1]

    print(f"Pai 1: {pai1}")
    print(f"Pai 2: {pai2}")
    print(f"Fatias definidas pelos cortes {cut_points}: {fatias}\n")


    # --- FASE 1: Teste e Transferência de Segmentos ---
    preencher_segmentos(filho, pai1, pai2, fatias, pais_fase1)
    print(f"\nEstado após Fase 1: {filho}\n")

    # --- FASE 2: Teste de Segmentos Alternativos para Lacunas ---
    preencher_segmentos(filho, pai1, pai2, fatias, pais_fase2)
    print(f"\nEstado após Fase 2: {filho}\n")

    # --- FASE 3: Reparo Aleatório (se restar alguma lacuna) ---
    presente = [0] * (tamanho + 1)
    for i in range(tamanho):
        if filho[i] is not None:
            presente[filho[i]] = 1

    presente

    elementos_faltantes = []
    for gene in range(1, tamanho + 1):
        if presente[gene] == 0:
            elementos_faltantes.append(gene)

    elementos_faltantes

    qtd_faltantes = len(elementos_faltantes)

    if qtd_faltantes > 0:
        print("--- FASE 3: Reparo Aleatório ---")
        print(f"Elementos faltantes para alocar: {elementos_faltantes}")

        # Embaralhamento Fisher-Yates
        for i in range(qtd_faltantes - 1, 0, -1):
            r = random.randint(0, i)
            temp = elementos_faltantes[i]
            elementos_faltantes[i] = elementos_faltantes[r]
            elementos_faltantes[r] = temp

        print(f"Embaralhados: {elementos_faltantes}")

        idx_faltante = 0
        for i in range(tamanho):
            if filho[i] is None:
                val = elementos_faltantes[idx_faltante]
                filho[i] = val
                idx_faltante += 1
                print(f"\tPosição {i} -> Reparado com {val} | Estado: {filho}")

    return filho


# --- TESTE PRÁTICO ---
pai1 = [1, 2, 3, 7, 8, 9, 4, 5, 6, 10, 11, 12]
pai2 = [4, 5, 6, 1, 2, 3, 10, 11, 12, 7, 8, 9]
cut_points = [3, 6, 9] 

random.seed(42)
resultado = gnx_crossover(pai1, pai2, cut_points)

print("\n" + "=" * 55)
print(f"Resultado Final (Filho GNX): {resultado}")
print(
    f"Permutação válida (sem repetições)? {sorted(resultado) == sorted(pai1)}"
)