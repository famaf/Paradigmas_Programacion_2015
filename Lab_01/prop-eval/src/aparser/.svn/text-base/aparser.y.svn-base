/* Archivo:: asignacion.y
 * Descripcion:: Archivo de especificacion utilizado por bison. 
 */

/* Describir esto*/

%name-prefix "a_"

%{
 #include <stdio.h>
 #include "misc.h"
 #include "assignment.h"

 /*funciones definidas por el lexer*/
 extern int a_lex();
 extern int a_error(char *s);
 extern int a_lex_destroy(); 
 extern FILE *a_in;
 extern int a_lineno;
 
 Asgmnt *asg; 
 char *aname;
%}

/* COMPLETAR AQUI */

%%



%%
/* Funcion que se provee para parsear una asignacion en un archivo.*/
void parse_assignment(FILE * input)
{
  a_lineno = 1;
  a_in = input;
  if (!a_in)
    log_error("parse_assignment: no input file.");
  a_parse();
  a_lex_destroy();
}


/* Funcion que se ejecuta cuando ocurre un error durante el parseo.*/
int a_error(char *s)
{
  log_error(" %s - parser error - %s\n",aname,s);
  return 0;
}
