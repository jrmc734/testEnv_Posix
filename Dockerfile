FROM ubuntu:latest

WORKDIR /app

COPY . /app

# Executa o build
RUN apt-get update && apt-get install -y \
    build-essential \
    make clean && make

# Binário em ./bin
CMD ["./bin/controller_bin"]
