all: final clean

final: coordinate.o player.o chainlist.o battlefield.o main.o
	gcc -o chain_heal coordinate.o player.o chainlist.o battlefield.o main.o -lm

main.o:
	gcc -c main.c

battlefield.o:
	gcc -c battlefield.c

chainlist.o:
	gcc -c chainlist.c

player.o:
	gcc -c player.c

coordinate.o:
	gcc -c coordinate.c

clean: 
	rm -rf *.o