/* Archivo:: asignacion.l 
 * Descripcion:: Archivo de especificacion utilizado por lex. A partir de este
 * archivo lex genera el analizador lexico para parsear las asignaciones.
 */

%option  noyywrap case-insensitive yylineno
%option prefix="a_"

%{
#include "misc.h"
#include "aparser.tab.h"
#include <stdio.h>
int a_lval;
extern char* aname;
%}

			
%%
.                             { log_error(" %s - lexer error - at line %d: %s\n",aname,a_lineno,a_text); }      
%%
