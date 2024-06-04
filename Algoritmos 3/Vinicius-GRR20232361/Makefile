# Flags de Compilação
CDFLAGS = -Wall -Werror -g
LDFLAGS = -lm
CC = gcc

objs = qualFilme.o trie.o lista.o

all: qualFilme

qualFilme: $(objs)
	$(CC) -o qualFilme $(objs) $(LDFLAGS)

qualFilme.o: qualFilme.c 
	$(CC) $(CDFLAGS) -c qualFilme.c

trie.o: trie.c trie.h
	$(CC) $(CDFLAGS) -c trie.c

lista.o: lista.c lista.h
	$(CC) $(CDFLAGS) -c lista.c

clean:
	rm -f $(objs)

purge:
	rm -f $(objs) qualFilme

.PHONY: clean purge