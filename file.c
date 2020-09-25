#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

/******************************************************************************
 * validParameters()
 *
 * Argumentos: número de linhas e colunas, modo e número de checkpoint do mapa
 *
 * Returns: 1 - se são válidos consoante o modo
 *          0 - se são inválidos
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int validParameters(int l, int col, char modo, int n_checkp){

  int valid = 0;
  if(modo == 'A'){
    /*se houver mais que um ponto de chegada*/
    if(n_checkp != 2)
      return valid = 0;
  }
  else if(modo == 'B'){
    /*se houver menos checkpoints*/
    if(n_checkp < 2)
      return valid = 0;
  }
  else if(modo != 'A' && modo != 'B' && modo != 'C'){
    /*se o modo nao for aceite*/
    return valid = 0;
  }
  /*se estão todos bem*/
  return valid = 1;
}
/******************************************************************************
 * alocaTabela()
 *
 * Argumentos: número de linhas e colunas, modo e número de checkpoint do mapa
 *
 * Returns: ponteiro para um novo mapa do tipo Map
 * Side-Effects:
 *
 * Description: Aloca memória para o novo mapa
 *
 *
 *****************************************************************************/
Map* alocaTabela(int l, int col, char modo, int n_checkp)
{
  int i = 0;
  Map* mapa = NULL;

  /*aloca o mapa*/
  mapa = (Map*)malloc(sizeof(Map));
  if(mapa == NULL){
    exit(0);
  }
  mapa->nlin = l;
  mapa->ncol = col;
  mapa->modo = modo;
  mapa->n_checkp = n_checkp;
  mapa->pontos = NULL;
  mapa->pontos = (checkp*)malloc(n_checkp*sizeof(checkp));
  if(mapa->pontos == NULL){
    exit(0);
  }
  /*aloca linhas da tabela*/
  mapa->tabela = NULL;
  mapa->tabela = (int**) malloc (l*sizeof(int*));
  if((*mapa).tabela == NULL){
    exit(0);
  }
  /*aloca colunas da tabela*/
  for(i = 0; i < mapa->nlin; i++){
     mapa->tabela[i] = (int*) malloc ((mapa->ncol)*sizeof(int));
     if((*mapa).tabela[i] == NULL){
       exit(0);
     }
  }
  return mapa;
}
/******************************************************************************
 * freeMap()
 *
 * Argumentos: pontiero para o mapa
 *
 * Returns:
 * Side-Effects:
 *
 * Description: Liberta a memória do mapa
 *
 *
 *****************************************************************************/
void freeMap(Map* mapa)
{
  int i = 0;
  if(mapa == NULL)
    exit(0);

  for(i = 0; i < mapa->nlin; i++){
    free(mapa->tabela[i]);
  };
  free(mapa->pontos);
  free(mapa->tabela);
  free(mapa);
}
/******************************************************************************
 * lerficheiro()
 *
 * Argumentos: nome do novo ficheirp
 *
 * Returns:
 * Side-Effects:
 *
 * Description: lê o ficheiro de entrada, cria o(s) mapa(s) do ficheiro e
 *              escreve a solução no novo ficheiro
 *
 *
 *****************************************************************************/
void lerficheiro(char* fileName)
{
  FILE* fp = NULL;
  FILE* fout = NULL;
  int i = 0, l = 0, j = 0, len = 0;
  char modo = '\0', *outfile = NULL;
  int col = 0, n_checkp = 0, variavel = 0, garbage = 0;

  Map* mapa = NULL;
  /*abre o ficheiro a ser lido*/
  fp = fopen(fileName, "r");
  if(fp == NULL){
    exit(0);
  }
  /*criação do novo ficheiro .walks*/
  outfile = (char*)calloc(1, (strlen(fileName))*sizeof(char));
  len = strlen(fileName) - strlen(".cities");
  strncpy(outfile, fileName, len);
  strcat(outfile, ".walks");
  if(fout == NULL){
    fout = fopen(outfile, "w");
    if(fout == NULL){
      exit(0);
    }
  }
  /*abre o ficheiro a escrever*/
  while (fscanf(fp, "%d %d %c %d", &l, &col, &modo, &n_checkp) == 4 ){

    /*se os parametros são válidos*/
    if(validParameters(l, col, modo, n_checkp)){
      /*se o mapa é válido então o resto está bem*/
      if(mapa != NULL)
        freeMap(mapa);

      mapa = alocaTabela(l, col, modo, n_checkp);
      /*lê o mapa do ficheiro*/
      for(i = 0; i < mapa->n_checkp; i++){
        variavel = fscanf(fp, "%d", &(mapa->pontos[i].lin));
        variavel = fscanf(fp, "%d", &(mapa->pontos[i].col));
      }

      for(i = 0; i < mapa->nlin; i++){
        for(j = 0; j < mapa->ncol; j++){
          variavel = fscanf(fp, "%d ", &(mapa->tabela[i][j]));
        }
      }
      SelectProblem(mapa, fout);
    }
    else{
      /*escreve que não existe solução e é inválido*/
      EscreverSaida(fout, l, col, modo, n_checkp, 0, -1);
      /*passar o mapa inválido*/
      for(i = 0; i < n_checkp; i++){
        garbage = fscanf(fp, "%d", &variavel);
        fscanf(fp, "%d", &variavel);
      }
      for(i = 0; i < l; i++){
        for(j = 0; j < col; j++){
          garbage = fscanf(fp, "%d", &variavel);
        }
      }
    }
  }
  garbage++;
  free(outfile);
  freeMap(mapa);

  fclose(fp);
  fclose(fout);
}
/******************************************************************************
 * EscreverSaida()
 *
 * Argumentos: ponteiro do novo ficheiro, número de linhas e colunas,
 *            modo, número de checkpoints, valido e custo do caminho
 *
 * Returns:
 * Side-Effects:
 *
 * Description: escreve no ficheiro de saída a solução
 *
 *
 *****************************************************************************/
void EscreverSaida( FILE* fp, int l, int col, int modo, int n_checkp, int valido, int custo)
{
  fprintf( fp, "%d %d %c %d %d %d\n\n", l, col, modo, n_checkp, custo , valido);
}
/******************************************************************************
 * initArray()
 *
 * Argumentos:
 *
 * Returns: ponteiro para um array de vertices
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
Vertex* initArray()
{
  Vertex* array = (Vertex*)malloc(3000*sizeof(Vertex));
  return array;
}
/******************************************************************************
 * WriteA()
 *
 * Argumentos: ponteiro para o ponteiro de saída, vetor de vertices,
 *            número de passos
 *
 * Returns:
 * Side-Effects:
 *
 * Description: escreve no ficheiro de saída a solução do mapa A
 *              guardada no vetor
 *
 *
 *****************************************************************************/
void WriteA(FILE* fout, Vertex* array, int n_passos)
{
  int i = 0;
  for(i = n_passos-1; i >= 0; i--){
    fprintf(fout, "%d %d %d\n", array[i].l, array[i].col, array[i].cost);
  }
  fprintf(fout, "\n");
}
/******************************************************************************
 * printArrayST()
 *
 * Argumentos: ponteiro para o ponteiro de saída, vetor de vertices,
 *            vetor que guarda o index do ponto incial de cada caminho
 *            para cada checkpoint
 *
 * Returns:
 * Side-Effects:
 *
 * Description: imprime cada caminho para cada checkpoint, guardado
 *              no array, sendo que o check_id guarda o index para
 *              o primeiro elemento de cada caminho (o vetor tem o caminho
 *              guardado inversamente)
 *
 *
 *****************************************************************************/
void printArrayST(FILE* fout, Vertex* array, int* check_id, int n)
{
  int prev = -1, i = 0, j = 0;
  for(i = 0; i < n; i++){
    if(check_id[i] == -1){
      continue;
    }
    for(j = check_id[i]; j > prev; j--){
      fprintf(fout, "%d %d %d\n", array[j].l, array[j].col, array[j].cost);
    }
    prev = check_id[i];
  }
  fprintf(fout, "\n");
}
