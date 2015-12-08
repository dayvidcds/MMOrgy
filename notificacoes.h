#ifndef __NOTIFICACAO_H__
#define __NOTIFICACAO_H__

struct Notificar{
	char notificacao[256];
	struct Notificar *prox;
};

/*
struct InteresseComum{
	char notificacao[256];
};
*/

void notificaCidades(struct Cidade **cidade_inicio);
void notificaInteresses(struct Cluster_interesses **head_interesses);
void inserir_notificacao(struct Notificar **inicio_lista, struct Notificar *novo);
void pushFile(struct No *head_no);

#endif
