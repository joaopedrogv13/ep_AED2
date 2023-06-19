// *************************************************
// Joao Pedro Goncalves Vilela 
// USP: 13731070
//**************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo_matrizadj.h"

Grafo* criarGrafo(int numNos) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numNos = numNos;
    grafo->numArestas = 0;

    grafo->matriz = (int**)malloc((numNos + 1) * sizeof(int*));
    for (int i = 0; i <= numNos; i++) {
        grafo->matriz[i] = (int*)calloc(numNos + 1, sizeof(int));
    }

    return grafo;
}

bool adicionarAresta(Grafo* grafo, int noOrigem, int noDestino, Peso peso) {
    if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos || noDestino < 0 || noDestino > grafo->numNos)
        return false;

    if (grafo->matriz[noOrigem][noDestino] == 0) {
        grafo->matriz[noOrigem][noDestino] = peso;
        grafo->numArestas++;
    }

    return true;
}

bool existeAresta(Grafo* grafo, int noOrigem, int noDestino) {
    if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos || noDestino < 0 || noDestino > grafo->numNos)
        return false;

    return grafo->matriz[noOrigem][noDestino] != 0;
}

void destPeso(Grafo* grafo, int noOrigem, int indiceAresta, int* destino, Peso* peso) {
    if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos || indiceAresta < 0 || indiceAresta >= grafo->numArestas) {
        *destino = -1;
        *peso = -1;
        return;
    }

    int count = 0;
    for (int i = 0; i <= grafo->numNos; i++) {
        if (grafo->matriz[noOrigem][i] != 0) {
            if (count == indiceAresta) {
                *destino = i;
                *peso = grafo->matriz[noOrigem][i];
                return;
            }
            count++;
        }
    }

    *destino = -1;
    *peso = -1;
}

bool removerAresta(Grafo* grafo, int noOrigem, int noDestino) {
    if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos || noDestino < 0 || noDestino > grafo->numNos)
        return false;

    if (grafo->matriz[noOrigem][noDestino] != 0) {
        grafo->matriz[noOrigem][noDestino] = 0;
        grafo->numArestas--;
    }

    return true;
}

int numArestas(Grafo* grafo, int noOrigem) {
    if (!grafo || noOrigem < 0 || noOrigem > grafo->numNos)
        return -1;

    int count = 0;
    for (int i = 0; i <= grafo->numNos; i++) {
        if (grafo->matriz[noOrigem][i] != 0)
            count++;
    }

    return count;
}

void removerGrafo(Grafo* grafo) {
    if (!grafo)
        return;

    for (int i = 0; i <= grafo->numNos; i++) {
        free(grafo->matriz[i]);
    }

    free(grafo->matriz);
    free(grafo);
}
