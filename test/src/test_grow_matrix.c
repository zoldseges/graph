void test_grow_matrix(void)
{
  Matrix m = {0};
  m.pm = calloc(4, sizeof(int));
  m.row_sz = 2;

  int w = -4;
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){
      set_matrix(m, i, j, w++);
    }
  }

  PRINT_MATRIX(m);
  grow_matrix(&m);
  PRINT_MATRIX(m);
}
