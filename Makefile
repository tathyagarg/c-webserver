CC := gcc
CFLAGS := -Wall -Werror -pedantic -std=gnu99

SRC := src
BIN := bin
INCLUDE := include
STRESS := stress

PORT ?= 8080
BIN_NAME ?= main

BIN_OPTS := --port $(PORT) 

THREAD_COUNT := 100
BATCH_SIZE := 100

.PHONY: stress

all: build run

build: $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/$(BIN_NAME) $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/handlers/*.c) -I$(INCLUDE)

run: $(BIN)/main
	$(BIN)/$(BIN_NAME) $(BIN_OPTS)&

stress:
	python $(STRESS)/main.py --host localhost --port $(PORT) --thread_count $(THREAD_COUNT) --batch_size $(BATCH_SIZE)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/$(BIN_NAME): build

kill:
	pkill $(BIN_NAME)
