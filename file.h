/******************************************************************************
 *
 * File Name: file.h
 *	      (c) 2018 AED
 * Author:    Daniel Rosa e Tiago Galeão
 * Revision:
 *
 * NAME
 *     file.h - biblioteca para implementação de leitura e escrita de ficheiro
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

#ifndef _READFILE_H
#define _READFILE_H

#include <stdio.h>
#include <stdlib.h>
#include "findWay.h"
#include "heap.h"
#include "defs.h"

int validParameters(int l, int col, char modo, int n_checkp);
Map* alocaTabela(int l, int col, char modo, int n_checkp);
void freeMap(Map* mapa);
void lerficheiro(char* fileName);
void EscreverSaida( FILE* fp, int l, int col, int modo, int n_checkp, int valido, int custo);
Vertex* initArray();

void WriteA(FILE* fout, Vertex* array, int n_passos);
void printArrayST(FILE* fout, Vertex* array, int* check_id, int n);

#endif
