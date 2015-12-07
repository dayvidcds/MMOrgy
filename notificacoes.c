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

			strcpy(strTemp, "Voce entrou no grupo das pessoas que moram em ");
			strcat(strTemp, temp_cidade->nome);
			strcpy(noti->notificacao, strTemp);

			temp_perfil->notificacoes = noti;

			temp_perfil = temp_perfil->prox_perfilCidade;

		}

		temp_cidade = temp_cidade->prox;

	}

}

void notificaInteresses(struct Cluster_interesses **head_interesses){
	struct Cluster_interesses *temp_interesses = (*head_interesses);
	
	while(temp_interesses){
		struct lista_perfisInteresses *temp_listaPerfis = NULL;
		char notificacao[256];
		
		strcpy(notificacao, "Hey dlc! Voce entrou no grupo sobre ");
		strcat(notificacao, temp_interesses->interesse);
		
		temp_listaPerfis = temp_interesses->lista;
		
		while(temp_listaPerfis){
			struct Notificar *notif_interesse = (struct Notificar*)malloc(sizeof(struct Notificar));
			
			strcpy(notif_interesse->notificacao, notificacao);
			inserir_notificacao(&temp_listaPerfis->perfil->notificacoes, notif_interesse);
			
			temp_listaPerfis = temp_listaPerfis->proxi;
		}
		
		temp_interesses = temp_interesses->prox;
	}
}

void inserir_notificacao(struct Notificar **lista, struct Notificar *novo){
	if((*lista)){
		novo->prox = (*lista);
	}
	(*lista) = novo;
}
