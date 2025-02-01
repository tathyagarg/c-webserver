CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99

SRC := src
BIN := bin
INCLUDE := include

BIN_OPTS := --port 8080

all: build run

build: $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/main $(wildcard $(SRC)/*.c) -I$(INCLUDE)

run: $(BIN)/main
	$(BIN)/main $(BIN_OPTS)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/main: build

