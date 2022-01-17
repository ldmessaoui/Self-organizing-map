CC = gcc -Wall 
SRC = main.c initialisation.c Apprentissage.c fonctions.c 
OBJ = main.o initialisation.o Apprentissage.o fonctions.o

SOM:	$(OBJ) structures.h			$(OBJ) fonctions.h
		
	$(CC) -o SOM $(OBJ) -lm
%.o:	%.c structures.h			%.c fonctions.h

	$(CC) -c $<

clean:
	rm *.o 


