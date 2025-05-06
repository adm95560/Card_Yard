PROG = projet

SRC = main.c jeu.c affichage.c  

all: $(PROG)
   ./$(PROG)
$(PROG): $(SRC) jeu.h
       gcc-o $(PROG) $(SRC)

clean:
     rm -f $(PROG)
