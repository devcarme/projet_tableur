prog : testCellule.o cellule.o ../liste/liste.o
	gcc -g testCellule.o cellule.o ../liste/liste.o -o prog
testCellule.o : testCellule.c cellule.h cellule.c ../liste/liste.o
	gcc -c -g testCellule.c -o testCellule.o
cellule.o : cellule.c cellule.h ../liste/liste.h ../liste/liste.o
	gcc -c -g cellule.c -o cellule.o
clean :
	rm *.o prog

