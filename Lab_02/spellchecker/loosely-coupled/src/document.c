#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "document.h"

struct _doc_t {
    FILE *doc_in;
    FILE *doc_out;
};

int doc_get_word(Document doc, char *word) {
    FILE* file = doc->doc_in;
    char c = fgetc(file);
    char *word_copy;
    int i = 0;
    fpos_t pos;
    word_copy = calloc(30, sizeof(char));
    strcpy(word_copy, word);
    printf("entre al get word con %s\n", word);
    // printf("el archivo termino? %i\n", feof(file));
    // if (!feof(file)) {
        while (c != EOF && !isalpha(c)) {
            printf("char es %c\n", c);
            fputc(c, doc->doc_out);
            c = fgetc(file);
        }

        while (c != EOF && isalpha(c)) {
            printf("char B es %c\n", c);
            fgetpos(file, &pos);
            word[i] = c;
            i++;
            word[i] = '\0';
            c = fgetc(file);
        }

        if (c == EOF && strcmp(word,word_copy) != 0) {
            return 1;
        }
        else if (c == EOF) {
            return 0;
        }
        else {
            fsetpos(file, &pos);
            return 1;
        }
    // }
    // else {
    //     return 0;
    // }
}

void doc_put_word(Document doc, char *word) {
    //printf("voy a putear %s\n", word);
    fprintf(doc->doc_out, "%s", word);
    //printf("Sali de put\n");
}


FILE* doc_open(Document doc, char* fname) {
    doc->doc_in = fopen(fname, "r");
    doc->doc_out = fopen("out.txt", "w+");
    //printf("sali del open\n");
    return doc->doc_in;
}

void doc_close(Document doc) {
    fclose(doc->doc_in);
    fclose(doc->doc_out);
    free(doc);
}
