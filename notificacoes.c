#include "grafo.h"
#include "search.h"
#include "cluster.h"
#include "notificacoes.h"


/* falta terminar */

void notificaCidades(struct Cidade **cidade_inicio){

	struct Cidade *temp_cidade = (*cidade_inicio);
	struct Perfil *temp_perfil = NULL;
	struct Notificar *noti = NULL;
	char strTemp[256];

	while(temp_cidade){

		temp_perfil = temp_cidade->perfil;

		while(temp_perfil){

			noti = (struct Notificar *)malloc(sizeof(struct Notificar));

			strcpy(strTemp, "Você entrou no grupo das pessoas que moram em ");
			strcat(strTemp, temp_cidade->nome);
			strcpy(noti->notificacao, strTemp);

			temp_perfil->notificacoes = noti;

			temp_perfil = temp_perfil->prox_perfilCidade;

		}

		temp_cidade = temp_cidade->prox;

	}

}