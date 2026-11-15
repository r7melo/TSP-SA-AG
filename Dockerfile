FROM gcc:13-bookworm

WORKDIR /app

COPY . .

RUN mkdir -p data/out && \
    chmod +x scripts/benchmark.sh && \
    gcc -O3 main.c sources/*.c -Iheads -lm -o main

CMD ["bash", "scripts/benchmark.sh"]