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

void insere_pessoas(struct No **head_perfis, struct Cidade **head_cidades, int *quantidade_perfis){
	int i = 0;
	struct Cidade *headCluster = (struct Cidade *) malloc(sizeof(struct Cidade));
	struct Cidade *primeiro = (*head_cidades);
	struct No *firstNo = (*head_perfis);
	struct Perfil *ultimoPerfilClusterInserido = NULL;
	
	headCluster = (*head_cidades);
       
    while(primeiro){
		
		for(i = 0; i < (*quantidade_perfis); ++i){
			if(strcmp(firstNo->perfil.cidade, primeiro->nome) != 0){
				firstNo = firstNo->no_prox;
			} else {
				if(primeiro->perfil == NULL){
					primeiro->perfil = &firstNo->perfil;
					ultimoPerfilClusterInserido = primeiro->perfil;	
				} else {
					ultimoPerfilClusterInserido->prox_perfilCidade = &firstNo->perfil;
					ultimoPerfilClusterInserido = &firstNo->perfil; 
				}
				firstNo = firstNo->no_prox;
			}
        }
        firstNo = (*head_perfis);
        primeiro = primeiro->prox;       
    }
}

void encadeia_interesses (struct Cluster_interesses ** head_interesses, struct Cluster_interesses ** fim, struct Cluster_interesses * novo){
    
    if (!(*fim)){
    	(*head_interesses) = novo;
    	(*fim) = (*head_interesses);
    }else{
    	(*fim)->prox = novo;
    	(*fim) = novo;
    }
        (*fim)->prox = NULL;
}

struct Cluster_interesses * mapear_interesses (struct No * grafo, int index_inicio){
    
    struct Cluster_interesses * head_interesses = (struct Cluster_interesses * ) malloc (sizeof (struct Cluster_interesses));
    struct Cluster_interesses * interesses_inicio = (struct Cluster_interesses * ) malloc (sizeof (struct Cluster_interesses));
    struct Cluster_interesses * interesses_fim = (struct Cluster_interesses * ) malloc (sizeof (struct Cluster_interesses));
    struct NoQueue *fila_inicio = (struct NoQueue*)malloc(sizeof(struct NoQueue));
	struct NoQueue *fila_fim = (struct NoQueue*)malloc(sizeof(struct NoQueue));
	struct NoQueue *fila_novo = (struct NoQueue*)malloc(sizeof(struct NoQueue)); 
    struct Cluster_interesses * novo = NULL;
    struct Interesses * temps = NULL;
    
    interesses_inicio = interesses_fim = head_interesses = NULL;
    
    reset_visitas (&grafo);
    
    fila_novo->no = list_get (&grafo,index_inicio);
    //fila_novo->no = grafo;
    
    enqueue (&fila_fim, fila_novo); //coloca o no visitado na fila e marca ele
    
    fila_inicio = fila_fim;
    
    for (temps = fila_inicio->no->perfil.interesses;temps != NULL; temps = temps->prox_interesse){
        novo = (struct Cluster_interesses*)malloc(sizeof(struct Cluster_interesses));
		strcpy(novo->interesse, temps->nome);
        encadeia_interesses(&head_interesses,&interesses_fim,novo);    
    }

    interesses_inicio = head_interesses;
    	
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
            
			struct Cluster_interesses *interesses_temp = (struct Cluster_interesses*)malloc(sizeof(struct Cluster_interesses));
			int verif = 0;
			struct Interesses * temp_interesses = NULL;  

			//andar com os interesses de cada perfil
			for (temp_interesses = fila_temp->no->perfil.interesses;temp_interesses != NULL; temp_interesses = temp_interesses->prox_interesse){
				struct Interesses *tempTeste = NULL;
				//anda com a lista encadeada de interesses

				tempTeste = temp_interesses;

				for (interesses_temp = interesses_inicio; interesses_temp!=NULL; interesses_temp = interesses_temp->prox){

					if(strcmp(tempTeste->nome,interesses_temp->interesse)==0){
						verif = 1;
						tempTeste = tempTeste->prox_interesse;
						break;
					}else{
						//novo = (struct Cluster_interesses*)malloc(sizeof(struct Cluster_interesses));
						//strcpy(novo->interesse, tempTeste->nome);
        				//encadeia_interesses(&head_interesses,&interesses_fim,novo);
        				//tempTeste = tempTeste->prox_amigo_interesse;
        				verif = 0;
        				continue;  
				  	}
				}

				if(verif == 0){
					novo = (struct Cluster_interesses*)malloc(sizeof(struct Cluster_interesses));
					strcpy(novo->interesse, tempTeste->nome);
        			encadeia_interesses(&head_interesses,&interesses_fim,novo);
        				//tempTeste = tempTeste->prox_interesse;
				}

			}
			/*
			if (!verif){
				
				for (temps = fila_inicio->no->perfil.interesses;temps != NULL; temps = temps->prox_interesse){
               
        			novo = (struct Cluster_interesses*)malloc(sizeof(struct Cluster_interesses));
					strcpy(novo->interesse, temps->nome);
        			encadeia_interesses(&interesses_fim,novo);    
    			}
    			*/
        	}
			
		}
		return head_interesses;
	}
