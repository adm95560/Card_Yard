# Nom de l'exécutable
PROG = projet

# Sources et objets
SRC = main.c jeu.c affichage.c 
OBJ = $(SRC:.c=.o)

# Options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -g

# Règle principale
all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f *.o $(PROG)
