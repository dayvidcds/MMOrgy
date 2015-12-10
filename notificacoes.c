#include "grafo.h"
#include "search.h"
#include "cluster.h"
#include "notificacoes.h"
#include <ctype.h>

/* falta terminar */

void notificaCidades(struct Cidade **cidade_inicio){

	struct Cidade *temp_cidade = (*cidade_inicio);
	struct Perfil *temp_perfil = NULL;
	struct Notificar *notif_cidades = NULL;
	

	while(temp_cidade){

		char strTemp[256];

		strcpy(strTemp, "Voce entrou no grupo das pessoas que moram em ");
		strcat(strTemp, temp_cidade->nome);

		temp_perfil = temp_cidade->perfil;

		while(temp_perfil){

			notif_cidades = (struct Notificar *)malloc(sizeof(struct Notificar));

			strcpy(notif_cidades->notificacao, strTemp);

			inserir_notificacao(&temp_perfil->notificacoes, notif_cidades);

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

void pushFile(struct No *head_no){

	struct No *tmp_head = head_no;
	FILE *arquivo = NULL;
	struct Notificar *notif = NULL;
	int i = 0;

	while(tmp_head){
    	notif = tmp_head->perfil.notificacoes;
    	char nomeTemp[128];
    	char nomeFile[128];
    	strcpy(nomeTemp, tmp_head->perfil.nome);
    	strcpy(nomeFile, "notificacoes/");

    	for(i = 0; i < strlen(nomeTemp); i++){
    		nomeTemp[i] = tolower(nomeTemp[i]);
    	}
    	
    	strcat(nomeTemp, ".txt");
    	strcat(nomeFile, nomeTemp);

    	arquivo = fopen(nomeFile, "w");

    	while(notif){
			fprintf(arquivo, notif->notificacao);
			fprintf(arquivo, "\n\n");

			notif = notif->prox;
		}
    	
    	tmp_head = tmp_head->no_prox;

    }

}
