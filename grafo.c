#include "grafo.h"

//Função para montar grafo a partir de informações dadas num arquivo .txt
struct No *montar_grafo (FILE *entrada, int *qtdade_cadastros){

	struct No *no_inicio = NULL, *no_fim = NULL, *no_novo = NULL;
	int i = 0;
	
	fscanf(entrada, "%d\n", qtdade_cadastros);
	
	for(i=0; i<(*qtdade_cadastros); i++){

		struct Amigos *amigos_inicio = NULL, *amigos_fim = NULL, *amigo_novo = NULL;
		struct Interesses *interesses_inicio = NULL, *interesses_fim = NULL, *novo_interesse = NULL;

		int quant_amigos = 0, quant_interesses, j;
		no_novo = (struct No *)malloc(sizeof(struct No));
		
		fscanf(entrada, "\n");
		fgets(no_novo->perfil.nome, 128, entrada);
		strtok(no_novo->perfil.nome, "\n");
		fgets(no_novo->perfil.cidade, 64, entrada);
		strtok(no_novo->perfil.cidade, "\n");
		fgets(no_novo->perfil.sexo, 64, entrada);
		strtok(no_novo->perfil.sexo, "\n");
		fscanf(entrada, "\n%d", &no_novo->perfil.idade);

		fscanf(entrada, "\n%d", &quant_interesses);

		//Insere os interesses 
		for(j = 0; j < quant_interesses; j++){

			novo_interesse = (struct Interesses *)malloc(sizeof(struct Interesses));

			fscanf(entrada, "\n%s", &novo_interesse->nome);

			if(interesses_fim == NULL){
				interesses_inicio = interesses_fim = novo_interesse;
			}else{
				interesses_fim->prox_interesse = novo_interesse;
				novo_interesse->prox_interesse = NULL;
				interesses_fim = novo_interesse;
			}

		}

		no_novo->perfil.interesses = interesses_inicio;


		fscanf(entrada, "\n%d", &quant_amigos);
		
		//Insere os amigos por indices
		for(j=0; j<quant_amigos; j++){

			amigo_novo = (struct Amigos *)malloc(sizeof(struct Amigos));

			fscanf(entrada, " %d", &amigo_novo->indice);

			//Aqui ele insere aresta
			if (amigos_fim==NULL){
				amigos_inicio = amigos_fim = amigo_novo;
			}else{
				amigos_fim->prox_amigo = amigo_novo;
				amigo_novo->prox_amigo = NULL;
				amigos_fim = amigo_novo;
			}
			
		}
		
		no_novo->perfil.amigos = amigos_inicio;
		no_novo->perfil.notificacoes = NULL;
		//Aqui ele insere nó
		if (no_fim==NULL){
			no_inicio = no_fim = no_novo;
		}else{
			no_fim->no_prox = no_novo;
			no_novo->no_prox = NULL;
			no_fim = no_novo;
		}
		
	}
	
	return no_inicio;
}
