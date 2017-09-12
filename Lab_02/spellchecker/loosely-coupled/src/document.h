#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "document.h"

typedef struct _doc_t *Document;

int doc_get_word(Document doc, char *word);

void doc_put_word(Document doc, char *word);

FILE* doc_open(Document doc, char* fname);

void doc_close(Document doc);

#endif