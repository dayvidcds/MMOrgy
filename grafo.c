#include "grafo.h"

//Função para montar grafo a partir de informações dadas num arquivo .txt
struct No *montar_grafo (FILE *entrada){
	struct No *no_inicio = NULL, *no_fim = NULL, *no_novo = NULL;
	int quant_cidades = 0, i;
	
	fscanf(entrada, "%d\n", &quant_cidades);
	
	
	for(i=0; i<quant_cidades; i++){
		struct Aresta *aresta_inicio = NULL, *aresta_fim = NULL, *aresta_novo = NULL;
		int quant_vizinhos = 0, j;
		no_novo = (struct No*)malloc(sizeof(struct No));
		
		fscanf(entrada, "\n");
		fgets(no_novo->cidade.nome, 64, entrada);
		strtok(no_novo->cidade.nome, "\n");
		fscanf(entrada, "\n%d", &no_novo->cidade.habitantes);
		
		fscanf(entrada, "\n%d", &quant_vizinhos);
		
		
		for(j=0; j<quant_vizinhos; j++){
			aresta_novo = (struct Aresta*)malloc(sizeof(struct Aresta));
			fscanf(entrada, " %d", &aresta_novo->indice);
			
			//Aqui ele insere aresta
			if (aresta_fim==NULL){
				aresta_inicio = aresta_fim = aresta_novo;
			}else{
				aresta_fim->aresta_prox = aresta_novo;
				aresta_novo->aresta_prox = NULL;
				aresta_fim = aresta_novo;
			}
			
		}
		
		no_novo->cidade.aresta = aresta_inicio;
		
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
