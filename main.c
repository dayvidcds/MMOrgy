#include "grafo.h"
#include "search.h"
#include "cluster.h"

int main (int argc, char **argv){

	
	struct No *head = (struct No*)malloc(sizeof(struct No)), *procurado = NULL;
	struct Cidade *head_cidade = (struct Cidade*)malloc(sizeof(struct Cidade)), *head_cidade_temp = (struct Cidade*)malloc(sizeof(struct Cidade));
    struct Cluster_interesses *head_interesses = (struct Cluster_interesses *)malloc(sizeof (struct Cluster_interesses)), *head_interesses_temp = (struct Cluster_interesses *)malloc(sizeof (struct Cluster_interesses));
    struct Perfil *perfil_temp = (struct Perfil*)malloc(sizeof (struct Perfil));
        
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
		printf("Encontrada! A busca passou por %d pessoas para encontrá-la.\n\n", n_pessoas);
	}else{
		printf("Pessoa não encontrada\n");
	}
	
	head_cidade = mapear_grafo(head, 1);
	head_interesses = mapear_interesses (head, 1);
	insere_pessoasCidade(&head, &head_cidade, &quantidade_cadastros);
	
	head_cidade_temp = head_cidade;
	

	//imprime os membros do cluster cidade
	while(head_cidade_temp){
		perfil_temp = head_cidade_temp->perfil;
		printf("%s: ", head_cidade_temp->nome);
		
		while(perfil_temp){
			printf("%s / ", perfil_temp->nome);
			perfil_temp = perfil_temp->prox_perfilCidade;
		}
		
		printf("Quantidade: %d\n", head_cidade_temp->contador);

		head_cidade_temp = head_cidade_temp->prox;
		printf("\n");
	}
	
	printf("\nInteresses:\n");
	
    head_interesses_temp = head_interesses;
    
    insere_pessoasInteresses(&head, &head_interesses);
    
    while(head_interesses_temp){
        printf("// %s //: ", head_interesses_temp->interesse);
        while(head_interesses_temp->lista){
            printf("%s\n ", head_interesses_temp->lista->perfil->nome);
            head_interesses_temp->lista = head_interesses_temp->lista->proxi;
        }
        printf("Quantidade: %d\n", head_interesses_temp->counter);
        head_interesses_temp = head_interesses_temp->prox;
    }
    
    
	free(head); free(procurado);
	
	return 0;
}