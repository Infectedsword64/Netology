FROM ubuntu:16.04
COPY . /usr/src/Docker
WORKDIR /usr/src/Docker
RUN apt update
RUN apt update && \
    apt install -y --no-install-recommends clang nano && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*
RUN clang++ -o Task_1 Task_1.cpp
CMD ["./Task_1"]