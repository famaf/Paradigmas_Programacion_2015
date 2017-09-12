#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
int is_known(char *word) {
    int is_in_main = 0;
    int is_in_ignored = 0;

    is_in_main = dict_contains(word, main_dict);
    // printf("sali de contains main\n");
    is_in_ignored = dict_contains(word, ignored);

    // printf("word %s  es conocida? %d\n", word, (is_in_main || is_in_ignored));

    return (is_in_main || is_in_ignored);
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
void consult_user(char *word) {
    char ans[2];
    char ans2[MAX_WORD_SIZE];

    do {
        printf("Palabra no reconocida: %s\n Aceptar (a) - Ignorar (i) - Reemplazar (r): ", word);
        scanf("%s", ans);
    } while ((strcmp(ans,"r") != 0) && (strcmp(ans,"a") != 0) && (strcmp(ans,"i") != 0));

    switch (ans[0]) {
        case 'a':
            //printf("Size obtenido es %d\n" ,size_es(ignored));
            dict_add(word, main_dict);
            //printf("Size obtenido desp de add es %d\n" ,size_es(ignored));
            break;

        case 'i':
            //printf("Voy a llamar a add con ignored\n");
            //printf("Size obtenido es %d\n" ,size_es(ignored));
            //printf("Size obtenido del main es %d\n" ,size_es(main_dict));
            dict_add(word, ignored);
            //printf("Size obtenido deespues es  %d\n" ,size_es(ignored));
            //printf("Size obtenido despues main es %d\n" ,size_es(main_dict));
            break;

        case 'r':
            printf("Ingrese la palabra por la cual quiere reemplazar %s\n", word);
            scanf("%s", ans2);
            strcpy(word, ans2);
            break;
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
void process_document(char *fname) {
   char current_word[MAX_WORD_SIZE];

   FILE* fd = NULL;

   fd = doc_open(doc, fname);

   while (doc_get_word(doc, current_word)) {
        printf("la palabra del get es %s\n", current_word);
        if (!is_known(current_word)) {
            //printf("consulto\n");
            consult_user(current_word);
        }
        //printf("sali if voy a putear\n");
        doc_put_word(doc, current_word);
        current_word[0] = '1';
   }

   // printf("sali process\n");

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
int main(int argc, char **argv) {
    char *dict;
    char *fd;
    /* Verificamos el nro de argumentos. */
    if (argc < 2) {
        printf("spellchecker.c: nro de argumentos erroneo. Deben ser <documento> [<diccionario>].\n");
        return (1);
    }
    /* si se especifico un diccionario lo usamos,  */
    /* caso contrario usamos el diccionario por defecto */
    dict = (argc >=3) ? argv[2] : "dict.txt";

    main_dict = dict_new();
    ignored = dict_new();
    doc = calloc(1, sizeof(Document)); 

    dict_load(dict, main_dict, MAX_WORD_SIZE);

    fd = argv[1];

    process_document(fd);

    dict_save(dict, main_dict);

    dict_destroy(main_dict);
    dict_destroy(ignored);

    printf("El documento %s ha sido procesado. Resultados en out.txt\n\n", argv[1]);
}
