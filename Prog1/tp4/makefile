# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Wextra -Werror -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_pilha.o pilha.o 
     
all: testa_pilha.o pilha.o
	$(CC) -o testa_pilha testa_pilha.o pilha.o $(LDFLAGS)

pilha.o: pilha.c
	$(CC) -c $(CFLAGS) pilha.c

testa_pilha.o: testa_pilha.c
	$(CC) -c $(CFLAGS) testa_pilha.c

clean:
	rm -f $(objects) testa_pilha


