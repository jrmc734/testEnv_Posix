FROM ubuntu:latest

WORKDIR /app

RUN apt-get update && apt-get install -y build-essential make

COPY . /app

# Executa o build
RUN make clean && make
# Binário em ./bin
CMD ["./bin/controller_bin"]
