#include <stdio.h>
#include <stdlib.h>

void null_error(void *p, char *filename, int linenum, const char *func)
{
  if(p == NULL){
      fprintf(stderr, "%s:", filename);
      fprintf(stderr, "%d:", linenum);
      fprintf(stderr, "%d: ", 0);
      fprintf(stderr, "NULL exception in `%s`\n", func);
      exit(1);
  }
}

void zero_error(int num, char *filename, int linenum, const char *func)
{
  if(!num){
      fprintf(stderr, "%s:", filename);
      fprintf(stderr, "%d:", linenum);
      fprintf(stderr, "%d: ", 0);
      fprintf(stderr, "NULL exception in `%s`\n", func);
      exit(1);
  }
}
