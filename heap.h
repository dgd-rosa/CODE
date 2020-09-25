/******************************************************************************
 *
 * File Name: heap.h
 *	      (c) 2018 AED
 * Author:    Daniel Rosa e Tiago Galeão
 * Revision:
 *
 * NAME
 *     heap.h - biblioteca para implementação de um acervo
 *
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#ifndef _HEAP_H
#define _HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
  int l;
  int col;
  int cost;
}Vertex;

int childLeft_Id(int parent_id);
int childRight_Id(int parent_id);
int parent_Id(int child_id);
int tem_esquerda(int Id, int size);
int tem_direita(int Id, int size);
int tem_pai(int Id);
Vertex criancaEsquerda(int id, Vertex* items);
Vertex criancaDireita(int id, Vertex* items);
Vertex pai(int id, Vertex* items);
void swap(int idOne, int idTwo, Vertex* items);
void heapUp(Vertex* items, int size);
void heapDown(Vertex* items, int size);
Vertex poll(Vertex* items, int id, int *size);
Vertex* initHeap(int l, int c);
#endif
