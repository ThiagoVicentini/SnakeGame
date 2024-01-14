flags = -lglut -lGLU -lGL -Wall

all: build

run: build
	./bin/main

build: main.o

main.o: src/main.cpp
	@g++ src/main.cpp -o ./bin/main $(flags)

clean:
	@rm ./bin/*
	clear