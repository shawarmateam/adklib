all: build run

FLAGS ?= -I./include -Wno-builtin-declaration-mismatch -Wimplicit-function-declaration

build:
	mkdir -p ./bin
	gcc ./src/main.c -o ./bin/main ${FLAGS}

run: build
	./bin/main
