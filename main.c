#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "findWay.h"
#include "heap.h"
#include "file.h"

void  argumentos(char** argv, int argc){
  char typeFile[] = ".cities";

  if(argc != 2){
    exit(0);
  }
  /*argumento não é válido*/
  if(strstr(argv[1], typeFile) == NULL){
    exit(0);
  }
}

int main(int argc, char** argv)
{
  argumentos(argv, argc);
  lerficheiro(argv[1]);
  return 0;
}
