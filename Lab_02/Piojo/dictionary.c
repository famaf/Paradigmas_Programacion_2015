#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define MAX_WORD_SIZE 30

struct _dict_t {
	char **dict_main;
	int dict_size;
};


void dict_load(Dictionary dict, char *fname){

  FILE *load = NULL;
  int i =0;
  int tmp = 0;
  load = fopen(fname, "r+");

  if(load == NULL)
  {
    printf("el diccionario no se pudo cargar\n");
    exit(1);
  } 
  else
  {
    while(!feof(load))
    {
        if(i < dict->dict_size)
        {
          dict->dict_main[i] = malloc(MAX_WORD_SIZE * sizeof(char*));
          fgets(dict->dict_main[i], MAX_WORD_SIZE, load);
          printf("%s\n", dict->dict_main[i]);
          strtok(dict->dict_main[i], "\n");
          i = i + 1;
        }
        dict->dict_size = dict->dict_size + 1;
    }
  }
  dict->dict_size = i;
  fclose(load);
}


void dict_save(Dictionary dict, char *fname){

  FILE *to_save;
  int i = 0;
  int tmp = 0;

  to_save = fopen(fname, "w+");

  if (to_save == NULL)
  {
    printf("no se pudo crear el archivo de salida\n");
    exit(1);
  }
  else
{
    while(dict->dict_main[i] != NULL)
    {
      tmp = strlen(dict->dict_main[i]);
      dict->dict_main[i][tmp] = '\n';
      
      if(i + 1 == dict->dict_size)
      {
        dict->dict_main[i][tmp] = '\0';
      }
      fputs(dict->dict_main[i] ,to_save);
      free(dict->dict_main[i]);
      i = i + 1;
    }
  }

  fclose(to_save);
}

void dict_add(Dictionary dict, char *word){

  dict->dict_main[dict->dict_size] = calloc(MAX_WORD_SIZE, sizeof(char));
  strcpy(dict->dict_main[dict->dict_size], word);
  dict->dict_size = dict->dict_size + 1;
}

bool dict_contains(Dictionary dict, char *word){

  int i = 0;
  
  while(dict->dict_main[i] != NULL)
  {
    if(strcmp(dict->dict_main[i], word) == 0)
    {
      return 1;
    }else{
      i = i + 1;
    }
  }
  return 0;
}

Dictionary dict_new(void){
	Dictionary dict = NULL;

	dict = calloc(1, sizeof(struct _dict_t));
	dict->dict_main = calloc(1, sizeof(char*)*1024);
	dict->dict_size = 0;

return dict;
}

void dict_destroy(Dictionary dict, bool b){
  int i = 0;

  if(b){
    while(dict->dict_main[i] != NULL){
      free(dict->dict_main[i]);
      i = i + 1;
    }
    free(dict->dict_main);
    free(dict);
  }else{
  	free(dict->dict_main);
    free(dict);
  }
}
