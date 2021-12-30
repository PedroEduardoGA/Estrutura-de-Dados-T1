progr: progrdin progrest

#arquivos .c
ARQUIVOS_C = $(wildcard *.c)

#wildcard é usado para listar todos os arquivos-fonte no diretório atual

#arquivos .h
ARQUIVOS_H = $(wildcard *.h)

#gera a lista de arquivos-objeto usando a lista de arquivos-fonte
OBJ = $(ARQUIVOS_C:.c=.o)

#compilador
CC = gcc

#flags para o compilador
FLAGS = -Wall -ansi -pedantic -std=c99 -fstack-protector-all -g

#ligação com as bibliotecas
LINKER_FLAGS = -lm

#linking e compilaçao

#all: progrdin
#all: progrest
progrdin: $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LINKER_FLAGS)

progrest: $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LINKER_FLAGS)

%.o: %.c %.h
	$(CC) -o $@ $< -c $(FLAGS) $(LINKER_FLAGS)

main.o: main.c $(ARQUIVOS_H)
	$(CC) -o $@ $< -c $(FLAGS)

clean:
	rm -rf *.o progrdin progrest *~

run: progrdin progrest
	./progrdin ./progrest

