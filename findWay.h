/******************************************************************************
 *
 * File Name: findWay.h
 *	      (c) 2018 AED
 * Author:    Daniel Rosa e Tiago Galeão
 * Revision:
 *
 * NAME
 *     findway.h - biblioteca para implementação de calcular o melhor caminho
 *                  entre 2 pontos
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

#ifndef _FINDWAY_H
#define _FINDWAY_H

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "file.h"
#include "defs.h"

int PointOnMap(int i, int j, Map* tabela);
int HorseJump (Map* Tabela, int i);
void SelectProblem( Map* mapas , FILE* fout);
void adjArray(Map* mapa, int l, int col, Vertex* adj);
Vertex** alocaSt(Map* mapa);
void freeSt(Map* mapa, Vertex** st);
int** alocaWT(Map* mapa);
void freeD(Map* mapa, int** d);
void initWT_ST(Map* mapa, int** wt, Vertex** st);
int DijkstraAlgorithmA(Map* mapa, Vertex startingNode, Vertex endNode, int** wt, Vertex** st);
int caminhoDiretoA(Map* mapa, int i);
int compareCheck(Map* mapa, int i);
int validCheck(Map* mapa);
int samePath(Map* mapa, int i);
int accessibleCheckPoints(Map* mapa);
void insertArray(Map* mapa, Vertex** st, Vertex* array, Vertex startingNode, Vertex endNode, int* n_passos);
void ProblemaA( Map* mapa, FILE* fout);
void ProblemaB(Map* mapa, FILE* fout);
#endif
