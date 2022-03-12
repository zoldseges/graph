#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "model.h"

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

void negint_error(int num, char *filename, int linenum, const char *func)
{
  if(num < 0){
    fprintf(stderr, "%s:", filename);
    fprintf(stderr, "%d:", linenum);
    fprintf(stderr, "%d: ", 0);
    fprintf(stderr, "NEG exception in `%s`\n", func);
    exit(1);
  }
}

void print_node(Node *n, UNUSED gpointer d)
{
  printf("ID: %3d x: %f y: %f\n", n->id, n->x, n->y);
}

void print_graph(Graph *g, char *filename, int linenum, const char *func)
{
  printf("print_graph called on ");
  printf("%s:", filename);
  printf("%d:", linenum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);
  printf("Graph:\n");
  nodes_call(print_node, g, 0);
  printf("-----------------------------\n");
}

void print_pos(gdouble x,
	       gdouble y,
	       char *filename,
	       int linenum,
	       const char *func)
{
  printf("print_pos called on ");
  printf("%s:", filename);
  printf("%d:", linenum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);
  printf("mouse pos: x: %f y: %f\n", x, y);
  printf("-----------------------------\n");
}


void print_hovered(Ctl *ctl,
		   char *filename,
		   int linenum,
		   const char *func)
{
  printf("print_hovered called on ");
  printf("%s:", filename);
  printf("%d:", linenum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);
  printf("hovered: [%d, %d]\n", ctl->hovered[0], ctl->hovered[1]);
  printf("-----------------------------\n");
}

void print_selected(Ctl *ctl,
		    char *filename,
		    int linenum,
		    const char *func)
{
  printf("print_selected called on ");
  printf("%s:", filename);
  printf("%d:", linenum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);
  printf("selected: [%d, %d]\n", ctl->selected[0], ctl->selected[1]);
  printf("-----------------------------\n");
}
