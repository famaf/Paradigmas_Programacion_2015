#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//tamaño maximo de una palabra
#define MAX_WORD_SIZE 30

/* diccionario principal */
char **dict_main = NULL;
/*tamaño inicial del diccionario principal*/
int main_size = 0;

/* diccionario de palabras ignoradas */
char **dict_ignored;
/*tamaño inicial del diccionario de palabras ignoradas*/
int ignored_size = 0;

/* Documento de entrada */
FILE *doc_in = NULL;
/* Documento de salida */
FILE *doc_out = NULL;

/*******************************************************************
* NAME :            void dict_load(char *fname)
*
* DESCRIPTION :     Carga en memoria el diccionario principal desde 
*                   el archivo fname
*
* PARAMETERS:
*      INPUT:
*           char    *fname       Nombre del archivo que contiene el 
*                                diccionario
* RETURN :
*           Type: void
*
* OBSERVATIONS :
*    1) El tamaño de la lista que contiene representa al diccionario 
*       debe coincidir con el nro de palabras en el diccionario. 
*       Esto implica que si es necesario hay que "agrandar" la lista, 
*       y si sobra espacio en la lista hay que "achicarla".
*    2) Recordar borrar el \n y \r al final de cada palabra y que los 
*       strings en C terminan en \0.
*******************************************************************/
void dict_load(char *fname) {
    FILE *fd = NULL;
    int i = 0;
    int tmp = 0;

    fd = fopen(fname, "r+");

    if (fd == NULL) {
        printf("No se puede cargar el archivo %s\n", fname);
        exit(1);
    }
    else {
        printf("Diccionario cargado con exito\n");
        dict_main = calloc(1000, sizeof(char*));
        dict_ignored = calloc(1000, sizeof(char*));

        while (!feof(fd)) {
            dict_main[i] = calloc(MAX_WORD_SIZE, sizeof(char));
            fgets(dict_main[i], MAX_WORD_SIZE, fd);
            strtok(dict_main[i], "\n");
            i++;
            main_size ++;
        }
    }

    fclose(fd);
}

/*******************************************************************
* NAME :            void dict_save(char *fname)
*
* DESCRIPTION :     Guarda el diccionario principal en el archivo 
*                   fname
*
* PARAMETERS:
*      INPUT:
*           char    *fname       Nombre del archivo donde se guardara
*                                el diccionario
* RETURN :
*           Type: void
*******************************************************************/
void dict_save(char *fname) {
    FILE *fd = NULL;
    fd = fopen(fname, "w+");
    int i = 0;

    // Paso las nuevas palabras al diccionario
    for (i; i < (main_size - 1); i++) {
        fprintf(fd, "%s\n", dict_main[i]);
    }
    fprintf(fd, "%s", dict_main[main_size - 1]);

    // Libero memoria de cada celda del dict_main
    i = 0;
    for (i; i < main_size; i++) {
        free(dict_main[i]);
    }

    free(dict_main); // Libero estructura dict_main

    // Libero memoria de cada celda del ignored_main
    i = 0;
    for (i; i < ignored_size; i++) {
        free(dict_ignored[i]);
    }

    free(dict_ignored); // Libero estructura dict_ignored

    fclose(fd);
}

/*******************************************************************
* NAME :            void dict_add(char *word)
*
* DESCRIPTION :     Agrega una palabra al diccionario principal.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a ser agregada.
*
* RETURN :
*           Type: void
*
* OBSERVATIONS :
*    1) Recordar que la lista que representa el diccionario no tiene 
*       lugar "de sobra".
*******************************************************************/
void dict_add(char *word) {
    dict_main[main_size] = realloc(dict_main[main_size], MAX_WORD_SIZE * sizeof(char));
    strcpy(dict_main[main_size], word);
    main_size += 1;
}

/*******************************************************************
* NAME :            void ignored_add(char *word)
*
* DESCRIPTION :     Agrega una palabra al diccionario de palabras 
*                   ignoradas.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a ser agregada.

* RETURN :
*           Type: void
* OBSERVATIONS :
*    1) La lista que representa el diccionario de palabras ignoradas 
*       debe agrandarse a medida que se agregan palabras.
*******************************************************************/
void ignored_add(char *word) {
    dict_ignored[ignored_size] = realloc(dict_ignored[ignored_size] ,MAX_WORD_SIZE * sizeof(char));
    strcpy(dict_ignored[ignored_size],word);
    ignored_size += 1;
}

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
    int i = 0;
    for (i; i < main_size; i++) {
        if (strcmp(dict_main[i], word) == 0) {
            return 1;
        }
    }

    i = 0;
    for (i; i < ignored_size; i++) {
        if (strcmp(dict_ignored[i], word) == 0) {
            return 1;
        }
    }

    return 0;
}


/*******************************************************************
* NAME :            int get_word(char *w)
*
* DESCRIPTION :     Lee una palabra del archivo de entrada, copiando 
*                   todo caracter de puntuacion precedente al archivo
*                   de salida.
* PARAMETERS:
*      OUTPUT:
*           char    *word       Palabra que se lee desde el archivo.
*
* RETURN :
*           Type: int
*           Values: 0 si no hay mas palabras para leer.  
*                   1 si hay mas palabras para leer.
*******************************************************************/
int get_word(char *word) {
    int i = 0;
    fpos_t pos;
    char c = fgetc(doc_in);
    char word_copy[MAX_WORD_SIZE];
    // char *word_copy = NULL;
    // word_copy = calloc(MAX_WORD_SIZE, sizeof(char));
    strcpy(word_copy, word);

    while (c != EOF && !isalpha(c)) {
        fputc(c, doc_out);
        c = fgetc(doc_in);
    }

    while (c != EOF && isalpha(c)) {
        fgetpos(doc_in, &pos);
        word[i] = c;
        i++;
        c = fgetc(doc_in);
        word[i] = '\0';
    }

    if (c == EOF && strcmp(word,word_copy) != 0) {
        // free(word_copy);
        return 1;
    }
    else if (c == EOF) {
        // free(word_copy);
        return 0;
    }
    else {
        fsetpos(doc_in, &pos);
        // free(word_copy);
        return 1;
    }

}

/*******************************************************************
* NAME :            void put_word(char *word)
*
* DESCRIPTION :     Escribe la palabra w al archivo de salida.
*
* PARAMETERS:
*      INPUT:
*           char    *word       Palabra a escribir.
*
* RETURN :
*           Type: void
*******************************************************************/
void put_word(char *word) {
    fprintf(doc_out, "%s", word);
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
            dict_add(word);
            break;
        case 'i':
            ignored_add(word);
            break;
        case 'r':
            printf("Ingrese la palabra por la cual quiere reemplazar '%s': ", word);
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

   doc_in = fopen(fname, "r");
   doc_out = fopen("out.txt", "w+");

    // get_word(current_word);
    while (feof(doc_in) == 0) {
        if (get_word(current_word) == 1) {
            if (!is_known(current_word)) {
                consult_user(current_word);
            }
            put_word(current_word);
            current_word[0] = '1';
        }
    }
    fclose(doc_in);
    fclose(doc_out);
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
    char *dict = NULL;
    char *fd = NULL;
    /* Verificamos el nro de argumentos. */
    if (argc < 2) {
        printf("spellchecker.c: nro de argumentos erroneo. Deben ser <documento> [<diccionario>].\n");
        return (1);
    }
    /* si se especifico un diccionario lo usamos,  */
    /* caso contrario usamos el diccionario por defecto */
    dict = (argc >=3) ? argv[2] : "dict.txt";

    dict_load(dict);
    fd = argv[1];
    process_document(fd);
    dict_save(dict);

    printf("El documento %s ha sido procesado. Resultados en out.txt\n\n", argv[1]);
}
