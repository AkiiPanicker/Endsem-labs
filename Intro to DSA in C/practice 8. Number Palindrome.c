#include <stdio.h>
#include <stdlib.h>


int main()
{
  char name[20] = "PSUC assignment 4";
  char *cptr = name;

  while(*cptr != '\0')
  {
    cptr++;
  } 
  printf("%d",cptr-name);
  return 0;
}