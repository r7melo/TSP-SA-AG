## Instalar o Compilador

```
winget install -e --id BrechtSanders.WinLibs.POSIX.UCRT
gcc --version
```

## Compilacao

```
gcc main.c sources/*.c -Iheads -lm -o main.exe
```

## Execucao

```
.\main.exe < data\tsp29.tsp > data\estimados\tsp29.tsp.tour
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

## Avaliacao experimental

O script abaixo compila o projeto, executa todas as instancias `.tsp` em `data/in/`, grava os tours em `data/out/` e gera um CSV com tempo e custo:

```powershell
.\scripts\benchmark.ps1
```
