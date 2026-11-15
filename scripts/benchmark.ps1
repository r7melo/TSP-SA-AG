$dataDir = "data\in"
$outDir  = "data\out"
$infoCsv = "data\vlsi_info.csv"
$resultsCsv = "data\results.csv"

# Verificação se a pasta de saída existe
if(-Not (Test-Path $outDir)) {
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null
}

# Carrega as referências (melhor conhecido) do CSV
if(-Not (Test-Path $infoCsv)) {
    Write-Host "Arquivo $infoCsv não encontrado. Script cancelado" -ForegroundColor Red
    exit
}
$infoRows = Import-Csv -Path $infoCsv
$infoLookup = @{}
foreach ($row in $infoRows) {
    $infoLookup[$row.numero] = $row
}

# Compilação do projeto
Write-Host "Compilando o projeto ..." -ForegroundColor Green

gcc main.c sources/*.c -Iheads -lm -o main.exe

if($LASTEXITCODE -ne 0) {
    Write-Host "Erro na compilação. Script cancelado" -ForegroundColor Red
    exit
}

Write-Host "Projeto compilado" -ForegroundColor Green

# Cabeçalho do CSV de resultados
"Instancia,MelhorConhecido,MeuResultado,GapPercent,TempoMs" | Out-File -FilePath $resultsCsv -Encoding utf8

Write-Host "Processando instâncias (em ordem de numero de cidades)..." -ForegroundColor Gray

# Pega os arquivos e ordena numericamente pelo nome (quantidade de cidades)
$arquivosTsp = Get-ChildItem -Path $dataDir -Filter "*.tsp" -File | Sort-Object { [int]$_.BaseName }

foreach ($arquivo in $arquivosTsp) {
    $nomeBase = $arquivo.Name
    $numero = $arquivo.BaseName
    $caminhoEntrada = $arquivo.FullName
    $caminhoSaida = "$outDir\$nomeBase.tour"

    Write-Host "Processando [$nomeBase]..." -NoNewline

    # Mede o tempo exato de execução do main.exe
    $tempo = Measure-Command {
        $comando = "/c `".\main.exe < `"$caminhoEntrada`" > `"$caminhoSaida`"`""
        Start-Process -FilePath "cmd.exe" -ArgumentList $comando -Wait -NoNewWindow
    }

    # Extração do Custo Total gerado
    $custo = $null
    if (Test-Path $caminhoSaida) {
        $conteudoSaida = Get-Content $caminhoSaida -Raw
        if ($conteudoSaida -match "(?i)TOTAL_WEIGHT[^\d]*(\d+(\.\d+)?)") {
            $custo = [double]$matches[1]
        }
    }

    # Busca o melhor conhecido no CSV de referência
    $melhor = $null
    if ($infoLookup.ContainsKey($numero)) {
        $valorTour = $infoLookup[$numero].tour
        if ($valorTour) {
            $melhor = [double]($valorTour -replace '\.', '')
        }
    }

    # Calcula o gap percentual (quanto o meu resultado ficou acima do melhor)
    $gapPercent = "N/A"
    if ($melhor -and $custo) {
        $gapPercent = [math]::Round((($custo - $melhor) / $melhor) * 100, 4)
    }

    $tempoMs = [math]::Round($tempo.TotalMilliseconds, 2)

    $custoStr  = if ($custo)  { $custo }  else { "N/A" }
    $melhorStr = if ($melhor) { $melhor } else { "N/A" }

    "$numero,$melhorStr,$custoStr,$gapPercent,$tempoMs" | Out-File -FilePath $resultsCsv -Append -Encoding utf8

    Write-Host " Concluído em ${tempoMs}ms (Melhor: $melhorStr | Meu: $custoStr | Gap: $gapPercent%)" -ForegroundColor DarkGray
}

Write-Host "Resultados salvos em $resultsCsv" -ForegroundColor Green