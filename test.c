#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define XX  4
char cBuffer[XX];


typedef struct XXx
{
  int v[9];
  int count;
  int index;
}D2List;

D2List SS[XX];


int atEnd()
{
  int iRet = 0;
  int i;

  for (i = 0 ; i < XX; i++)
  {
    if (SS[i].index != SS[i].count-1)
    {
      return  -1;
    }
  }
  return 0;
}

int show(void)
{
  int i;
  for (i = 0; i < XX; i++)
  {
    cBuffer[i] = SS[i].v[SS[i].index];
    printf("%d  ", cBuffer[i]);
  }
  printf("\n");
}

int pop(int i)
{
  if ((i < 0)||(i>XX))
  {
    return 0;
  }

  if (SS[i].index == SS[i].count -1)
  {
    //printf("Pop to up level %d\n", i-1);
    pop(i-1);
    SS[i].index = 0;
    //printf("Reset level %d index to 0\n",i);
  }
  else
  {
    SS[i].index += 1;
    //printf("increase level %d index to %d\n",i,SS[i].index);
  }
  return 0;
}

int main(int argc, char **argv)
{
  SS[0].count=2;
  SS[0].index=0;
  SS[0].v[0] = 1;
  SS[0].v[1] = 2;

  SS[1].count=3;
  SS[1].index=0;
  SS[1].v[0] = 3;
  SS[1].v[1] = 7;
  SS[1].v[2] = 8;

  SS[2].count=1;
  SS[2].index=0;
  SS[2].v[0] = 9;

  SS[3].count=4;
  SS[3].index=0;
  SS[3].v[0] = 0;
  SS[3].v[1] = 1;
  SS[3].v[2] = 2;
  SS[3].v[3] = 5;



  while(atEnd())
  {
  show();
  pop(XX-1);
  }
  show();


  return 0;
}
