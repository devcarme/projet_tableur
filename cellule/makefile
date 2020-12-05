prog : testCellule.o cellule.o ../liste/liste.o ../stack/stack.o
	gcc -g testCellule.o cellule.o ../liste/liste.o ../stack/stack.o -o prog
testCellule.o : testCellule.c cellule.h cellule.c ../liste/liste.o ../stack/stack.o
	gcc -c -g testCellule.c -o testCellule.o
cellule.o : cellule.c cellule.h ../liste/liste.h ../liste/liste.o ../stack/stack.o ../stack/stack.h
	gcc -c -g cellule.c -o cellule.o
clean :
	rm *.o prog

