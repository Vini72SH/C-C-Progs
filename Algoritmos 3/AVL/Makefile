# Flags de Compilação
CDFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lm
CC = gcc

objects = AVL.o clienteAVL.o

all: clienteAVL

clienteAVL: clienteAVL.o AVL.o
	$(CC) -o clienteAVL clienteAVL.o AVL.o $(LDFLAGS)

clienteAVL.o: clienteAVL.c
	$(CC) -c $(CDFLAGS) clienteAVL.c

AVL.o: AVL.c AVL.h
	$(CC) -c $(CDFLAGS) AVL.c

clean:
	rm -f $(objects)

purge:
	rm -f $(objects) clienteAVL