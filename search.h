#ifndef __SEARCH_H__
#define __SEARCH_H__

struct NoQueue{
	struct No *no;
	struct NoQueue *fila_prox;
};

int verif_visitas (struct No **head);
void reset_visitas (struct No **head);
struct No *list_get (struct No **head, int indice);
void enqueue (struct NoQueue **fila_fim, struct NoQueue *fila_novo);
struct No *buscaLargura (struct No *grafo, int index_Inicio, const char *nomePessoa, int *numCidades);

#endif
