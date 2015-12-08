#ifndef __CLUSTER_H__
#define __CLUSTER_H__

struct Cidade{
	char nome[32];
	struct Perfil *perfil;
	struct Cidade *prox;
    float porcentagem;
	int contador;
};

struct Cluster_interesses {
    char interesse[32];
    struct lista_perfisInteresses *lista;
    struct Cluster_interesses *prox;
    float percent;
    int counter;
};

struct lista_perfisInteresses {
    struct Perfil *perfil;
    struct lista_perfisInteresses *proxi;
};

void encadeia_cidades (struct Cidade **cidade_fim, struct Cidade *cidade_novo);
struct Cidade *mapear_grafo (struct No *grafo, int index_Inicio);
void insere_pessoasCidade(struct No **head_perfis, struct Cidade **head_cidades, int *quantidade_perfis);
void encadeia_interesses (struct Cluster_interesses ** head_interesses,struct Cluster_interesses ** fim, struct Cluster_interesses * novo);
struct Cluster_interesses * mapear_interesses (struct No * grafo, int index_inicio);
void insere_pessoasInteresses(struct No **head_perfis, struct Cluster_interesses **head_interesses);
void porcentagem_cidade (struct Cidade **head_cidades, struct Cluster_interesses **head_interesses);
void porcentagem_interesses (struct Cluster_interesses **head_interesses, int quant_perfis);

#endif
