/* error checking only enabled if not optimized */
#ifndef __OPTIMIZE__
#define DEBUG
#endif

#ifndef DEBUG_H__
#define DEBUG_H__

#include "types.h"

void null_error(void *p, char *filename, int linum, const char *func);
void zero_error(int num, char *filename, int linum, const char *func);
void negint_error(int num, char *filename, int linum, const char *func);
void unreachable_error(char *filename, int linum, const char *func);

void print_graph(Graph *g, char *filename, int linum, const char *func);
void print_pos(Point p,
	       char *filename,
	       int linenum,
	       const char *func);

void print_hovered(Ctl *ctl,
		    char *filename, int linum, const char *func);

void print_selected(Ctl *ctl,
		 char *filename, int linum, const char *func);


#ifdef DEBUG
  #define UNUSED __attribute__((unused))
  #define UNIMPLEMENTED assert(0)
  #define DEBUG_NULL(p) null_error(p, __FILE__, __LINE__, __func__)
  #define DEBUG_ZERO(n) zero_error(n, __FILE__, __LINE__, __func__)
  #define DEBUG_NEGINT(n) negint_error(n, __FILE__, __LINE__, __func__)
  #define UNREACHABLE() unreachable_error(__FILE__, __LINE__, __func__)
#else
  #define UNUSED
  #define UNIMPLEMENTED
  #define DEBUG_NULL(p)
  #define DEBUG_ZERO(n)
  #define DEBUG_NEGINT(n)
  #define UNREACHABLE()
#endif /* DEBUG */

#define PRINT_GRAPH(g) print_graph(g, __FILE__, __LINE__, __func__)
#define PRINT_POS(p) print_pos(p, __FILE__, __LINE__, __func__)
#define PRINT_HOVERED(c) print_hovered(c, __FILE__, __LINE__, __func__)
#define PRINT_SELECTED(c) print_selected(c, __FILE__, __LINE__, __func__)

#endif /* ERROR_H__ */
