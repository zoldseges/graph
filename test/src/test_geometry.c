#include <stdio.h>

void test_rdist() {
  int a = rdist(124.35345, 90.12343, 75.634234, 140.64523);
  // not sure if correct, but let's assume
  assert(a == 70);
}
