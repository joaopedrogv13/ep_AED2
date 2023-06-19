// *************************************************
// Joao Pedro Goncalves Vilela 
// USP: 13731070
//**************************************************

#include <stdbool.h>

typedef int Peso;

//struct dos slides
typedef struct
{
    int **matriz;
    int numNos;
    int numArestas;
} Grafo;

Grafo *criarGrafo(int numNos);

bool adicionarAresta(Grafo *grafo, int noOrigem, int noDestino, Peso peso);

bool removerAresta(Grafo *grafo, int noOrigem, int noDestino);

bool existeAresta(Grafo *grafo, int noOrigem, int noDestino);

void destPeso(Grafo *grafo, int noOrigem, int indiceAresta, int *destino, Peso *peso);

int numArestas(Grafo *grafo, int noOrigem);

void removerGrafo(Grafo *grafo);
