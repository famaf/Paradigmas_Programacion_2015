#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct _dict_t *Dictionary;

Dictionary dict_new(void);

void dict_load(char *fname, Dictionary dict, int size);
/*
CARGA EL DICICONARIO EN MEMORIA
*/

void dict_save(char *fname, Dictionary dict);
/*
GUARDA EL DICCIONARIOR
*/

void dict_add(char *word, Dictionary dict);
/*
AGREGA PALABRA AL DICCIONARIO PRINCIPAL
*/

int dict_contains(char *word, Dictionary dict);

void dict_destroy(Dictionary dict);

#endif