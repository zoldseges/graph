/* Turn on error checking */
#define DEBUG

#ifndef DEBUG_H__
#define DEBUG_H__

void null_error(void *p, char *filename, int linum, const char *func);
void zero_error(int num, char *filename, int linum, const char *func);

#define UNUSED __attribute__((unused))
#define UNIMPLEMENTED assert(0)

#ifdef DEBUG
  #define DEBUG_NULL(p) null_error(p, __FILE__, __LINE__, __func__)
  #define DEBUG_ZERO(n) zero_error(n, __FILE__, __LINE__, __func__)
#else
  #define DEBUG_NULL(p)
  #define DEBUG_ZERO(n)
#endif /* DEBUG */

#endif /* ERROR_H__ */
