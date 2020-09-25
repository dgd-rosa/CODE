#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/******************************************************************************
 * childLeft_Id()
 *
 * Argumentos: id do pai
 * Returns: id do filho da esquerda
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int childLeft_Id(int parent_id)
{
  return 2*parent_id + 1;
}
/******************************************************************************
 * childRight_Id()
 *
 * Argumentos: id do pai
 * Returns: id do filho da direita
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int childRight_Id(int parent_id)
{
  return 2*parent_id + 2;
}
/******************************************************************************
 * parent_Id()
 *
 * Argumentos: id do filho
 * Returns: id do pai
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int parent_Id(int child_id)
{
  return (child_id - 1)/2;
}

/******************************************************************************
 * tem_esquerda()
 *
 * Argumentos: id do pai, e size ( tamanho do acervo)
 * Returns: id do filho da esquerda se existir
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int tem_esquerda(int Id, int size)
{
  return childLeft_Id(Id) < size;
}
/******************************************************************************
 * tem_direita()
 *
 * Argumentos: id do pai, e size ( tamanho do acervo)
 * Returns: id do filho da direita se existir
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int tem_direita(int Id, int size)
{
  return childRight_Id(Id) < size ;
}
/******************************************************************************
 * tem_pai()
 *
 * Argumentos: id do filho, e size ( tamanho do acervo)
 * Returns: id do pai se existir
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int tem_pai(int Id)
{
  return parent_Id(Id) >= 0;
}
/******************************************************************************
 * criancaEsquerda()
 *
 * Argumentos: id do pai, e vetor de vertices (acervo)
 * Returns: vertice do filho da esquerda
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
Vertex criancaEsquerda(int id, Vertex* items)
{
  return items[childLeft_Id(id)];
}
/******************************************************************************
 * criancaDireita()
 *
 * Argumentos: id do pai, e vetor de vertices (acervo)
 * Returns: vertice do filho da direita
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
Vertex criancaDireita(int id, Vertex* items)
{
  return items[childRight_Id(id)];
}
/******************************************************************************
 * pai()
 *
 * Argumentos: id do filho, e vetor de vertices (acervo)
 * Returns: vertice do pai
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
Vertex pai(int id, Vertex* items)
{
  return items[parent_Id(id)];
}
/******************************************************************************
 * swap()
 *
 * Argumentos: idOne, idTwo, e vetor de vertices(acervo)
 * Returns:
 * Side-Effects:
 *
 * Description: troca os vertices de posição no acervo
 *
 *
 *****************************************************************************/
void swap(int idOne, int idTwo, Vertex* items)
{
  Vertex aux = items[idOne];
  items[idOne] = items[idTwo];
  items[idTwo] = aux;
}
/******************************************************************************
 * heapUp()
 *
 * Argumentos: vetor de vertices e tamanho(size) do acervo
 * Returns:
 * Side-Effects: Faz com que o vetor estabeleça a condição de acervo
 *                com o novo elemento
 *
 * Description: Vai trocando os vertices de posição até que o pai tenha
 *              maior prioridade (menor custo)
 *
 *
 *****************************************************************************/
void heapUp(Vertex* items, int size)
{
  int id = size-1;
  while( tem_pai(id) >= 0 && items[(id-1)/2].cost > items[id].cost){
    swap(parent_Id(id), id, items);
    id = parent_Id(id);
  }
}
/******************************************************************************
 * heapDown()
 *
 * Argumentos: vetor de vertices e tamanho(size) do acervo
 * Returns:
 * Side-Effects: Faz com que o vetor estabeleça a condição de acervo
 *                com a remoção de um elemetno
 *
 * Description: Vai trocando os vertices de posição até que o filho tenha
 *              menorr prioridade (maior custo)
 *
 *
 *****************************************************************************/
void heapDown(Vertex* items, int size)
{
  int id = 0, i = 0;
  int id_child_pequena = 0;
  while(2*id < size -1){
    i++;
    id_child_pequena = childLeft_Id(id);
    if(tem_direita(id, size) < size -1 && criancaDireita(id, items).cost < criancaEsquerda(id, items).cost){
      id_child_pequena = childRight_Id(id);
    }
    if(items[id].cost < items[id_child_pequena].cost){
      break;
    }
    else{
      swap(id, id_child_pequena, items);
    }
    id = id_child_pequena;
  }
}
/******************************************************************************
 * poll()
 *
 * Argumentos: vetor de vertices,tamanho(size) do acervo, id de o elemento
 *              a retirar
 * Returns: Vertice a ser retirardo
 * Side-Effects: Retira um elemento do acervo
 *
 * Description:
 *
 *
 *****************************************************************************/
Vertex poll(Vertex* items, int id, int *size)
{
  if(*size < 0){
    exit(1);
  }
  else if (*size == 1)
  { (*size)--;
    return items[0];
  }
  Vertex root = items[0];
  items[0] = items[(*size)-1];
  (*size)--;

  heapDown(items, *size);
  return root;
}
Vertex* initHeap(int l, int c)
{
  Vertex* heap = (Vertex*)malloc(l*c*sizeof(Vertex));
  return heap;
}
/******************************************************************************
 * add()
 *
 * Argumentos: vetor de vertices,tamanho(size) do acervo, vertice a adicionar
 *
 * Returns:
 * Side-Effects: Adiciona o vertice x ao acervo
 *
 * Description: Aumenta o tamanho e faz-se heapUp para continuar a ser
 *              um acervo
 *
 *
 *****************************************************************************/
void add(Vertex* items, int *size, Vertex x)
{
  items[(*size)] = x;
  (*size)++;
  heapUp(items, *size);
}
