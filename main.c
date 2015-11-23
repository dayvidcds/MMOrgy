#include "grafo.h"
#include "search.h"

int main (int argc, char **argv){

	struct No *head = (struct No*)malloc(sizeof(struct No)), *procurado = NULL;
	char nome_pessoa[64], ler_char = 0;
	int n_pessoas = 0;
	FILE *entrada = NULL;
	
	if(!argv[1]){
		printf("Por favor, repasse o arquivo de texto como parâmetro para construção do grafo\n");
		return 1;
	}
	
	entrada = fopen(argv[1], "r");
	
	head = montar_grafo(entrada);

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
	
	free(head); free(procurado);
	
	return 0;
}
