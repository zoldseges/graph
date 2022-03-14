#include <stdio.h>
#include <limits.h>

#include "debug.h"
#include "model.h"
#include "controller.h"

void null_error(void *p, char *fname, int linum, const char *func)
{
  if(p == NULL){
    fprintf(stderr, "%s:", fname);
    fprintf(stderr, "%d:", linum);
    fprintf(stderr, "%d: ", 0);
    fprintf(stderr, "`%s`:\n", func);
    fprintf(stderr, "NULL exception\n");
    exit(1);
  }
}

void zero_error(int num, char *fname, int linum, const char *func)
{
  if(!num){
    fprintf(stderr, "%s:", fname);
    fprintf(stderr, "%d:", linum);
    fprintf(stderr, "%d: ", 0);
    fprintf(stderr,"`%s`:\n", func);
    fprintf(stderr, "0 exception\n");
    exit(1);
  }
}

void negint_error(int num, char *fname, int linum, const char *func)
{
  if(num < 0){
    fprintf(stderr, "%s:", fname);
    fprintf(stderr, "%d:", linum);
    fprintf(stderr, "%d: ", 0);
    fprintf(stderr,"`%s`:\n", func);
    fprintf(stderr, "NEG exception\n");
    exit(1);
  }
}

void unreachable_error(int n, char *fname, int linum, const char *func)
{
  fprintf(stderr, "%s:", fname);
  fprintf(stderr, "%d:", linum);
  fprintf(stderr, "%d: ", 0);
  fprintf(stderr,"`%s`:\n", func);
  fprintf(stderr, "UNREACHABLE case \"%d\"\n", n);
  exit(1);
}

void print_node(Node *n, UNUSED gpointer d)
{
  printf("ID: %3d x: %f y: %f\n", n->id, n->p.x, n->p.y);
}

void print_graph(Graph *g, char *fname, int linum, const char *func)
{
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("print graph called\n");
  printf("Graph:\n");
  nodes_call(print_node, g, 0);
  printf("-----------------------------\n");
}

void print_pos(Point p, char *fname, int linum, const char *func)
{
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("print pos called\n");
  printf("mouse pos: x: %f y: %f\n", p.x, p.y);
  printf("-----------------------------\n");
}


void print_mode(Ctl *ctl, char *fname, int linum, const char *func)
{
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("print_mode called\n");
  printf("MODE: ");
  switch (ctl->mode) {
  case ADD_NODE:
    printf("ADD_NODE");
    break;
  case MOVE_NODE:
    printf("MOVE_NODE");
    break;
  case START_EDGE:
    printf("START_EDGE");
    break;
  case END_EDGE:
    printf("END_EDGE");
    break;
  case SELECT:
    printf("SELECT");
    break;
  case DELETE:
    printf("DELETE");
    break;
  default:
    UNREACHABLE(ctl->mode);
    break;
  }
  printf("\n");
  printf("-----------------------------\n");
}
void print_event(Ctl *ctl, char *fname, int linum, const char *func)
{
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("print_mode called\n");
  printf("EVENT: ");
  switch (ctl->event) {
  case MOTION:
    printf("MOTION");
    break;
  case L_CLICK:
    printf("L_CLICK");
    break;
  case M_CLICK:
    printf("M_CLICK");
    break;
  case R_CLICK:
    printf("R_CLICK");
    break;
  case SCROLL_UP:
    printf("SCROLL_UP");
    break;
  case SCROLL_DOWN:
    printf("SCROLL_DOWN");
    break;
  case L_DRAG_BEGIN:
    printf("L_DRAG_BEGIN");
    break;
  case R_DRAG_BEGIN:
    printf("R_DRAG_BEGIN");
    break;
  case L_DRAG_UPDATE:
    printf("L_DRAG_UPDATE");
    break;
  case R_DRAG_UPDATE:
    printf("R_DRAG_UPDATE");
    break;
  case L_DRAG_END:
    printf("L_DRAG_END");
    break;
  case R_DRAG_END:
    printf("R_DRAG_END");
    break;
  case DESTROY:
    printf("DESTROY");
    break;
  case RESIZE:
    printf("RESIZE");
    break;
  default:
    UNREACHABLE(ctl->event);
    break;
  }
  printf("\n");
  printf("-----------------------------\n");
}

void print_hovered(Ctl *ctl, char *fname, int linum, const char *func)
{
  Marked *curr = ctl->hovered;

  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("print_hovered called\n");

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

  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("print_selected called\n");

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

void print_matrix(Matrix m, char *fname, int linum, const char *func)
{
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("print_matrix called\n");
  printf("Matrix:\n");
  printf("+");
  for(int i = 0; i < m.row_sz; i++) {
    printf("----");
  }
  printf("+\n");
  for(int i = 0; i < m.row_sz; i++) {
    printf("|");
    for(int j = 0; j < m.row_sz; j++) {
      int val = *(m.pm + (m.row_sz * i) + j);
      if(val == INT_MAX){
	printf("INF ");
      } else {
	printf("%3d ", val);
      }
    }
    printf("|\n");
  }
  printf("+");
  for(int i = 0; i < m.row_sz; i++) {
    printf("----");
  }
  printf("+");
  printf("\n");
}

void cls(char *fname, int linum, const char *func)
{
  printf("\033[2J\033[H");
  printf("%s:", fname);
  printf("%d:", linum);
  printf("%d: ", 0);
  printf("`%s`:\n", func);
  printf("clear screen called\n");
  printf("-----------------------------\n");
}
