#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "findWay.h"

#define MaxDistance 1000

/******************************************************************************
 * PointOnMap()
 *
 * Argumentos: coordenadas do ponto e o ponteiro do mapa
 * Returns: 1 - se o ponto é válido
 *          0 - se é inválido
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int PointOnMap(int i, int j, Map* tabela)
{
    int valido = 0;
    if( i > tabela->nlin - 1 || i < 0 || j > tabela->ncol - 1 || j < 0 )
        valido = 0;
    else if( tabela->tabela[i][j] == 0 ){
        valido = 0;
    }
    else
        valido = 1;

    return ( valido );
}
/******************************************************************************
 * SelectProblem()
 *
 * Argumentos: ponteiro para o mapa e ponteiro para do novo ficheiro
 * Returns:
 * Side-Effects:
 *
 * Description: Consoante o modo executa o Problema
 *
 *
 *****************************************************************************/
void SelectProblem(Map* mapa, FILE* fout)
{
	switch(mapa->modo)
	{
	  case 'A':
        ProblemaA(mapa, fout);
        break;
      case 'B':
        ProblemaB(mapa, fout);
        break;
      case 'C':
        break;
      default:
        break;
    }
}
/******************************************************************************
 * adjArray()
 *
 * Argumentos: ponteiro para o mapa, posição l e col do ponto,
 *            vetor de vertices adj(adjacentes)
 * Returns:
 * Side-Effects:
 *
 * Description: adiciona ao vetor adj os pontos adjacentes válidos do ponto
 *
 *
 *****************************************************************************/
void adjArray(Map* mapa, int l, int col, Vertex* adj)
{
  Vertex lixo = {-1, -1, MaxDistance};
  /*Todas as combinações possíveis para a adjacência de 1 vertice
  de coordenadas l e col no mapa*/
  if( PointOnMap(l-2, col-1, mapa) ){
    Vertex x1 = {l-2, col-1, mapa->tabela[l-2][col-1]};
    /*add(items, size, x1);*/
    adj[0] = x1;
  }
  else{
    adj[0] = lixo;
  }
  if(PointOnMap(l-2, col+1, mapa) ){
    Vertex x2 = {l-2, col+1, mapa->tabela[l-2][col+1]};
    /*add(items, size, x2);*/
    adj[1] = x2;
  }
  else{
    adj[1] = lixo;
  }
  if(PointOnMap(l-1, col+2, mapa) ){
    Vertex x3 = {l-1, col+2, mapa->tabela[l-1][col+2]};
    /*add(items, size, x3);*/
    adj[2] = x3;
  }
  else{
    adj[2] = lixo;
  }
  if(PointOnMap(l+1, col+2, mapa) ){
    Vertex x4 = {l+1, col+2, mapa->tabela[l+1][col+2]};
    /*add(items, size, x4);*/
    adj[3] = x4;
  }
  else{
    adj[3] = lixo;
  }
  if(PointOnMap(l-1, col-2, mapa) ){
    Vertex x5 = {l-1, col-2, mapa->tabela[l-1][col-2]};
    /*add(items, size, x5);*/
    adj[4] = x5;
  }
  else{
    adj[4] = lixo;
  }
  if(PointOnMap(l+1, col-2, mapa) ){
    Vertex x6 = {l+1, col-2, mapa->tabela[l+1][col-2]};
    /*add(items, size, x6);*/
    adj[5] = x6;
  }
  else{
    adj[5] = lixo;
  }
  if(PointOnMap(l+2, col-1, mapa) ){
    Vertex x7 = {l+2, col-1, mapa->tabela[l+2][col-1]};
    /*add(items, size, x7);*/
    adj[6] = x7;
  }
  else{
    adj[6] = lixo;
  }
  if(PointOnMap(l+2, col+1, mapa) ){
    Vertex x8 = {l+2, col+1, mapa->tabela[l+2][col+1]};
    /*add(items, size, x8);*/
    adj[7] = x8;
  }
  else{
    adj[7] = lixo;
  }
}
/******************************************************************************
 * alocaST()
 *
 * Argumentos: ponteiro para o mapa
 * Returns: Ponteiro para a matriz ST
 * Side-Effects:
 *
 * Description: Aloca a matriz ST
 *
 *
 *****************************************************************************/
Vertex** alocaSt(Map* mapa)
{
  Vertex** st = (Vertex**)malloc((mapa->nlin) * sizeof(Vertex*));
  int i = 0;
  for(i = 0; i < (mapa->nlin); i++){
    st[i] = (Vertex*)malloc((mapa->ncol)*sizeof(Vertex));
  }
  return st;
}
/******************************************************************************
 * freeST()
 *
 * Argumentos: ponteiro para o mapa e matriz wt
 * Returns:
 * Side-Effects:
 *
 * Description: Liberta a memória da matriz ST
 *
 *
 *****************************************************************************/
void freeSt(Map* mapa, Vertex** st)
{
  int i = 0;
  for(i = 0; i < (mapa->nlin); i++){
    free(st[i]);
  }
  free(st);
}
/******************************************************************************
 * alocaWT()
 *
 * Argumentos: ponteiro para o mapa
 * Returns: Ponteiro para a matriz WT
 * Side-Effects:
 *
 * Description: Aloca a matriz WT
 *
 *
 *****************************************************************************/
int** alocaWT(Map* mapa)
{
  int** wt = (int**)malloc((mapa->nlin) * sizeof(int*));
  int i = 0;
  for(i = 0; i < (mapa->nlin); i++){
    wt[i] = (int*)malloc((mapa->ncol)*sizeof(int));
  }
  return wt;
}
/******************************************************************************
 * freeWT()
 *
 * Argumentos: ponteiro para o mapa e matriz wt
 * Returns:
 * Side-Effects:
 *
 * Description: Liberta a memória da matriz WT
 *
 *
 *****************************************************************************/
void freeWT(Map* mapa, int** wt)
{
  int i = 0;
  for(i = 0; i < (mapa->nlin); i++){
    free(wt[i]);
  }
  free(wt);
}
/******************************************************************************
 * initWT_ST()
 *
 * Argumentos: ponteiro para o mapa e matriz wt e st
 * Returns:
 * Side-Effects:
 *
 * Description: inicializa as matrizes wt e st com todos os valores
 *              MaxDistance e com um ponto inexistente, respetivamente
 *
 *
 *****************************************************************************/
void initWT_ST(Map* mapa, int** wt, Vertex** st)
{
  int i = 0, j = 0;
  for(i = 0; i < mapa->nlin; i++){
    for(j = 0; j < mapa->ncol; j++){
      wt[i][j] = MaxDistance;
      Vertex item = {-1, -1, 100};
      st[i][j] = item;
    }
  }
}
/******************************************************************************
 * DijkstraAlgorithmA()
 *
 * Argumentos: ponteiro para o mapa, o startingNode e endNode do tipo Vertex que
 *             que representam o ponto inicial e o final, e as matrizes wt e st
 *             que representam, respetivamente, o custo ótimo para cada ponto do mapa,
 *             e o vertice anterior do caminho ótimo para cada posição
 * Returns: 1 - se o endNode é visitado e o caminho é possível;
 *          0 - se o endNode não é visitado e o caminho é impossível;
 * Side-Effects: Calcula o melhor caminho de um ponto inicial a um final;
 *
 * Description: -Cria um acervo, vetor de prioridades a partir do initHeap
 *              -Adiciona ao acervo, os pontos adjacentes de cada ponto com a
 *              função add, e para cada iteração do ciclo while, retira o
 *              vertice de maior prioridade(menor custo)
 *              -Apenas sai do ciclo while, quando o caminho ótimo for calculado
 *
 *
 *****************************************************************************/
int DijkstraAlgorithmA(Map* mapa, Vertex startingNode, Vertex endNode, int** wt, Vertex** st)
{

  int size = 0, end = 0, t = 0;
  int x = mapa->ncol*mapa->nlin;
  Vertex* adj_arr = (Vertex*)malloc(8*sizeof(Vertex));
  Vertex* array_prio = initHeap(mapa->nlin, mapa->ncol);
  /*incializar startingNode*/
  wt[startingNode.l][startingNode.col] = 0;
  st[startingNode.l][startingNode.col].col = startingNode.col;
  st[startingNode.l][startingNode.col].cost = startingNode.cost;
  st[startingNode.l][startingNode.col].l = startingNode.l;
  add(array_prio, &size, startingNode, startingNode.cost);

  /*enquanto o acervo tiver vertices e o endNode não ter sido visitado*/
  while(size > 0 && end == 0){
    /*retirar o elemento de maior prioridade*/
    Vertex current = poll(array_prio, 0, &size);
    /*visitou o endNode*/
    if(current.l == endNode.l && current.col == endNode.col){
      end = 1;
    }
    /*verifica se o current está ligado a algum nó*/
    if(wt[current.l][current.col] != MaxDistance){
      /*adicona ao array os adjacentes*/
      adjArray(mapa, current.l, current.col, adj_arr);
      /*verifica cada um dos pontos adjacentes do current*/
      for(t = 0; t < 8; t++){
        /*se o adjacente existe*/
        if(adj_arr[t].cost != MaxDistance){
          /*adciiona apenas se o novo caminho é melhor que o anterior*/
          if(wt[adj_arr[t].l][adj_arr[t].col] > wt[current.l][current.col] + mapa->tabela[adj_arr[t].l][adj_arr[t].col]){
            /*atualiza a matriz wt e st*/
            wt[adj_arr[t].l][adj_arr[t].col] = wt[current.l][current.col] + mapa->tabela[adj_arr[t].l][adj_arr[t].col];
            st[adj_arr[t].l][adj_arr[t].col] = current;

            adj_arr[t].cost = wt[adj_arr[t].l][adj_arr[t].col];
            /*condiçao para se alocar mais memória se necessário*/
            if(size == x){
              x += x;
              Vertex* array_prio2 = (Vertex*)realloc(array_prio, x*sizeof(Vertex));
              array_prio = array_prio2;
            }
            /*adicionar o vertice ao acervo*/
            add(array_prio, &size, adj_arr[t]);
          }
        }
        /*incializar os pontos do array de adjacentes*/
        adj_arr[t].cost = MaxDistance;
        adj_arr[t].l = -1;
        adj_arr[t].col = -1;
      }
    }
  }
  free(array_prio);
  free(adj_arr);
  if(!end)
    return 0;
  return 1;
}
/******************************************************************************
 * caminhoDiretoA()
 *
 * Argumentos: ponteiro para o mapa e indice para o checkpoint
 * Returns: 1 - se o ponto final é o mesmo que o ponto incial do caminho anterior
 *          0 - se o ponto final é diferente do ponto incial do caminho anterior
 * Side-Effects:
 *
 * Description: Verifica se o caminho é o mesmo que o anterior
 *
 *
 *****************************************************************************/
int caminhoDiretoA(Map* mapa, int i)
{
  /*ambos os pontos existem no mapa*/
  if(PointOnMap(mapa->pontos[i].lin, mapa->pontos[i].col, mapa) && PointOnMap(mapa->pontos[i+1].lin, mapa->pontos[i+1].col, mapa)){
    /*ponto final é adjacente do ponto incial*/
    if((abs(mapa->pontos[i].lin-mapa->pontos[i+1].lin) == 2 && abs(mapa->pontos[i].col - mapa->pontos[i].lin) == 1) ||
      (abs(mapa->pontos[i].lin-mapa->pontos[i+1].lin) == 1 && abs(mapa->pontos[i].col-mapa->pontos[i+1].col) == 2)){

      return 1;
    }
    else{
      return 0;
    }
  }
  return 0;
}
/******************************************************************************
 * compareCheck()
 *
 * Argumentos: ponteiro para o mapa e indice para o checkpoint
 * Returns: 1 - se os checkpoints são iguais
 *          0 - se checkpoints são diferentes
 * Side-Effects:
 *
 * Description: Verifica se os pontos são iguais para não se usar o
 *              Dijkstra pela resposta ser trivial
 *
 *
 *****************************************************************************/
int compareCheck(Map* mapa, int i)
{
  /*se os checkpoints são iguais*/
  if(mapa->pontos[i].lin == mapa->pontos[i+1].lin && mapa->pontos[i].col == mapa->pontos[i+1].col){
    return 1;
  }
  return 0;
}/******************************************************************************
 * validCheck()
 *
 * Argumentos: ponteiro para o mapa
 * Returns: 1 - se todos os checkpoints são válidos(dentro do mapa e com valor
 *              diferente de 0)
 *          0 - se algum checkpoints é inválido
 * Side-Effects:
 *
 * Description: Verifica para cada checkpoint com a função PointOnMap
 *
 *
 *****************************************************************************/
int validCheck(Map* mapa)
{
  int i = 0;
  for(i = 0; i < mapa->n_checkp; i++){
    if(!PointOnMap(mapa->pontos[i].lin, mapa->pontos[i].col, mapa)){
      return 0;
    }
  }
  return 1;
}
/******************************************************************************
 * samePath()
 *
 * Argumentos: ponteiro para o mapa e indice para o checkpoint
 * Returns: 1 - se o ponto final é o mesmo que o ponto incial do caminho anterior
 *          0 - se o ponto final é diferente do ponto incial do caminho anterior
 * Side-Effects:
 *
 * Description: Verifica se o caminho é o mesmo que o anterior
 *
 *
 *****************************************************************************/
int samePath(Map* mapa, int i)
{
  if(i-1 >= 0){
    /*Mesmo caminho do que anterior*/
    if(mapa->pontos[i-1].lin == mapa->pontos[i+1].lin && mapa->pontos[i-1].col == mapa->pontos[i+1].col){
      return 1;
    }
  }
  return 0;
}
/******************************************************************************
 * accessibleCheckPoints()
 *
 * Argumentos: ponteiro para o mapa
 * Returns: 1 - se todos os pontos são acessíveis
 *          0 - se é impossível aceder a algum dos pontos
 * Side-Effects:
 *
 * Description:
 *
 *
 *****************************************************************************/
int accessibleCheckPoints(Map* mapa)
{
  int count = 0, i = 0, l = 0, col = 0;
  for(i = 0; i < mapa->n_checkp; i++){
    count = 0;
    l = mapa->pontos[i].lin;
    col = mapa->pontos[i].col;
    if( !PointOnMap(l-2, col-1, mapa) ){
      count++;
    }
    if(!PointOnMap(l-2, col+1, mapa) ){
      count++;
    }
    if(!PointOnMap(l-1, col+2, mapa) ){
      count++;
    }
    if(!PointOnMap(l+1, col+2, mapa) ){
      count++;
    }
    if(!PointOnMap(l-1, col-2, mapa) ){
      count++;
    }
    if(!PointOnMap(l+1, col-2, mapa) ){
      count++;
    }
    if(!PointOnMap(l+2, col-1, mapa) ){
      count++;
    }
    if(!PointOnMap(l+2, col+1, mapa) ){
      count++;
    }
    if(count == 8)
      return 0;
  }

  return 1;
}
/******************************************************************************
 * insertArray()
 *
 * Argumentos: mapa, matriz st, array de vertices que guarda o caminho, ponto
 *             inicial e final do caminho e número de passos
 *
 * Returns:
 * Side-Effects:
 *
 * Description: insere no vetor os pontos por ordem inversa do caminho a
 *              partir da matriz st
 *
 *
 *****************************************************************************/
void insertArray(Map* mapa, Vertex** st, Vertex* array, Vertex startingNode, Vertex endNode, int* n_passos)
{
  int c = endNode.l, f = endNode.col;
  /*adicionar o ultimo vertice da iteração*/
  (*n_passos)++;
  array[(*n_passos)-1] = endNode;

  while(st[c][f].l != startingNode.l || st[c][f].col != startingNode.col){
    (*n_passos)++;
    array[(*n_passos)-1] = st[c][f];
    array[(*n_passos-1)].cost = mapa->tabela[st[c][f].l][st[c][f].col];
    int aux = st[c][f].l;
    int aux2 = st[c][f].col;
    c = aux;
    f = aux2;
  }
}
/******************************************************************************
 * ProblemaA()
 *
 * Argumentos: ponteiro para o mapa e para o ficheiro a ser escrito
 * Returns: void
 * Side-Effects: imprime no ficheiro a solução do mapa de Problema A
 *
 * Description: -Verifica se os checkpoint são válidos, se estão dentro do mapa
 *              ao se o seu valor é diferente de 0 com a função validCheck;
 *              -Se o caminho é direto, isto é, por um salto de cavalo,
 *              imprime diretamente
 *              -Depois calcula-se o melhor caminho com o Dijkstra;
 *
 *
 *****************************************************************************/
void ProblemaA(Map* mapa, FILE* fout)
{
  int n_passos = 0;
  /*se for um ponto adjacente ao inicial é escusado usar o Dijkstra*/
  int i = caminhoDiretoA(mapa, 0);
  if(validCheck(mapa) && accessibleCheckPoints(mapa)){
    if(i == 1){
      fprintf(fout, "%d %d %c %d %d %d\n", mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, mapa->tabela[mapa->pontos[1].lin][mapa->pontos[1].col], 1);
      fprintf(fout, "%d %d %d\n", mapa->pontos[1].lin, mapa->pontos[1].col, mapa->tabela[mapa->pontos[1].lin][mapa->pontos[1].col]);
    }
    else if(compareCheck(mapa, 0)){
      EscreverSaida(fout, mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, 0, 0);
    }
    else{
      /*vetor de distnacia ( wt[L][C])*/
      int** wt = alocaWT(mapa);
      /*matriz caminho st[L][C]*/
      Vertex** st = alocaSt(mapa);
      /*incia os vetores wt e st*/
      initWT_ST(mapa, wt, st);
      Vertex startingNode = {mapa->pontos[0].lin, mapa->pontos[0].col, mapa->tabela[mapa->pontos[0].lin][mapa->pontos[0].col]};
      Vertex endNode = {mapa->pontos[1].lin, mapa->pontos[1].col, mapa->tabela[mapa->pontos[1].lin][mapa->pontos[1].col]};

      if(DijkstraAlgorithmA(mapa, startingNode, endNode, wt, st)){
        /*se a distancia ao nó for diferente de infinito há caminho*/

        if(wt[endNode.l][endNode.col] != MaxDistance){
          Vertex* array = initArray();
          insertArray(mapa, st, array, startingNode, endNode, &n_passos);
          fprintf(fout, "%d %d %c %d %d %d\n", mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, wt[endNode.l][endNode.col], n_passos);
          WriteA(fout, array, n_passos);
          free(array);
        }
        else{
          EscreverSaida(fout, mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, 0, -1);
        }
      }
      else{
        EscreverSaida(fout, mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, 0, -1);
      }
      /*free de tudo que foi utilizado*/
      freeSt(mapa, st);
      freeWT(mapa, wt);
    }
  }
  else{
    EscreverSaida(fout, mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, 0, -1);
  }
}
/******************************************************************************
 * ProblemaB()
 *
 * Argumentos: ponteiro para o mapa e para o ficheiro a ser escrito
 * Returns: void
 * Side-Effects: imprime no ficheiro a solução do mapa de Problema B
 *
 * Description: -Verifca se os checkpoint são válidos, se estão dentro do mapa
 *              ao se o seu valor é diferente de 0 com a função validCheck;
 *              -Para cada caminho compara se os ponto de partida e de chegada
 *              são iguais com a função compareCheck;
 *              -Função samePath permite verificar se o caminho é o mesmo que
 *              o anteriormente calculado, para não ter de efectuar o DijkstraAlgorithmA
 *              novamente;
 *              -Usar o Dijkstra para calcular o melhor caminho;
 *
 *
 *****************************************************************************/
void ProblemaB(Map* mapa, FILE* fout)
{
  int n = mapa->n_checkp-1, custo = 0, n_passos = 0;
  int** wt = alocaWT(mapa);
  int* check_id = (int*)calloc(n, sizeof(int));
  Vertex** st = alocaSt(mapa);
  Vertex* array = NULL;
  /*incia os vetores wt e st*/
  initWT_ST(mapa, wt, st);
  Vertex startingNode = {mapa->pontos[0].lin, mapa->pontos[0].col, mapa->tabela[mapa->pontos[0].lin][mapa->pontos[0].col]};
  Vertex endNode = {mapa->pontos[1].lin, mapa->pontos[1].col, mapa->tabela[mapa->pontos[1].lin][mapa->pontos[1].col]};

  /*Cálculo de cada caminho para cada checkpoint*/
  int control = 0, i = 0, j = 0, x = 0, y = 0;
  int compare = 0, guarda = 0;
  /*verificar se os checkpoints são válidos e acessíveis*/
  if(validCheck(mapa) && accessibleCheckPoints(mapa)){
    array = initArray();

    for(i = 0; i < n; i++){
      /*inicializar as variáveis para a iteração*/
      initWT_ST(mapa, wt, st);
      startingNode.l = mapa->pontos[i].lin; startingNode.col = mapa->pontos[i].col;
      startingNode.cost = mapa->tabela[mapa->pontos[i].lin][mapa->pontos[i].col];
      endNode.l = mapa->pontos[i+1].lin; endNode.col = mapa->pontos[i+1].col;
      endNode.cost = mapa->tabela[mapa->pontos[i+1].lin][mapa->pontos[i+1].col];
      /*se são iguais não é preciso fazer nada*/
      if(compareCheck(mapa, i)){
        control++;
        compare++;
        check_id[i] = -1;
        continue;
      }
      /*verificar se os pontos estão a um salto de cavalo*/
      if(caminhoDiretoA(mapa, i)){
        control++;
        custo = custo + mapa->tabela[mapa->pontos[i+1].lin][mapa->pontos[i+1].col];
        n_passos++;
        if(i == 0)
          check_id[i] = 0;
        else
          check_id[i] = check_id[i-1]+1;
        array[check_id[i]] = endNode;
        continue;
      }
      /*se o caminho é o mesmo entao nao é preciso fazer o dijkstra*/
      if(samePath(mapa, i)){
        /*se só houver 1 checkpoint anterior*/
        /*x guarda o id do proximo caminho*/
        if(i-1 == 0){
          x = 2*check_id[i-1]+1;
        }
        else{
          x = check_id[i-1]-check_id[i-2];
          x = x + check_id[i-1];
        }
        /*y = ao id do checkpoint anterior que fez o mesmo caminho*/
        y = check_id[i-1]-1;
        array[check_id[i-1]+1] = endNode;
        for(j = check_id[i-1]+2; j <= x; j++){
          if(y == check_id[i-2]){
            break;
          }
          array[j] = array[y+1];
          y--;
          /*se chegou ao id do startingNode anterior*/
        }
        /*o endNode é o último vertice do caminho por isso colocado na posição x*/
        /*atualiza o custo*/
        custo = custo + guarda -
              mapa->tabela[startingNode.l][startingNode.col] + mapa->tabela[endNode.l][endNode.col];

        check_id[i] = x;
        /*atualiza o número de passos*/
        if(i-1 == 0)
          n_passos = n_passos + check_id[i] - check_id[i-1];
        else
          n_passos = n_passos + check_id[i] - check_id[i-1];
        control++;
        continue;
      }
      /*Usar o Dijkstra*/
      else if(DijkstraAlgorithmA(mapa, startingNode, endNode, wt, st)){
        custo = custo + wt[endNode.l][endNode.col];
        guarda = wt[endNode.l][endNode.col];
        insertArray(mapa, st, array, startingNode, endNode, &n_passos);
        control++;
      }
      /*se no Dijkstra não é possível encontrar o ponto final, então o caminho é impossível*/
      else{
        EscreverSaida(fout, mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, 0, -1);
        break;
      }
      check_id[i] = n_passos-1;
    }
  }
  /*se os pontos não são válidos, então o mapa é impossível*/
  else{
    EscreverSaida(fout, mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, 0, -1);
  }
  /*Só escrever se os pontos todos têm solução*/
  if(control == mapa->n_checkp-1){
    fprintf(fout, "%d %d %c %d %d %d\n", mapa->nlin, mapa->ncol, mapa->modo, mapa->n_checkp, custo, n_passos);
    /*só imprime se os checkpoints não forem todos iguais*/
    if(compare != mapa->n_checkp-1)
      printArrayST(fout, array, check_id, n);
  }
  free(array);
  free(check_id);
  freeSt(mapa, st);
  freeWT(mapa, wt);
}
