prog : testCellule.o cellule.o
	gcc -g testCellule.o cellule.o -o prog
testCellule.o : testCellule.c cellule.h cellule.c liste.h 
	gcc -c -g testCellule.c -o testCellule.o
cellule.o : cellule.c cellule.h liste.h
	gcc -c -g cellule.c -o cellule.o
clean :
	rm *.o prog

