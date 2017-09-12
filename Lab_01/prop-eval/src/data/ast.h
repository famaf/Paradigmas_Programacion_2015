#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"

/*
--------------------------------------------------------------------------------
Este modulo define la estructura de datos que representa 
el Abstract Syntax Tree (AST) retornado por el parser.
--------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
Definicion de los tipos de nodos del AST
--------------------------------------------------------------------------------
*/
#define PROP   0
#define OR     1
#define AND    2
#define NOT    3
#define IFF    4
#define IMPL   5
#define OP     6
#define CP     7
#define COMMA  8
#define TRUE   9
#define FALSE 10
#define UNKNW 11


/*
--------------------------------------------------------------------------------
Estructura de datos que representa un nodo del AST
--------------------------------------------------------------------------------
*/

typedef struct ASTNode 
{
  /* tipo de nodo */
  int type;
  /* id del nodo*/
  int id;
  /* puntero al sucesor derecho*/
  struct ASTNode *r_succ;
  /* puntero al sucesor izquierdo*/
  struct ASTNode *l_succ;
} ASTNode;

/*
--------------------------------------------------------------------------------
Constructor
--------------------------------------------------------------------------------
*/

/* ASTNode *ASTNode_new(int type, int value,  */
/* 		     ASTNode *l_succ, ASTNode *r_succ); */

#define ASTNODE_NEW(a,t,i,l,r)	  \
{                                 \
 a=NULL;                          \
 MY_MALLOC(a,sizeof(ASTNode));	  \
 a->type = t;			  \
 a->id = i;			  \
 a->r_succ = r;			  \
 a->l_succ = l;			  \
 }

/*
--------------------------------------------------------------------------------
Macros para crear los distintos tipos de nodos
--------------------------------------------------------------------------------
*/
#define ASTNODE_LEAF(a,type,value) ASTNODE_NEW(a,type,value, NULL, NULL);
#define ASTNODE_OR(a,l,r) ASTNODE_NEW(a,OR,0, l, r);
#define ASTNODE_AND(a,l,r) ASTNODE_NEW(a,AND,0, l, r);
#define ASTNODE_IMPL(a,l,r) ASTNODE_NEW(a,IMPL,0, l, r);
#define ASTNODE_IFF(a,l,r) ASTNODE_NEW(a,IFF,0, l, r);
#define ASTNODE_NOT(a,l) ASTNODE_NEW(a,NOT,0, l, NULL);
#define ASTNODE_PROP(a,i) ASTNODE_NEW(a,PROP,i, NULL, NULL);
#define ASTNODE_TRUE(a) ASTNODE_NEW(a,TRUE,1, NULL, NULL);
#define ASTNODE_FALSE(a) ASTNODE_NEW(a,FALSE,0, NULL, NULL);
#define ASTNODE_UNKNW(a) ASTNODE_NEW(a,UNKNW,0, NULL, NULL);


/*
--------------------------------------------------------------------------------
Destructor
--------------------------------------------------------------------------------
*/

/* void ASTNode_free(ASTNode *node); */

#define ASTNODE_FREE(n)          \
{                                \
  if( n->l_succ != NULL)         \
    ASTNODE_FREE(node->l_succ);  \
  if( n->r_succ != NULL)         \
    ASTNODE_FREE(n->r_succ);     \
  free(node);                    \
}

/*
--------------------------------------------------------------------------------
funciones utiles.
--------------------------------------------------------------------------------
*/

/* void ASTNode_print(ASTNode *node); */

/* void ASTNode_print(ASTNode *node) */
/* { */
/*   _ASTNode_print(node,0); */
/* } */


/* char* _build_prefix(int level) */
/* { */
/*   char c = '-'; */
/*   char *pr; */
/*   size_t l = sizeof(c)*level; */
/*   pr = malloc(l+1); */
/*   if (level > 0) */
/*       memset(pr,'-',l); */
/*   pr[l]='\0'; */
/*   return pr; */
/* } */

/* void ASTNode_print(ASTNode *node, int level) */
/* { */
/*   char *pr = _build_prefix(level); */
/*   printf("%s Node Type: %d\n", pr, node->type); */
/*   printf("%s Node Value: %d\n", pr, node->id); */
/*   free(pr); */
/*   if( node->l_succ != NULL) */
/*     ASTNode_print(node->l_succ,(level+1)); */
/*   if( node->r_succ != NULL) */
/*     ASTNode_print(node->r_succ,(level+1));   */
/* } */

/* #define ASTNODE_PRINT(n) ASTnode_print(n,0); */

#endif
