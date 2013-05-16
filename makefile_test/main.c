/* main.c */
#include <stdio.h>
/* other headers */
#include "add/add.h"
#include "sub/sub.h"

int main(void)
{
  int a = 10, b = 12;
  float x = 1.23456, y = 9.87654321;
  
  /* using add/sub to print result */
  printf("int a+b IS:%d\n",add_int(a,b));
  printf("int a-b IS:%d\n",sub_int(a,b));
  printf("float x+y IS:%d\n",add_float(x,y));
  printf("float x-y IS:%d\n",sub_float(x,y));
  return 0;
}
