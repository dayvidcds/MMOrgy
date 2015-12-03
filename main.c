#include "grafo.h"
#include "search.h"
#include "cluster.h"

int main (int argc, char **argv){

	struct Cluster_interesses * head_interesses = (struct Cluster_interesses *) malloc (sizeof (struct Cluster_interesses));
	struct No *head = (struct No*)malloc(sizeof(struct No)), *procurado = NULL;
	struct Cidade *head_cidade = (struct Cidade*)malloc(sizeof(struct Cidade)), *head_cidade2 = (struct Cidade*)malloc(sizeof(struct Cidade));
    char nome_pessoa[64], ler_char = 0;
	int n_pessoas = 0, quantidade_cadastros = 0;
	FILE *entrada = NULL;
	
	if(!argv[1]){
		printf("Por favor, repasse o arquivo de texto como parâmetro para construção do grafo\n");
		return 1;
	}
	
	entrada = fopen(argv[1], "r");
	
	head = montar_grafo(entrada, &quantidade_cadastros);

	fscanf(entrada, "\n%c ", &ler_char);
	
	if(ler_char=='B'){
		procurado = (struct No*)malloc(sizeof(struct No));
		fgets(nome_pessoa, 64, entrada);
		strtok(nome_pessoa, "\n");
		procurado = buscaLargura(head, 1, nome_pessoa, &n_pessoas);
	}
	
	
	fclose(entrada);
		
	if(procurado){
		printf("Encontrada! A busca passou por %d pessoas para encontrá-la.\n", n_pessoas);
	}else{
		printf("Pessoa não encontrada\n");
	}
	
	head_cidade = mapear_grafo(head, 1);
	
	head_cidade2 = head_cidade;
	
	head_interesses = mapear_interesses (head, 1);

	while(head_cidade2){
		printf("%s\n", head_cidade2->nome);
		head_cidade2 = head_cidade2->prox;
	}
	
	while (head_interesses){
		printf ("%s\n", head_interesses->interesse);
		head_interesses = head_interesses->prox;
	}
	
    insere_pessoas(&head, &head_cidade, &quantidade_cadastros);
    
	free(head); free(procurado);
	
	return 0;
}
