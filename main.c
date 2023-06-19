// *************************************************
// Joao Pedro Goncalves Vilela 
// USP: 13731070
//**************************************************

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo_listaadj.h"
//#include "grafo_matrizadj.h"

// structs auxiliares para interface lista/matriz
typedef struct
{
  int centro1;
  int centro2;
  int peso;
} Consulta;

typedef struct
{
  Consulta *vetConsultas;
  int tamConsultas;
} Consultas;

typedef struct
{
  int no;
  int ant;
  int peso;
  bool aberto;
} NoBusca;

typedef struct
{
  NoBusca *vetBusca;
  int origem;
  int tam;
} ResBusca;

// Ajusta os pesos dos resultados das consultas
void resultados(ResBusca *r)
{
  for (int i = 0; i <= r->tam; i++)
  {
    if (r->vetBusca[i].peso >= 450)
      r->vetBusca[i].peso = 450;
    else if (r->vetBusca[i].peso >= 400)
      r->vetBusca[i].peso = 400;
    else if (r->vetBusca[i].peso >= 350)
      r->vetBusca[i].peso = 350;
    else if (r->vetBusca[i].peso >= 300)
      r->vetBusca[i].peso = 300;
    else if (r->vetBusca[i].peso >= 250)
      r->vetBusca[i].peso = 250;
    else
      r->vetBusca[i].peso = -1;
  }
}

// Encontra o índice do nó com o maior peso entre os nos nao visitados
void indiceMaiorMin(NoBusca *vetor, int tam, int *indice)
{
  int maior = -1;
  for (int i = 0; i < tam; i++)
  {
    if (vetor[i].aberto && vetor[i].peso > maior)
    {
      maior = vetor[i].peso;
      *indice = i;
    }
  }
}

// Libera a memória alocada para os resultados da busca
void deletarResBusca(ResBusca **resultados, int tam)
{
  for (int i = 0; i < tam; i++)
  {
    free(resultados[i]->vetBusca);
    free(resultados[i]);
  }
  free(resultados);
}

// Escreve os resultados das consultas em um arquivo
void escreverResultados(ResBusca **resBusca, Consultas *consultas)
{
  FILE *arquivo = fopen("saida.txt", "w");
  for (int i = 0; i < consultas->tamConsultas; i++)
  {
    fprintf(arquivo, "%.1f\n", ((double)resBusca[i]->vetBusca[consultas->vetConsultas[i].centro2].peso) / 100);
  }
  fclose(arquivo);
}

// le o arquivo e cria o grafo
Grafo *lerArquivo(char *caminho, Consultas *consultas)
{
  FILE *arquivo = fopen(caminho, "r");
  if (arquivo == NULL)
  {
    printf("Falha ao abrir o arquivo.txt\n");
    return NULL;
  }
  int centros;
  int conexoes;
  int tamConsultas;
  fscanf(arquivo, "%d %d %d\n", &centros, &conexoes, &tamConsultas);
  consultas->vetConsultas = (Consulta *)malloc(sizeof(Consulta) * tamConsultas);
  consultas->tamConsultas = tamConsultas;
  Grafo *grafo = criarGrafo(centros);
  for (int i = 0; i < conexoes; i++)
  {
    int centro1, centro2;
    float peso;
    fscanf(arquivo, "%d %d %f", &centro1, &centro2, &peso);
    adicionarAresta(grafo, centro1, centro2, (int)(peso * 100));
    adicionarAresta(grafo, centro2, centro1, (int)(peso * 100));
  }
  for (int i = 0; i < consultas->tamConsultas; i++)
  {
    int centro1, centro2;
    fscanf(arquivo, "%d %d", &centro1, &centro2);
    consultas->vetConsultas[i].centro1 = centro1;
    consultas->vetConsultas[i].centro2 = centro2;
  }
  fclose(arquivo);
  return grafo;
}

// devolve o valor do menor peso entre dois caminhos resultantes da AGM
ResBusca *fazerConsulta(Grafo *grafo, Consulta consulta)
{
  ResBusca *resBusca = (ResBusca *)malloc(sizeof(ResBusca));
  resBusca->vetBusca = (NoBusca *)malloc(sizeof(NoBusca) * (grafo->numNos + 1));
  resBusca->origem = consulta.centro1;
  resBusca->tam = grafo->numNos;
  for (int i = 0; i <= grafo->numNos; i++)
  {
    resBusca->vetBusca[i].no = i;
    resBusca->vetBusca[i].ant = -1;
    resBusca->vetBusca[i].peso = -1;
    resBusca->vetBusca[i].aberto = true;
  }
  resBusca->vetBusca[consulta.centro1].peso = INT_MAX;
  resBusca->vetBusca[consulta.centro1].aberto = false;
  int i = consulta.centro1;
  int arestas = numArestas(grafo, i);
  for (int z = 0; z <= grafo->numNos - 1; z++)
  {
    int destArestas;
    int pesoAresta;
    for (int j = 0; j < arestas; j++)
    {
      destPeso(grafo, i, j, &destArestas, &pesoAresta);
      int minimo = resBusca->vetBusca[i].peso < pesoAresta ? resBusca->vetBusca[i].peso : pesoAresta;
      if (resBusca->vetBusca[destArestas].aberto && resBusca->vetBusca[i].no != destArestas && minimo > resBusca->vetBusca[destArestas].peso)
      {
        resBusca->vetBusca[destArestas].peso = minimo;
        resBusca->vetBusca[destArestas].ant = resBusca->vetBusca[i].no;
      }
    }
    resBusca->vetBusca[i].aberto = false;
    indiceMaiorMin(resBusca->vetBusca, grafo->numNos, &i);
    arestas = numArestas(grafo, i);
  }
  resultados(resBusca);
  return resBusca;
}

int main(int argc, char *argv[])
{
  Consultas *consultas = (Consultas *)malloc(sizeof(Consultas));
  Grafo *grafo = lerArquivo(argv[1], consultas);
  ResBusca **resBusca = (ResBusca **)malloc(sizeof(ResBusca *) * consultas->tamConsultas);
  for (int i = 0; i < consultas->tamConsultas; i++)
  {
    for (int j = 0; j < i; j++)
    {
      if (consultas->vetConsultas[i].centro1 == consultas->vetConsultas[j].centro1)
      {
        resBusca[i] = resBusca[j];
        break;
      }
    }
    resBusca[i] = fazerConsulta(grafo, consultas->vetConsultas[i]);
  }
  escreverResultados(resBusca, consultas);
  removerGrafo(grafo);
  deletarResBusca(resBusca, consultas->tamConsultas);
  return 0;
}
