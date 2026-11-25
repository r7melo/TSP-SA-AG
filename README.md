> Todos os comandos são para windows via cmd

## Instalar o Compilador

windows
```
winget install -e --id BrechtSanders.WinLibs.POSIX.UCRT
gcc --version
```

linux
```
sudo apt update
sudo apt install build-essential
gcc --version
```

## Compilacao

```
gcc sa.c sources/*.c -Iheads -lm -o sa.exe
```

```
gcc ag.c sources/*.c -Iheads -lm -o ag.exe
```

## Execucao

windows
```
.\sa.exe < data\in\131.tsp > data\out\131.tsp.tour
```

```
.\ag.exe < data\in\131.tsp > data\out\131.tsp.tour
```

linux
```
./sa.exe < data/in/131.tsp > data/out/131.tsp.tour
```

```
./ag.exe < data/in/131.tsp > data/out/131.tsp.tour
```

## Formato dos dados

As entradas seguem o formato TSPLIB simplificado com coordenadas 2D:

```text
NAME: exemplo
TYPE: TSP
DIMENSION: 3
EDGE_WEIGHT_TYPE: EUC_2D
NODE_COORD_SECTION
1 10 10
2 20 10
3 15 20
EOF
```

A saida segue o formato `.tour`, contendo nome, comentarios, dimensao, peso total estimado e a secao `TOUR_SECTION`, sem mensagens extras no arquivo:

```text
NAME: exemplo
COMMENT:  Simulated Annealing
TYPE: TOUR
DIMENSION: 3
TOTAL_WEIGHT: 34
TOUR_SECTION
1
2
3
EOF
```

## Avaliacao experimental (via Docker)

O script abaixo compila o projeto, executa todas as instancias `.tsp` em `data/in/`, grava os tours em `data/out/` e gera um CSV com tempo e custo em `data/results.csv`:

1. Build da imagem
```
docker build -t tsp-benchmark .
```

2. Executar o benchmark completo
```
docker run --rm -v "%cd%\data:/app/data" tsp-benchmark
```

## Avaliacao experimental (via EC2)



1. Conecte-se com a instancia:
    ```
    ssh -o StrictHostKeyChecking=no -i "<CAMINHO_DA_CHAVE.pem>" ec2-user@<IP_DA_INSTANCIA>
    ```
2. Configure o ambiente através do script `script/setup_ec2.txt`.
3. Rode o script de execução de testes `script/run_ec2.sh`.
4. Capture os dados via protocolo HTTP:
    ```
    sftp -o StrictHostKeyChecking=no -i "<CAMINHO_DA_CHAVE.pem>" ec2-user@<IP_DA_INSTANCIA>
    ```
    ```
    get TSP-SA-AG/data/results.csv data/
    get TSP-SA-AG/data/system_infos.txt data/
    bye
    ```