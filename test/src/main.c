#include "includes.h"
#include "test_geometry.c"
#include "test_grow_matrix.c"

int main(void)
{
  test_rdist();
  test_grow_matrix();
  return 0;
}
