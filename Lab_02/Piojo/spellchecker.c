#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "dictionary.h"
#include "document.h"

/* tamaño maximo de una palabra */
#define MAX_WORD_SIZE 30

/* diccionario principal */
Dictionary main_dict;
/* diccionario de palabras ignoradas */
Dictionary ignored;
/* Documento a procesar */
Document doc;


/*******************************************************************
* NAME :            int is_known(char *word)
*
* DESCRIPTION :     Verifica si una palabra es "conocida", ya sea 
*                   porque esta en el diccionario principal o en el 
*                   diccionario de palabras ignoradas. 
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a verificar.
*
* RETURN :
*           Type: int
*           Values: 1 si la palabra es conocida
*                   0 si la palabra no es conocida
*******************************************************************/
int is_known(char *word)
{
  
  if(dict_contains(main_dict, word))
  {
    return 1;
  }
  
  if(dict_contains(ignored, word))
  {
    return 1;
  }

  return 0;
}

/*******************************************************************
* NAME :            void consult_user(char *word)
*
* DESCRIPTION :     Consulta al usuario sobre que accion realizar 
*                   (aceptar, ignorar o reemplazar) con la palabra w.
*                   Una vez que el usuario elige, realiza la accion 
*                   elegida.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra sobre la cual se consulta la 
*                            accion a realizar.
*
* RETURN :
*           Type: void
*******************************************************************/
void consult_user(char *word)
{
  char ans[2];
  char ans_user[MAX_WORD_SIZE];

  do{
    printf("Palabra no reconocida: %s\n Aceptar (a) - Ignorar (i) - Reemplazar (r): ", word);
    scanf("%s", ans);
  }while((strcmp(ans,"r") != 0) && (strcmp(ans,"a") != 0) && (strcmp(ans,"i") != 0));

  if(strcmp(ans, "r") == 0)
  {
    printf("escriba la palabra por la que quiere reemplazar la palabra %s: ", word);
    scanf("%s", ans_user);
    printf("la palabra ans_user es: %s\n", ans_user);
    strcpy(word, ans_user);
  }
  else if(strcmp(ans, "i") == 0)
  {
    dict_add(ignored, word);
  }
  else if(strcmp(ans, "a") == 0)
  {
    dict_add(main_dict, word);
  }

}

/*******************************************************************
* NAME :            void process_document(char *fname)
*
* DESCRIPTION :     Procesa el documento fname, palabra por palabra, 
*                   consultando al usuario sobre la accion a realizar 
*                   si la palabra no es conocida.
* PARAMETERS:
*      INPUT:
*           char    *fname   Nombre del archivo a procesar.
*
* RETURN :
*           Type: void
*******************************************************************/
void process_document(char *fname)
{
  char current_word[MAX_WORD_SIZE];

  doc = doc_open(fname);

    while(doc_get_word(doc, current_word) == 1)
    {
      printf("CURRENT WORD es %s\n", current_word);
      if(!is_known(current_word))
      {
        consult_user(current_word);
        doc_put_word(doc, current_word);
      }
      else
      {
        doc_put_word(doc, current_word);
      }
    }
  
  doc_close(doc);
}

/*******************************************************************
* NAME :            int main(int argc, char **argv)
*
* DESCRIPTION :     Punto de entrada principal. Abre el diccionario 
*                   principal, procesa el archivo especificado y 
*                   guarda los cambios realizados en el diccionario 
*                   principal.
*******************************************************************/
int main(int argc, char **argv)
{
  char *dict;

  main_dict = dict_new();
  ignored = dict_new();  

  /* Verificamos el nro de argumentos. */
  if (argc < 2)
   {
     printf("spellchecker.c: nro de argumentos erroneo. Deben ser <documento> [<diccionario>].\n");
     return (1);
   }
  /* si se especifico un diccionario lo usamos,  */
  /* caso contrario usamos el diccionario por defecto */
  dict = (argc >=3) ? argv[2] : "dict.txt";

  dict_load(main_dict, argv[2]);
  process_document(argv[1]);
  dict_save(main_dict, argv[2]);
  dict_destroy(main_dict, false);
  dict_destroy(ignored, true);

  printf("El documento %s ha sido procesado. Resultados en out.txt\n", argv[1]);
}