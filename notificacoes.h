#ifndef __NOTIFICACAO_H__
#define __NOTIFICACAO_H__

struct Notificar{
	char notificacao [256];
	struct Notificar *prox;
};

void notificaCidades(struct Cidade **cidade_inicio);
void notificaInteresses(struct Cluster_interesses **head_interesses);
void inserir_notificacao(struct Notificar **inicio_lista, struct Notificar *novo);

#endif
