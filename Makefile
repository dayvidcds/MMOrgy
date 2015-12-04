all: programa

programa: main.o grafo.o search.o cluster.o 
	gcc main.o grafo.o search.o cluster.o -o programa

main.o: main.c
	gcc -g -c main.c

grafo.o: grafo.c
	gcc -g -c grafo.c

search.o: search.c
	gcc -g -c search.c

cluster.o: cluster.c
	gcc -g -c cluster.c

clean:
	rm main.o grafo.o search.o cluster.o programa
