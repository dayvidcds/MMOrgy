#include "grafo.h"
#include "search.h"
#include "cluster.h"

void encadeia_cidades (struct Cidade **cidade_fim, struct Cidade *cidade_novo){
	if((*cidade_fim)){
		(*cidade_fim)->prox = cidade_novo;
	}
	(*cidade_fim) = cidade_novo;
	(*cidade_fim)->prox = NULL;
}

struct Cidade *mapear_grafo (struct No *grafo, int index_Inicio){
	struct Cidade *head_cidade = (struct Cidade*)malloc(sizeof(struct Cidade));
	struct Cidade *cidade_inicio = (struct Cidade*)malloc(sizeof(struct Cidade));
	struct Cidade *cidade_fim = (struct Cidade*)malloc(sizeof(struct Cidade));
	struct NoQueue *fila_inicio = (struct NoQueue*)malloc(sizeof(struct NoQueue));
	struct NoQueue *fila_fim = (struct NoQueue*)malloc(sizeof(struct NoQueue));
	struct NoQueue *fila_novo = (struct NoQueue*)malloc(sizeof(struct NoQueue)); 
	
	cidade_inicio = cidade_fim = head_cidade;
	
	reset_visitas(&grafo);
	
	fila_novo->no = list_get(&grafo, index_Inicio);
	enqueue(&fila_fim, fila_novo);
	fila_inicio = fila_fim;
	
	strcpy(head_cidade->nome, grafo->perfil.cidade);
	
	
	while(verif_visitas(&grafo)==1){
		struct NoQueue *fila_temp = (struct NoQueue*)malloc(sizeof(struct NoQueue));
		
		//Insere nós correspondentes as arestas e remove os nós já verificados da lista de prioridades
		for(fila_temp = fila_fim; fila_inicio!=fila_temp->fila_prox; fila_inicio = fila_inicio->fila_prox){
			struct Amigos *temp_amigos = NULL;
		
			for(temp_amigos = fila_inicio->no->perfil.amigos; temp_amigos != NULL; temp_amigos = temp_amigos->prox_amigo){
				struct No *temp = list_get(&grafo, temp_amigos->indice);
				fila_novo = (struct NoQueue*)malloc(sizeof(struct NoQueue));
				
				if(temp->visitado==0){
					fila_novo->no = temp;
					enqueue(&fila_fim, fila_novo);
				}
			
			}
		
		}
		
		
		for(fila_temp = fila_inicio; fila_temp!=NULL; fila_temp = fila_temp->fila_prox){
			struct Cidade *cidade_temp = (struct Cidade*)malloc(sizeof(struct Cidade));
			int verif = 0;
			
			for (cidade_temp = cidade_inicio; cidade_temp!=NULL; cidade_temp = cidade_temp->prox){
				
				if(strcmp(fila_temp->no->perfil.cidade, cidade_temp->nome)==0){
					verif = 1;
					break;
				}
			}
			
			if (!verif){
				struct Cidade *novo = (struct Cidade*)malloc(sizeof(struct Cidade));
				strcpy(novo->nome, fila_temp->no->perfil.cidade);
				encadeia_cidades(&cidade_fim, novo);
			}
			
		}
	
	}
	
	return head_cidade;

}
