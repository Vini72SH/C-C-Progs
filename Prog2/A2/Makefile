# Flags de Compilação
CDFLAGS = -Wall -Werror -g
LDFLAGS = -lm
CC = gcc

# Arquivos-objeto
objects = csvreader.o lista.o ordena.o io.o aux.o filtros.o

all: csvreader

csvreader: csvreader.o io.o lista.o ordena.o aux.o filtros.o
	$(CC) -o csvreader csvreader.o io.o lista.o ordena.o aux.o filtros.o $(LDFLAGS)

csvreader.o: csvreader.c 
	$(CC) -c $(CDFLAGS) csvreader.c

io.o: io.c io.h
	$(CC) -c $(CDFLAGS) io.c

lista.o: lista.c lista.h
	$(CC) -c $(CDFLAGS) lista.c

ordena.o: ordena.c ordena.h
	$(CC) -c $(CDFLAGS) ordena.c

aux.o: aux.c aux.h
	$(CC) -c $(CDFLAGS) aux.c

filtros.o: filtros.c filtros.h
	$(CC) -c $(CDFLAGS) filtros.c

clean:
	rm -f $(objects)

purge: 
	rm -f $(objects) csvreader
