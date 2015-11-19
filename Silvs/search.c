#include "grafo.h"

//Reseta todas as visitas
void reset_visitas (struct No **head){
	struct No *temp = (*head);
	while(temp){
		temp->visitado = 0;
		temp = temp->no_prox;
	}
}

//Verifica todas as visitas
int verif_visitas (struct No **head){
	struct No *temp = (*head);
	while(temp){
		if(temp->visitado==0){
			return 1;
		}
		temp = temp->no_prox;
	}
	return 0;
}

//Função que procura nó pelo indice e retorna o ponteiro
struct No *list_get (struct No **head, int indice){
	struct No *temp = (*head);
	int i;
	for (i=1; i<indice; i++){
		temp = temp->no_prox;
	}
	return temp;
}

//Função para enfileirar nós do grafo numa lista de prioridades
void enqueue (struct NoQueue **fila_fim, struct NoQueue *fila_novo){
	if((*fila_fim)){
		(*fila_fim)->fila_prox = fila_novo;
	}
	(*fila_fim) = fila_novo;
	(*fila_fim)->fila_prox = NULL;
	(*fila_fim)->no->visitado = 1;
}

//Função de busca em grafo por largura
struct No *buscaLargura (struct No *grafo, int index_Inicio, const char *nomeCidade, int *numCidades){
	struct NoQueue *fila_inicio = (struct NoQueue*)malloc(sizeof(struct NoQueue));
	struct NoQueue *fila_fim = (struct NoQueue*)malloc(sizeof(struct NoQueue));
	struct NoQueue *fila_novo = (struct NoQueue*)malloc(sizeof(struct NoQueue)); 
	
	reset_visitas(&grafo);
	
	fila_novo->no = list_get(&grafo, index_Inicio);
	enqueue(&fila_fim,  fila_novo);
	fila_inicio = fila_fim;
	
	if (strcmp(fila_inicio->no->cidade.nome, nomeCidade)==0){
		//return fila_inicio->no->cidade;
		return fila_inicio->no;
	}
	
	while(verif_visitas(&grafo)==1){
		struct NoQueue *fila_temp = (struct NoQueue*)malloc(sizeof(struct NoQueue));
		(*numCidades)++;
	
		//Insere nós correspondentes as arestas e remove os nós já verificados da lista de prioridades
		for(fila_temp = fila_fim; fila_inicio!=fila_temp->fila_prox; fila_inicio = fila_inicio->fila_prox){
			struct Aresta *temp_aresta = NULL;
		
			for(temp_aresta = fila_inicio->no->cidade.aresta; temp_aresta!=NULL; temp_aresta = temp_aresta->aresta_prox){
				struct No *temp = list_get(&grafo, temp_aresta->indice);
				fila_novo = (struct NoQueue*)malloc(sizeof(struct NoQueue));
				
				if(temp->visitado==0){
					fila_novo->no = temp;
					enqueue(&fila_fim, fila_novo);
				}
			
			}
		
		}
		
		//Testar se na lista está presente o nó procurado
		for(fila_temp = fila_inicio; fila_temp!=NULL; fila_temp = fila_temp->fila_prox){
		
			if(strcmp(fila_temp->no->cidade.nome, nomeCidade)==0){
				//return fila_temp->no->cidade;
				return fila_temp->no;
			}
			
		}
	
	}
	
	return NULL;

}
