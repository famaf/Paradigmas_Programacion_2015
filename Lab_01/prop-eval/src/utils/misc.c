#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "misc.h"

int SILENT = 0;

void log_error(char *format, ...)
{
  va_list params;
  va_start(params,format);
  fprintf(stderr, "error: ");
  vfprintf(stderr, format, params);
  va_end(params);
  exit(1);
}

void log_warning(char *format, ...)
{
  va_list params;
  va_start(params,format);
  fprintf(stderr, "warning: ");
  vfprintf(stderr, format, params);
  va_end(params);
}

void log_message(char *format, ...)
{
  va_list params;
  if (SILENT)
    return;
  va_start(params,format);
  fprintf(stderr, "message: ");
  vfprintf(stderr, format, params);
  va_end(params);
}

int get_val(char *str, int pref_size, int suf_size)
{
  char *str_val;
  int i_len = strlen(str);
  int o_len = i_len - pref_size - suf_size;
  MY_MALLOC(str_val,sizeof(char)*o_len);
  strncpy (str_val, str + pref_size, o_len);
  int val = atoi(str_val);
  free(str_val);
  return val;
}
