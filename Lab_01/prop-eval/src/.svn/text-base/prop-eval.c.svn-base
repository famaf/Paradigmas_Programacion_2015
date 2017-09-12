#include <stdio.h>
#include "evaluator.h"
#include "ast.h"
#include "assignment.h"
#include "fparser.h"
#include "aparser.h"
#include "misc.h"

/*Variable que contiene el AST.*/
extern ASTNode *ast;
extern char *fname;
extern char *aname;

/*Variable que contiene la asignacion.*/
extern Asgmnt  *asg;

int main(int argc, char **argv)
{
  FILE *f,*a;

  /* Verificamos el nro de argumentos. */
  if (argc != 3)
    {
      log_error("prop_eval.c: nro de argumentos erroneo. Deben ser <formula> <asignacion>.\n");
      perror(argv[1]);
      return (1);
    }
  
  /*Abrimos el archivo correspondiente a la formula*/
  fname = argv[1];
  if(!(f = fopen(fname, "r"))){
    log_error("prop_eval.c: No se pudo abrir el archivo %s.\n", fname);
    return (1);
  }

  /*Abrimos el archivo correspondiente a la asignacion*/
  aname = argv[2];
  if(!(a = fopen(aname, "r"))){
    log_error("prop_eval.c: No se pudo abrir el archivo %s.\n", aname);
    return (1);
  }

  /* ---------------------- */
  /* /\* COMPLETAR AQUI *\/ */
  /* ---------------------- */

  switch(eval(ast,asg))
    {
    case 1:
      printf("True\n");
      break;
    case 0:
      printf("False\n"); 
      break;
    case -1:
      printf("Error\n"); 
      break;
    }

  return 0;
}
