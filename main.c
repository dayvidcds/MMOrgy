#include "grafo.h"
#include "search.h"
#include "cluster.h"
#include "notificacoes.h"

void imprime_membros_Cidade(FILE *newsfeed, struct Cidade **head_cidade);
void imprime_notificacoes(FILE *newsfeed, struct No **head);

int main (int argc, char **argv){
	
	struct No *head = (struct No*)malloc(sizeof(struct No)), *procurado = NULL;
	struct Cidade *head_cidade = (struct Cidade*)malloc(sizeof(struct Cidade));
    struct Cluster_interesses *head_interesses = (struct Cluster_interesses *)malloc(sizeof (struct Cluster_interesses)), *head_interesses_temp = (struct Cluster_interesses *)malloc(sizeof (struct Cluster_interesses));
    struct No *head_temp = NULL;
    char nome_pessoa[64], ler_char = 0;
	int n_pessoas = 0, quantidade_cadastros = 0;
	
    FILE *newsfeed = NULL;
    newsfeed = fopen("News Feed.txt", "w+");
    
	FILE *entrada = NULL;
    
	if(!argv[1]){
		printf("Por favor, repasse o arquivo de texto como parametro para construcao do grafo\n");
		return 1;
	}
	
	entrada = fopen(argv[1], "r");
	
	head = montar_grafo(entrada, &quantidade_cadastros);

	// Porque não imprime?
	//printf("Nome: %s\n", head->no_prox->perfil.nome);

	fscanf(entrada, "\n%c ", &ler_char);
	
	if(ler_char=='B'){
		procurado = (struct No*)malloc(sizeof(struct No));
		fgets(nome_pessoa, 64, entrada);
		strtok(nome_pessoa, "\n");
		procurado = buscaLargura(head, 1, nome_pessoa, &n_pessoas);
	}
		
	fclose(entrada);
		
	if(procurado){
		fprintf(newsfeed, "Encontrada! A busca passou por %d pessoas para encontra-la.\n\n", n_pessoas);
	}else{
		fprintf(newsfeed, "Pessoa nao encontrada\n");
	}
	
	head_cidade = mapear_grafo(head, 1);
	head_interesses = mapear_interesses (head, 1);
	insere_pessoasCidade(&head, &head_cidade, &quantidade_cadastros);	

    imprime_membros_Cidade(newsfeed, &head_cidade);
	
	fprintf(newsfeed, "\nInteresses:\n");
	
    head_interesses_temp = head_interesses;
    
    insere_pessoasInteresses(&head, &head_interesses);
    
    notificaCidades(&head_cidade);

    notificaInteresses(&head_interesses);
	
    imprime_notificacoes(newsfeed, &head);
       
    porcentagem_cidade(&head_cidade, &head_interesses);
	
	popular(head,newsfeed);
	
	fprintf(newsfeed,"\n");
	
	popular_grupo(head_cidade,newsfeed);
	
	fprintf(newsfeed,"\n");
	
	popular_interesses(head_interesses,newsfeed);
    
	free(head); free(procurado);
	
	return 0;
}

void imprime_membros_Cidade(FILE *newsfeed, struct Cidade **head_cidade){
    struct Cidade *head_cidade_temp = (struct Cidade*) malloc(sizeof(struct Cidade));
    struct Perfil *perfil_temp = (struct Perfil*)malloc(sizeof (struct Perfil));
    head_cidade_temp = (*head_cidade);
    
    while(head_cidade_temp){
		perfil_temp = head_cidade_temp->perfil;
		fprintf(newsfeed, "%s: ", head_cidade_temp->nome);
		
		while(perfil_temp){
			fprintf(newsfeed, "%s / ", perfil_temp->nome);
			perfil_temp = perfil_temp->prox_perfilCidade;
		}
		
		fprintf(newsfeed, "Quantidade: %d\n", head_cidade_temp->contador);

		head_cidade_temp = head_cidade_temp->prox;
		fprintf(newsfeed, "\n");
             
	}
    
    free(head_cidade_temp);
    free(perfil_temp);
}

void imprime_notificacoes(FILE *newsfeed, struct No **head){
   struct No *head_temp = (struct No *) malloc(sizeof(struct No));
   struct Notificar *notif_temp = NULL;
   
   head_temp = (*head);

   while(head_temp){
    	fprintf(newsfeed, "Notificacoes - %s:\n", head_temp->perfil.nome);
    	notif_temp = head_temp->perfil.notificacoes;
    	
    	while(notif_temp){
			fprintf(newsfeed, "%s\n", notif_temp->notificacao);
			notif_temp = notif_temp->prox;
		}
    	
    	head_temp = head_temp->no_prox;
    	fprintf(newsfeed, "\n");
    }
    
    free(head_temp);
}

