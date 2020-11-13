prog : testStack.o stack.o
	gcc testStack.o stack.o -o prog
testStack.o : testStack.c stack.h
	gcc -c testStack.c -o testStack.o
stack.o : stack.c stack.h
	gcc -c stack.c -o stack.o	
clean :
	rm *.o prog

