/******************************************************************************
 *
 * File Name: defs.h
 *	      (c) 2018 AED
 * Author:    Daniel Rosa e Tiago Galeão
 * Revision:
 *
 * NAME
 *     defs.h - implementação de uma estrutura de um mapa
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

#ifndef _DEFS_H
#define _DEFS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int lin;
  int col;
} checkp;

typedef struct{
  int nlin;
  int ncol;
  char modo;
  int** tabela;
  int n_checkp;
  checkp* pontos;
} Map;

#endif
