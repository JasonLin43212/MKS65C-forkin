all: fork.o
	gcc fork.o

fork.o: fork.c
	gcc -c fork.c

run:
	./a.out

clear:
	rm *.o
	rm *.out
