#include<stdio.h>

struct smth{
  char x
};

int main(int argc, char *argv[]){
  struct smth a = { 10 };
  struct smth b = { 20 };
  void *array[] = { &a, &b };
  for( int i = 0; i < 2; i++ ){
    printf("%d\n", (struct smth)array[i].x);
  }
  return 0;
}
