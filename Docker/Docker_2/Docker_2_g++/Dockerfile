FROM ubuntu:16.04
COPY . /usr/src/Docker
WORKDIR /usr/src/Docker
RUN apt update
RUN apt install -y g++ nano
RUN g++ -o Task_1 Task_1.cpp
CMD ["./Task_1"]