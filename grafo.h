#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aresta{
	int indice;
	struct Aresta *aresta_prox;
};

struct Cidade{
	char nome[64];
	int habitantes;
	struct Aresta *aresta;
};

struct No{
	int visitado;
	struct Cidade cidade;
	struct No *no_prox;
};

struct NoQueue{
	struct No *no;
	struct NoQueue *fila_prox;
};

struct No *montar_grafo (FILE *entrada);

#endif
