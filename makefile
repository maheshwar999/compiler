exe: main.c scanner.o parser.o ast.o SymbolTable.o asm.o
	gcc -g main.c asm.o ast.o SymbolTable.o scanner.o parser.o tree.o stack.o -o exe

scanner.o: scanner.c scanner.h
	gcc -g -c scanner.c

tree.o: tree.c tree.h
	gcc -g -c tree.c
	
stack.o: stack.c stackOps.h
	gcc -g -c stack.c
	
parser.o: tree.o stack.o scanner.o parser.c parser.h
	gcc -g -c parser.c 
	
ast.o:	ast.c parser.o scanner.o ast.h parser.h SymbolTable.o
	gcc -g -c ast.c 

SymbolTable.o: SymbolTable.c SymbolTable.h parser.o
	gcc -g -c SymbolTable.c
	
asm.o:	asm.c ast.o asm.h SymbolTable.o
	gcc -g -c asm.c
	
clean:
	rm -rf *.o exe

