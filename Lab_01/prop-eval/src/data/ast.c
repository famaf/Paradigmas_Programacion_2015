#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "misc.h"

ASTNode *ASTNode_new(int type, int value, ASTNode *l_succ, ASTNode *r_succ)
{
  ASTNode *a;
  MY_MALLOC(a,sizeof(ASTNode));
  a->type = type;
  a->value = value;
  a->r_succ = r_succ;
  a->l_succ = l_succ;
  return a;
}

/* ASTNode *ASTNode_new_leaf(int type, int value) */
/* { */
/*   return ASTNode_new(type,value, NULL, NULL); */
/* } */

char* _build_prefix(int level)
{
  char c = '-';
  char *pr;
  size_t l = sizeof(c)*level;
  pr = malloc(l+1);
  if (level > 0)
      memset(pr,'-',l);
  pr[l]='\0';
  return pr;
}

void _ASTNode_print(ASTNode *node, int level)
{
  char *pr = _build_prefix(level);
  printf("%s Node Type: %d\n", pr, node->type);
  printf("%s Node Value: %d\n", pr, node->value);
  free(pr);
  if( node->l_succ != NULL)
    _ASTNode_print(node->l_succ,(level+1));
  if( node->r_succ != NULL)
    _ASTNode_print(node->r_succ,(level+1));  
}


void ASTNode_print(ASTNode *node)
{
  _ASTNode_print(node,0);
}

void ASTNode_free(ASTNode *node)
{
  if( node->l_succ != NULL)
    ASTNode_free(node->l_succ);
  if( node->r_succ != NULL)
    ASTNode_free(node->r_succ);
  #ifdef DEBUG
  printf("freeing node: %d\n", node->value);
  #endif
  free(node);
}



/* void main(int argc, char **argv) */
/* { */
/*   ASTNode *n1=ASTNode_new_leaf(1,1); */
/*   ASTNode *n2=ASTNode_new_leaf(2,2); */
/*   ASTNode *n6=ASTNode_new_leaf(6,6); */
/*   ASTNode *n7=ASTNode_new_leaf(7,7); */
/*   ASTNode *n4=ASTNode_new(4,4, n6, n7); */
/*   ASTNode *n5=ASTNode_new(5,5, n1, n2); */
/* //  ASTNode_print(n1); */
/* //  ASTNode_print(n2); */
  
/*   ASTNode *n3=ASTNode_new(3,3,n4,n5); */
/*   ASTNode_print(n3);   */
/*   ASTNode_free(n3); */
/*   /\* char *v1="P13"; *\/ */
/*   /\* char *v2="RW12"; *\/ */
/*   /\* int v3=get_val(v1,1); *\/ */
/*   /\* int v4=get_val(v2,2); *\/ */
/*   /\* printf("val 1:%d", v3); *\/ */
/*   /\* printf("val 2:%d", v4); *\/ */
/* } */



