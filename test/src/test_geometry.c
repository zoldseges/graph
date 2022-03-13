#include <stdio.h>

void test_rdist() {
  Point p1;
  p1.x = 124.35345;
  p1.y = 75.634234;
  Point p2;
  p2.x = 90.12343;
  p2.y = 140.64523;
  int a = rdist(p1, p2);
  assert(a == 73);
}
