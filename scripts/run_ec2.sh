#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
cd "$PROJECT_ROOT"

IMAGE_NAME="tsp-benchmark"

echo "=== 1. Atualizando repositório ==="
git fetch --all
git pull --ff-only

echo "=== 2. Coletando informações do hardware ==="
CPU_COUNT=$(nproc)
RAM_GB=$(free -g | awk '/^Mem:/ {print $2}')
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")

OUTPUT_CSV="${1:-data/results_${CPU_COUNT}vcpu_${RAM_GB}GB_${TIMESTAMP}.csv}"

echo "Hardware: ${CPU_COUNT} vCPUs | ${RAM_GB} GB RAM"
echo "Arquivo de saída: ${OUTPUT_CSV}"

echo "=== 3. Construindo imagem Docker ==="
docker build -t "$IMAGE_NAME" .

echo "=== 4. Executando benchmark no container ==="
mkdir -p data/out
docker run --rm \
    -v "${PROJECT_ROOT}/data:/app/data" \
    "$IMAGE_NAME" \
    bash scripts/benchmark.sh "$OUTPUT_CSV"

echo "=== Concluído com sucesso! ==="
echo "Resultados salvos em: ${OUTPUT_CSV}"