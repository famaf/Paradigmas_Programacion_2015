#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "misc.h"
#include "uthash.h"


/*
--------------------------------------------------------------------------------
Estructura de datos que define una asignacion para una variable proposicional
--------------------------------------------------------------------------------
*/

typedef struct Asgmnt 
{
  /* variable proposicional */
  int prop_id;
  /* valor de verdad*/
  int value;
  /* indica que la estructura es hashable */
  UT_hash_handle hh; 
} Asgmnt;


/*
--------------------------------------------------------------------------------
Macros para operar (agregar, buscar, etc) con una lista de asignaciones.
--------------------------------------------------------------------------------
*/


/* 
--------------------------------------------------------------------------------
Agrega una asignacion a la lista de asignaciones. Si ya existe una asignacion
para la variable, la reemplaza.
 - (*Asgmnt) asgmn_list: lista de assignaciones 
 - (int)prop_id: variable propocional para la cual estamos asignando el valor. 
 - (int)value: valor de la variable proposicional.  
 - Retorna: void
--------------------------------------------------------------------------------
*/
#define ASSIGNMENT_ADD(asgnmt_list,i,v)         \
 {                                              \
  Asgmnt *a,*b;				        \
  MY_MALLOC(a,sizeof(Asgmnt));                  \
  a->prop_id = i;                               \
  a->value = v;                                 \
  HASH_REPLACE_INT(asgnmt_list, prop_id, a, b);	\
 }                                                 

/* 
--------------------------------------------------------------------------------
Busca la asignacion para una variable proposicional en la lista de asignaciones. 
 - (*Asgmnt) asgmn_list: lista de assignaciones 
 - (*int)prop_id: variable propocional para la cual estamos buscando el valor. 
 - (*Asgmnt): puntero a la estructura donde se devuelve el resultado.
 - Retorna: estructura Asgmnt
--------------------------------------------------------------------------------
*/
#define ASSIGNMENT_FIND(asgnmt_list,i,a) HASH_FIND_INT(asgnmt_list, i, a);

/* 
--------------------------------------------------------------------------------
Imprime en pantalla el contenido de la asignacion.
 - (*Asgmnt) asgmn_list: lista de assignaciones 
 - Retorna: void
--------------------------------------------------------------------------------
*/
#define ASSIGNMENT_PRINT(asgmnt_list)                           \
{                                                               \
  Asgmnt *s;						        \
  for(s=asgmnt_list; s != NULL; s=s->hh.next) {                 \
    printf("P%d:%s(%d),", s->prop_id, (s->value==1?"True":"False"),s->value);	\
  }                                                             \
  printf("\n");                                                 \
}

#endif

