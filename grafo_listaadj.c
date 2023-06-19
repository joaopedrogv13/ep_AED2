// *************************************************
// Joao Pedro Goncalves Vilela 
// USP: 13731070
//**************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo_listaadj.h"

Grafo *criarGrafo(int nos)
{
	Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
	grafo->numNos = nos;
	grafo->numArestas = 0;
	grafo->listaNo = (No *)calloc(nos + 1, sizeof(No));
	return grafo;
}

Aresta *criarAresta(int no, int peso)
{
	Aresta *p = (Aresta *)malloc(sizeof(Aresta));
	p->destino = no;
	p->peso = peso;
	p->prox = NULL;
	return p;
}

bool adicionarAresta(Grafo *grafo, int noOrigem, int noDestino, Peso peso)
{
	if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos || noDestino < 0 || noDestino > grafo->numNos)
		return false;

	Aresta *novaAresta = criarAresta(noDestino, peso);
	novaAresta->prox = grafo->listaNo[noOrigem].inicio;
	grafo->listaNo[noOrigem].inicio = novaAresta;
	grafo->listaNo[noOrigem].numArestas++;
	grafo->numArestas++;
	return true;
}

void destPeso(Grafo *grafo, int noOrigem, int indiceAresta, int *destino, Peso *peso)
{
	if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos || indiceAresta < 0 || indiceAresta > grafo->listaNo[noOrigem].numArestas)
	{
		*destino = -1;
		*peso = -1;
		return;
	}
	// Verifica se não há arestas no nó de origem
	if (grafo->listaNo[noOrigem].numArestas == 0)
	{
		*destino = -1;
		*peso = -1;
		return;
	}
	// Obtém o destino e o peso da aresta especificada
	Aresta *p = grafo->listaNo[noOrigem].inicio;
	for (int i = 0; i < indiceAresta; i++)
	{
		p = p->prox;
	}
	*destino = p->destino;
	*peso = p->peso;
}

bool removerAresta(Grafo *grafo, int noOrigem, int noDestino)
{
	if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos || noDestino < 0 || noDestino > grafo->numNos)
		return false;

	Aresta *ant = NULL;
	Aresta *p = grafo->listaNo[noOrigem].inicio;
	while (p && p->destino != noDestino)
	{
		ant = p;
		p = p->prox;
	}

	if (p)
	{
		if (ant)
			ant->prox = p->prox;
		else
			grafo->listaNo[noOrigem].inicio = p->prox;

		free(p);
		grafo->listaNo[noOrigem].numArestas--;
		grafo->numArestas--;
		return true;
	}

	return false;
}

int numArestas(Grafo *grafo, int noOrigem)
{
	if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos)
		return -1;

	return grafo->listaNo[noOrigem].numArestas;
}

void removerGrafo(Grafo *grafo)
{
	if (!grafo)
		return;

	for (int i = 0; i <= grafo->numNos; i++)
	{
		Aresta *p = grafo->listaNo[i].inicio;
		while (p)
		{
			Aresta *aux = p;
			p = p->prox;
			free(aux);
		}
	}

	free(grafo->listaNo);
	free(grafo);
}
