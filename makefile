CC = gcc
CFLAGS = -Wall -std=c99

all: CardYard

CardYard: main.o jeu.o affichage.o
	$(CC) $(CFLAGS) -o CardYard main.o jeu.o affichage.o

main.o: main.c jeu.h affichage.h
	$(CC) $(CFLAGS) -c main.c

jeu.o: jeu.c jeu.h
	$(CC) $(CFLAGS) -c jeu.c

affichage.o: affichage.c jeu.h
	$(CC) $(CFLAGS) -c affichage.c

clean:
	rm -f *.o CardYard
