#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Sexo{
	MASC = 1,
	FEM = 2
};

struct Amigos{
	int indice;
	struct Amigos *prox_amigo;
};

struct Interesses{
	char nome[64];
	struct Interesses *prox_interesse;
};

struct Perfil{
	char nome[128];
	char cidade[64];
	char sexo[64];
	int idade;
	struct Amigos *amigos;
	struct Interesses *interesses;
};

struct No{
	int visitado;
	struct Perfil perfil;
	struct No *no_prox;
};

struct No *montar_grafo (FILE *entrada);

#endif
