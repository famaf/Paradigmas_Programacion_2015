#include <stdio.h>
#include "assignment.h"
#include "aparser.h"
#include "misc.h"

/*Variable que contiene la asignacion.*/
extern Asgmnt  *asg;

/*Nombre del archivo que contiene la asignacion.*/
extern char *aname;

int main(int argc, char **argv)
{
  FILE *a;

  /* Verificamos el nro de argumentos. */
  if (argc != 2)
    {
      log_error("test-aparser.c: nro de argumentos erroneo. Debe especificar una asignacion.\n");
      return (1);
    }

 /*Abrimos el archivo correspondiente a la asignacion*/  
  aname = argv[1];
  if(!(a = fopen(aname, "r"))){
    log_error("test-aparser.c: No se pudo abrir el archivo %s.\n", aname);
    return (1);
  }
  /* Parseamos la asignacion */
  parse_assignment(a);
  printf("ok: %s\n",aname);
  return 0;
}
