#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "dictionary.h"
#include "document.h"

struct _dict_t {
    char **dict;
    int dict_size;
};


Dictionary dict_new(void) {
    Dictionary dict = NULL;
    dict = calloc(1, sizeof(struct _dict_t));
    dict->dict = calloc(1000, sizeof(char*));
    dict->dict_size = 0;
    return (dict);
}

void dict_load(char *fname, Dictionary dict, int size) {
    FILE *fd = NULL;
    int i = 0;
    int tmp = 0;

    fd = fopen(fname, "r+");

    if (fd == NULL) {
        printf("No se puede cargar el archivo %s\n", fname);
        exit(1);
    }
    else {
        while (!feof(fd)) {
            dict->dict[i] = calloc(size, sizeof(char));
            fgets(dict->dict[i], size, fd);
            strtok(dict->dict[i], "\n");
            // printf("dict %i es %s\n", i, dict->dict[i]);
            i++;
            dict->dict_size++;
        }
    }
    // printf("size es %d\n", dict->dict_size);
    fclose(fd);
}


void dict_save(char *fname, Dictionary dict) {
    FILE *fd = NULL;
    fd = fopen(fname, "w+");

    int i = 0;
    for (i; i < (dict->dict_size - 1); i++) {
        fprintf(fd, "%s\n", dict->dict[i]);
    }
    fprintf(fd, "%s", dict->dict[dict->dict_size - 1]);

    fclose(fd);
}


void dict_add(char *word, Dictionary dict) {
    // printf("el size en add es %d\n", dict->dict_size);
    dict->dict[dict->dict_size] = calloc(30, sizeof(char));
    // printf("entro add word es %s\n",word);
    strcpy(dict->dict[dict->dict_size], word);
    // printf("copie add\n");
    // printf("dict[%d] es %s\n", dict->dict_size, dict->dict[dict->dict_size]);
    dict->dict_size += 1;
    // printf("el size en add salida es %d\n", dict->dict_size);
}


int dict_contains(char *word, Dictionary dict) {
    int i = 0;
    int result = 0;

    // printf("el size en contains is %d\n",dict->dict_size);

    while (i < dict->dict_size && !result) {
        result = (strcmp(dict->dict[i], word) == 0);
        printf("comparo word %s con dict % i (%s)\n" , word, i, dict->dict[i]);
        i++;
    }

    // if (result != 0) {
    //     result = 0;
    // }
    // else {
    //     result = 1;
    // }

    return result;
}


void dict_destroy(Dictionary dict) {
    int i = 0;

    while(dict->dict[i] != NULL && i < dict->dict_size) {
        free(dict->dict[i]);
        i++;
    }

    free(dict);
}
