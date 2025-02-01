CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99

SRC := src
BIN := bin
INCLUDE := include
STRESS := stress

PORT := 8080

BIN_OPTS := --port $(PORT) 

THREAD_COUNT := 100
BATCH_SIZE := 100

.PHONY: stress

all: build run

build: $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/main $(wildcard $(SRC)/*.c) -I$(INCLUDE)

run: $(BIN)/main
	$(BIN)/main $(BIN_OPTS)

stress:
	python $(STRESS)/main.py --host localhost --port $(PORT) --thread_count $(THREAD_COUNT) --batch_size $(BATCH_SIZE)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/main: build

