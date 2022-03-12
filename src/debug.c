#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "model.h"
#include "controller.h"

void null_error(void *p, char *fname, int linum, const char *func)
{
  if(p == NULL){
    fprintf(stderr, "%s:", fname);
    fprintf(stderr, "%d:", linum);
    fprintf(stderr, "%d: ", 0);
    fprintf(stderr, "NULL exception in `%s`\n", func);
    exit(1);
  }
}

void zero_error(int num, char *fname, int linum, const char *func)
{
  if(!num){
    fprintf(stderr, "%s:", fname);
    fprintf(stderr, "%d:", linum);
    fprintf(stderr, "%d: ", 0);
    fprintf(stderr, "0 exception in `%s`\n", func);
    exit(1);
  }
}

void negint_error(int num, char *fname, int linum, const char *func)
{
  if(num < 0){
    fprintf(stderr, "%s:", fname);
    fprintf(stderr, "%d:", linum);
    fprintf(stderr, "%d: ", 0);
    fprintf(stderr, "NEG exception in `%s`\n", func);
    exit(1);
  }
}

void unreachable_error(int n, char *fname, int linum, const char *func)
{
  fprintf(stderr, "%s:", fname);
  fprintf(stderr, "%d:", linum);
  fprintf(stderr, "%d: ", 0);
  fprintf(stderr, "UNREACHABLE inf `%s` case %d\n", func, n);
  exit(1);
}

void print_node(Node *n, UNUSED gpointer d)
{
  printf("ID: %3d x: %f y: %f\n", n->id, n->p.x, n->p.y);
}

void print_graph(Graph *g, char *fname, int linum, const char *func)
{
  printf("print_graph called on ");
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);
  printf("Graph:\n");
  nodes_call(print_node, g, 0);
  printf("-----------------------------\n");
}

void print_pos(Point p, char *fname, int linum, const char *func)
{
  printf("print_pos called on ");
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);
  printf("mouse pos: x: %f y: %f\n", p.x, p.y);
  printf("-----------------------------\n");
}


void print_hovered(Ctl *ctl, char *fname, int linum, const char *func)
{
  Marked *curr = ctl->hovered;

  printf("print_hovered called on ");
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);

  while(curr) {
    switch (marked_type(curr)) {
    case NONE:
      printf("NONE");
      break;
    case NODE:
      printf("%6s%6s  ", "TYPE: ", "NODE");
      printf("ID: %3d   ", curr->elem[0]->id);
      printf("x: %.2f ", curr->elem[0]->p.x);
      printf("y: %.2f ", curr->elem[0]->p.y);
      break;
    case EDGE:
      printf("%6s%6s  ", "TYPE: ", "EDGE");
      printf("%6s%3d /", "IDS: ", curr->elem[0]->id);
      printf("x: %.2f ", curr->elem[0]->p.x);
      printf("y: %.2f\n", curr->elem[0]->p.y);
      printf("%6s%3d \\", " ", curr->elem[1]->id);
      printf("x: %.2f ", curr->elem[1]->p.x);
      printf("y: %.2f\n", curr->elem[1]->p.y);
      break;
    default:
      UNREACHABLE(marked_type(curr));
      break;
    }
    printf("\n");
    curr = curr->next;
  }
  printf("-----------------------------\n");
}

void print_selected(Ctl *ctl, char *fname, int linum, const char *func)
{
  Marked *curr = ctl->selected;

  printf("print_selected called on ");
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: \n", 0);
  printf("in `%s`\n", func);

  while(curr) {
    switch (marked_type(curr)) {
    case NONE:
      printf("NONE");
      break;
    case NODE:
      printf("%6s%6s  ", "TYPE: ", "NODE");
      printf("ID: %3d   ", curr->elem[0]->id);
      printf("x: %.2f ", curr->elem[0]->p.x);
      printf("x: %.2f ", curr->elem[0]->p.y);
      break;
    case EDGE:
      printf("%6s%6s  ", "TYPE: ", "EDGE");
      printf("%6s%3d /", "IDS: ", curr->elem[0]->id);
      printf("x: %.2f ", curr->elem[0]->p.x);
      printf("y: %.2f\n", curr->elem[0]->p.y);
      printf("%6s%3d \\", " ", curr->elem[1]->id);
      printf("x: %.2f ", curr->elem[1]->p.x);
      printf("y: %.2f\n", curr->elem[1]->p.y);
      break;
    default:
      UNREACHABLE(marked_type(curr));
      break;
    }
    printf("\n");
    curr = curr->next;
  }
  printf("-----------------------------\n");
}
