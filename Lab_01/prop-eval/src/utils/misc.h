#ifndef MISC_H
#define MISC_H

#include <stdlib.h>

extern int SILENT;

/*Memory allocation macros*/

/*Malloc macro borrowed from veriT source code (www.verit-solver.org)*/
#define MY_MALLOC(v,s)							\
  {									\
    v = malloc(s);							\
    if (s && !v)							\
      log_error ("malloc error on line %d in file %s\n", __LINE__, __FILE__); \
  }

/* log functions */
void log_error(char *format, ...);
void log_warning(char *format, ...);
void log_message(char *format, ...);

/* conversion functions*/

/*Macro for getting the value of a prop var from a 
  string of the form "PX" where X is a number */
#define get_prop_var(str) get_val(str,1,0)

/*Macro for getting the id of a relation from a 
  string of the form "RX" where X is a number */
#define get_rel_id(str) get_val(str,2,1)

/*Given an string str, it removes the first pref_size characters 
  from str, the last suf_size from srt, and then convert the rest to int. */
int  get_val(char *str, int pref_size, int suf_size);
#endif
