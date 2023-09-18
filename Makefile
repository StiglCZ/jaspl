CC=g++
CFLAGS= -c -Wall

all: mkdir bin/parser.o bin/tokenizer.o bin/common.o
	$(CC) src/program.cpp bin/parser.o bin/tokenizer.o bin/common.o -o bin/jaspl
clean:
	rm -rf bin

bin/common.o: src/common.cpp
	$(CC) $(CFLAGS) src/common.cpp -o bin/common.o
bin/parser.o: src/parser.cpp
	$(CC) $(CFLAGS) src/parser.cpp -o bin/parser.o

bin/tokenizer.o: src/tokenizer.cpp
	$(CC) $(CFLAGS) src/tokenizer.cpp -o bin/tokenizer.o
mkdir:
	mkdir -p bin