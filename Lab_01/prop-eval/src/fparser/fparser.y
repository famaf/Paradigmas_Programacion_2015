/* Archivo:: formula.y
 * Descripcion:: Archivo de especificacion utilizado por bison. 
 */

/* Describir esto*/

%name-prefix "f_"

%{
#define _POSIX_C_SOURCE 1
 #include <stdio.h>
 #include "misc.h"
 #include "ast.h" 
 extern int f_lex();
 extern int f_error(char *s);
 extern int f_lex_destroy(); 
 extern FILE *f_in;
 extern int f_lineno;
 ASTNode *ast;
 char *fname;
 /*nodo temporal que se usa para crear el AST. */
 ASTNode *n;
%}

/* Declaracion de yyval: yyval es la variable que  */
%union {
  ASTNode *a;
  int v;
}

/* Tokens*/
%token <v> TK_PROP
%token TK_BEGIN
%token TK_END
%token TK_AND
%token TK_OR
%token TK_IMPL
%token TK_IFF
%token TK_NOT
%token TK_TRUE
%token TK_FALSE
%token TK_OP
%token TK_CP

/* PRECEDENCIA DE LOS OPERADORES */
/* EL DE MAS ARRIBA TIENE MENOS PRECEDENCIA QUE EL DE ABAJO */
/* SI SE PONEN EN LA MISMA LINEA, TENDRÁ LA MISMA PRECEDENCIA */
%left TK_IFF /*CAMBIADO*/ 
%left TK_IMPL /*CAMBIADO*/
%left TK_OR /*CAMBIADO*/
%left TK_AND/*CAMBIADO*/
%left TK_NOT /*CAMBIADO*/

 /* Define el tipo de datos que retorna la bnf*/
%type <a> formula input

%%
/* Simbolo inicial */
input: TK_BEGIN formula TK_END {ast = $2;};

/* COMPLETAR ACA */
formula: TK_PROP                  {ASTNODE_PROP(n,$1); $$ =n ;} /*------*/
       | formula TK_OR formula    {ASTNODE_OR(n,$1,$3); $$ =n ;} /*------*/
       | formula TK_AND formula   {ASTNODE_AND(n,$1,$3); $$ =n ;} /*------*/
       | formula TK_IMPL formula  {ASTNODE_IMPL(n,$1,$3); $$ =n ;} /*------*/
       | formula TK_IFF formula   {ASTNODE_IFF(n,$1,$3); $$ =n ;} /*------*/
       | TK_NOT formula           {ASTNODE_NOT(n,$2); $$ =n ;} /*------*/
       | TK_OP formula TK_CP      {$$= $2;} /*------*/
       | TK_TRUE                  {ASTNODE_TRUE(n); $$ =n;} /*------*/
       | TK_FALSE                 {ASTNODE_FALSE(n); $$ =n;}; /*------*/
%%

/* Funcion que se provee para parsear una formula en un archivo.*/
void parse_formula(FILE * input)
{
  f_lineno = 1;
  f_in = input;
  if (!f_in)
    log_error("parse_formula: no input file.");
  f_parse();
  f_lex_destroy();
}

/* Funcion que se ejecuta cuando ocurre un error durante el parseo.*/
int f_error(char *s)
{
    log_error(" %s - parser error - %s\n",fname,s);
    return 0;
}
