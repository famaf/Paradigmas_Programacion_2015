#include <stdio.h>
#include "ast.h"
#include "fparser.h"
#include "misc.h"

/*Variable que contiene el AST.*/
extern ASTNode *ast;
/*Nombre del archivo que contiene la formula.*/
extern char *fname;

int main(int argc, char **argv)
{
  FILE *f;

  /* Verificamos el nro de argumentos. */
  if (argc != 2)
    {
      log_error("test-fparser.c: nro de argumentos erroneo. Debe especificar una formula.\n");
      return (1);
    }

 /*Abrimos el archivo correspondiente a la formula*/  
  fname = argv[1];
  if(!(f = fopen(argv[1], "r"))){
    log_error("test-fparser.c: No se pudo abrir el archivo %s.\n", fname);
    return (1);
  }
  /* Parseamos la formula */
  parse_formula(f);
  printf("ok: %s\n",fname);
  return 0;
}
