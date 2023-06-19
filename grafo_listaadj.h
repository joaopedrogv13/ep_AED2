// *************************************************
// Joao Pedro Goncalves Vilela 
// USP: 13731070
//**************************************************

#include <stdbool.h>

typedef int Peso; 

//struct dos slides 
typedef struct aresta {
	int destino; 
    Peso peso; 
	struct aresta *prox; 
} Aresta;

typedef struct no {
	Aresta *inicio;
	int numArestas; 
} No;

typedef struct ListaGrafo {
	int numNos; 
	int numArestas;
	No *listaNo;
} Grafo;

Grafo *criarGrafo(int numNos);

Aresta *criarAresta(int no, int peso);

bool adicionarAresta(Grafo *g, int noOrigem, int noDestino, Peso peso);

bool removerAresta(Grafo *g, int noOrigem, int noDestino);

void destPeso(Grafo *g, int noOrigem, int indiceAresta, int *destino, Peso *peso);

int numArestas(Grafo *g, int noOrigem);

void removerGrafo(Grafo *g);
