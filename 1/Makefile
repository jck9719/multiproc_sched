CC = gcc -Wall -pedantic -std=c17
VL = valgrind --leak-check=full -v --track-origins=yes

all : utils main final

utils :
	$(CC) -c -g src/utils.c -o output/utils.o

main :
	$(CC) -c -g src/main.c -o output/main.o

final : 
	$(CC) -o output/main output/main.o output/utils.o

run :
	./output/main

full : clean run

c :
	rm output/main output/main.o output/utils.o

val :
	$(VL) ./output/main 
