#ifndef __NOTIFICACAO_H__
#define __NOTIFICACAO_H__

struct Notificar{
	char notificacao [256];
	struct Notificar *prox;
};

void notificaCidades(struct Cidade **cidade_inicio);

#endif