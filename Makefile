all: prog

a1.o: externs.c
	gcc externs.c -o a1.o -c -m32 -lm

a2.o: main.c
	gcc main.c -o a2.o -c -m32 -lm

a3.o: asmfunc.asm
	nasm -f elf32 asmfunc.asm -o a3.o

prog: a2.o a1.o a3.o
	gcc a1.o a2.o a3.o -m32 -lm

clean: FORCE
	rm -f 1 *.o
	rm -f 1 *.out

FORCE:
