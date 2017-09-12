#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "document.h"


struct _doct_t {
	FILE *doc_in;
	FILE *doc_out;
};

int doc_get_word(Document doc, char *word){
  char c = NULL;
  int i = 0;


  while(!feof(doc->doc_in)){
    c = fgetc(doc->doc_in);

    while(!isalnum(c)){
      fputc(c,doc->doc_out);
      c = fgetc(doc->doc_in);
      if(feof(doc->doc_in)){
        return 0;
      }
    }

    while(isalnum(c)){
      word[i] = c;
      c = fgetc(doc->doc_in);
      i = i+1;
    }
    if(c == EOF){
      return 1;
    }
    word[i] = '\0';
    fseek(doc->doc_in, -1, SEEK_CUR);
    return 1;
  }
  return 0;
}

void doc_put_word(Document doc, char *word){

  fprintf(doc->doc_out, "%s", word);
}

Document doc_open(char *fname){
  Document doc = NULL;

  doc = calloc(1, sizeof(struct _doct_t));
  doc->doc_in = fopen(fname, "r");
	doc->doc_out = fopen("out.txt", "w+");

  return doc;
}

void doc_close(Document doc){
	fclose(doc->doc_in);
	fclose(doc->doc_out);
  free(doc);
  doc = NULL;
}