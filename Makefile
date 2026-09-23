# ==============================================================================
# Makefile - Projetos e Algoritmos em C
# Automação de build para os projetos acadêmicos de Estruturas de Dados e C
# ==============================================================================

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGETS = agenda_contatos algoritmos_ordenacao estruturas_fila_pilha montador_neander

all: $(TARGETS)

agenda_contatos: agenda_contatos.c
	$(CC) $(CFLAGS) -o agenda_contatos agenda_contatos.c

algoritmos_ordenacao: algoritmos_ordenacao.c
	$(CC) $(CFLAGS) -o algoritmos_ordenacao algoritmos_ordenacao.c -lm

estruturas_fila_pilha: estruturas_fila_pilha.c
	$(CC) $(CFLAGS) -o estruturas_fila_pilha estruturas_fila_pilha.c

montador_neander: montador_neander.c
	$(CC) $(CFLAGS) -o montador_neander montador_neander.c

clean:
	rm -f $(TARGETS) agenda sort_algorithms queue_stack *.o *.mem ListaDeContatos.txt

.PHONY: all clean
