#ifndef __CLUSTER_H__
#define __CLUSTER_H__

struct Cidade{
	char nome[32];
	struct Perfil *perfil;
	struct Cidade *prox;
};

void encadeia_cidades (struct Cidade **cidade_fim, struct Cidade *cidade_novo);
struct Cidade *mapear_grafo (struct No *grafo, int index_Inicio);
void insere_pessoas(struct No **head_perfis, struct Cidade **head_cidades, int *quantidade_perfis);

#endif
