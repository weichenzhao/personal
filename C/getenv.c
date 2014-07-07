/* getenv example: getting path */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* getenv */

int main ()
{
  char* pPath;
  pPath = getenv ("PATH");
  if (pPath!=NULL)
    printf ("The current path is: %s\n",pPath);
  setenv("TEST", "1", 1);
  pPath = getenv ("TEST");
  if (pPath!=NULL)
    printf ("TEST: %s\n",pPath);
  return 0;
}
