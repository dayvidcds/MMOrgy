#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*enum Sexo{
	MASC = 1,
	FEM = 2
};*/


/* estruturas para encadeamento de amigos e interesses */
struct Amigos{
	int indice;
	struct Amigos *prox_amigo;
};

struct Interesses{
	char nome[64];
	struct Interesses *prox_interesse;
};

/* definição da estrutura de Perfil dos usuários */
struct Perfil{
	char nome[128];
	char cidade[64];
	char sexo[64];
    char teste[64];
	//enum Sexo {MASC = 1, FEM = 2} sexo;
	int idade;
    //int marcado;
    struct Perfil *prox_perfilCidade;
	struct Amigos *amigos;
	struct Interesses *interesses;
};

/* definição da estrutura do Nós do Grafo */
struct No{
	int visitado;
	struct Perfil perfil;
	struct No *no_prox;
};

/* função que monta o grafo, dado um arquivo de entrada */
struct No *montar_grafo (FILE *entrada, int *qtdade_cadastros);

#endif
