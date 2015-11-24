#ifndef __SEARCH_H__
#define __SEARCH_H__

/* definição da estrutura dos Nós da Fila */
struct NoQueue{
	struct No *no;
	struct NoQueue *fila_prox;
};

/* verifica quais nós já foram visitados */
int verif_visitas (struct No **head);

/* reseta todas as visitas */
void reset_visitas (struct No **head);

/* dado um indice/posição, devolve o nó correspondente
	na lista de adjacências  */
struct No *list_get (struct No **head, int indice);

/* enfileira um elemento */
void enqueue (struct NoQueue **fila_fim, struct NoQueue *fila_novo);

/* função que efetua a busca em largura BFS */
struct No *buscaLargura (struct No *grafo, int index_Inicio, const char *nomePessoa, int *numCidades);

#endif
