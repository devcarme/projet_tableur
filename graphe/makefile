prog : testGraphe.o graphe.o ../liste/liste.o ../stack/stack.o ../cellule/cellule.o 
	gcc -g testGraphe.o graphe.o ../liste/liste.o ../stack/stack.o ../cellule/cellule.o  -o prog
testGraphe.o : testGraphe.c graphe.h graphe.c ../liste/liste.o ../stack/stack.o ../cellule/cellule.o
	gcc -c -g testGraphe.c -o testGraphe.o
graphe.o : graphe.c graphe.h ../liste/liste.h ../liste/liste.o ../stack/stack.o ../stack/stack.h
	gcc -c -g graphe.c -o graphe.o
clean :
	rm *.o prog

