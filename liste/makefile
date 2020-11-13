prog : testList.o liste.o
	gcc testList.o liste.o -o prog
testList.o : testList.c liste.c liste.h
	gcc -c testList.c -o testList.o
liste.o : liste.c liste.h
	gcc -c liste.c -o liste.o
clean :
	rm *.o prog

