#!/usr/bin/env bash
set -e

DATA_DIR="data/in"
OUT_DIR="data/out"
INFO_CSV="data/vlsi_info.csv"
RESULTS_CSV="${1:-data/results.csv}" # Aceita nome customizado ou usa data/results.csv

mkdir -p "$OUT_DIR"

if [ ! -f "$INFO_CSV" ]; then
    echo "Arquivo $INFO_CSV não encontrado. Script cancelado" >&2
    exit 1
fi

echo "Compilando o projeto ..."
gcc -O3 main.c sources/*.c -Iheads -lm -o main
echo "Projeto compilado"

# Cabeçalho exato do seu benchmark.ps1
echo "Instancia,MelhorConhecido,MeuResultado,GapPercent,TempoMs" > "$RESULTS_CSV"

echo "Processando instâncias (em ordem de numero de cidades)..."

# Lista os .tsp, extrai o nome base e ordena numericamente
mapfile -t numeros < <(
    find "$DATA_DIR" -maxdepth 1 -name "*.tsp" -printf "%f\n" \
    | sed 's/\.tsp$//' \
    | sort -n
)

for numero in "${numeros[@]}"; do
    nome_base="${numero}.tsp"
    caminho_entrada="${DATA_DIR}/${nome_base}"
    caminho_saida="${OUT_DIR}/${nome_base}.tour"

    printf "Processando [%s]..." "$nome_base"

    # Mede o tempo em nanosegundos e converte para milissegundos com 2 casas decimais
    inicio_ns=$(date +%s%N)
    ./main < "$caminho_entrada" > "$caminho_saida"
    fim_ns=$(date +%s%N)

    tempo_ms=$(awk -v ini="$inicio_ns" -v fim="$fim_ns" 'BEGIN { printf "%.2f", (fim - ini) / 1000000 }')

    # Extração do TOTAL_WEIGHT gerado
    custo=""
    if [ -f "$caminho_saida" ]; then
        custo=$(grep -i "TOTAL_WEIGHT" "$caminho_saida" | grep -oE '[0-9]+(\.[0-9]+)?' | head -n 1)
    fi

    # Busca o melhor conhecido em data/vlsi_info.csv (removendo pontos de milhar)
    melhor=$(awk -F',' -v num="$numero" '
        NR == 1 {
            for (i = 1; i <= NF; i++) {
                gsub(/\r|"/, "", $i)
                if ($i == "numero") col_num = i
                if ($i == "tour")   col_tour = i
            }
            next
        }
        {
            gsub(/\r|"/, "", $col_num)
            if ($col_num == num) {
                gsub(/\r|"|\./, "", $col_tour)
                print $col_tour
                exit
            }
        }
    ' "$INFO_CSV")

    # Calcula GapPercent e formata strings
    custo_str="${custo:-N/A}"
    melhor_str="${melhor:-N/A}"
    gap_percent="N/A"

    if [ -n "$melhor" ] && [ -n "$custo" ]; then
        gap_percent=$(awk -v c="$custo" -v m="$melhor" 'BEGIN { printf "%.4f", ((c - m) / m) * 100 }')
    fi

    echo "${numero},${melhor_str},${custo_str},${gap_percent},${tempo_ms}" >> "$RESULTS_CSV"
    echo " Concluído em ${tempo_ms}ms (Melhor: ${melhor_str} | Meu: ${custo_str} | Gap: ${gap_percent}%)"
done

echo "Resultados salvos em $RESULTS_CSV"