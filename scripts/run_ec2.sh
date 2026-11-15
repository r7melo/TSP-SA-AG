#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
cd "$PROJECT_ROOT"

IMAGE_NAME="tsp-benchmark"

echo "=== 1. Atualizando repositório ==="
git fetch --all
git reset --hard origin/main
chmod +x scripts/run_ec2.sh

echo "=== 2. Salvando informações do sistema ==="
mkdir -p data/out
INFO_TXT="data/system_infos.txt"

{
    echo "=== SISTEMA ==="
    uname -a
    echo "=== CPU ==="
    lscpu | grep -E "Model name|Architecture|CPU\(s\)|Thread|Core|Socket|MHz" || true
    echo "=== MEMORIA ==="
    free -h
    echo "=== DISCO ==="
    df -h /
} > "$INFO_TXT"

echo "Informações da máquina salvas em: ${INFO_TXT}"

echo "=== 3. Construindo imagem Docker ==="
docker build -t "$IMAGE_NAME" .

echo "=== 4. Executando benchmark no container ==="
MSYS_NO_PATHCONV=1 docker run --rm \
    -v "${PROJECT_ROOT}/data:/app/data" \
    "$IMAGE_NAME"

echo "=== Concluído com sucesso! ==="
echo "Ficha técnica: ${INFO_TXT}"
echo "Resultados:    data/results.txt"