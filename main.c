#include "stdlib.h"
#include "stdio.h"
#include "string.h"









#if 0
2-0    7-0    0-3    5-0    4-0    0-2    0-4    0-4    8-0
4-0    6-0    0-2    7-0    3-0    8-0    0-2    5-0    2-0
5-0    8-0    0-2    1-0    2-0    0-2    0-5    0-5    0-3

0-4    0-2    8-0    0-2    1-0    5-0    0-5    0-5    0-3
0-2    5-0    4-0    0-2    9-0    2-0    0-4    0-3    6-0
0-3    1-0    2-0    0-3    7-0    4-0    0-3    0-2    5-0

0-2    0-2    5-0    4-0    8-0    1-0    0-5    0-5    0-3
8-0    4-0    6-0    2-0    5-0    7-0    0-2    0-2    1-0
1-0    2-0    7-0    9-0    6-0    3-0    5-0    8-0    4-0

#endif


typedef struct myData
{
	int iTrueValue;
	int iPossibleCount;
	int iPossibleValue[9];
	int iMask;
}tMyData;

typedef struct myType
{
	int iType;
	int iCount;
	int iPossibleValue[9];
}tMyType;


static tMyData Data[9][9];

static tMyData *pDataGroup[27][9];

void importData(char *pcFileName)
{
	FILE *pF = NULL;
	char cBuffer[32];
	int i,j,k,l,x,y;


	pF = fopen(pcFileName, "r");
	if (pF == NULL)
	{
		printf("Can't open File %s\n",pcFileName);
		return;
	}

	i = 0;
	while(!feof(pF))
	{
		memset(cBuffer,0x0,sizeof(cBuffer));
		fgets(cBuffer, sizeof(cBuffer), pF);
		for (j = 0; j < 9; j++)
		{
			Data[i][j].iTrueValue = cBuffer[2*j]-'0';
			if ((Data[i][j].iTrueValue > 9)||(Data[i][j].iTrueValue < 0))
			{
				printf("Import a wrong data %d\n", Data[i][j].iTrueValue);
				return;
			}
			if (Data[i][j].iTrueValue == 0)
			{
				for (k = 0; k < 9; k++)
				{
					Data[i][j].iPossibleValue[k] = 1;
				}
				Data[i][j].iPossibleCount = 9;
			}
			else
			{
        for (k = 0; k < 9; k++)
				{
					Data[i][j].iPossibleValue[k] = 0;
				}
				Data[i][j].iPossibleCount = 0;
			}
		}
		i++;
	}
	fclose(pF);


  memset(&pDataGroup,0x0,sizeof(pDataGroup));

  k = 0;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      pDataGroup[k][j] = &Data[i][j];
    }
    k++;
  }

  for (j = 0; j < 9; j++)
  {
    for (i = 0; i < 9; i++)
    {
      pDataGroup[k][i] = &Data[i][j];
    }
    k++;
  }

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      l = 0;
      for (x = 0; x < 3; x++)
      {
        for (y = 0; y < 3; y++)
        {
          pDataGroup[k][l++] = &Data[3*i+x][3*j+y];
        }
      }
      k++;
    }
  }
}

void showData(void)
{
	int i,j;

printf("==========\n");
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d-%d    ", Data[i][j].iTrueValue,Data[i][j].iPossibleCount);
			//printf("%d    ", Data[i][j].iTrueValue);
		}
		printf("\n");
	}

#if 0
  for (i = 0; i < 27; i++)
  {
    for (j = 0; j < 9; j++)
    {
      printf("%d ", pDataGroup[i][j]->iTrueValue);
    }
    printf("\n");
  }
#endif
}

int generateType(int *piPossibleValue)
{
	int i,x;

	x = 0;
	for (i = 0; i < 9; i++)
	{
		x = x*2 + piPossibleValue[i];
	}

	return x;
}


void ttt(tMyData **pOneDataList, int iLevel)
{
	int i,j,k,l,x,y;
	int type,flag;
	int iTypeValue = 0;
	tMyType list[9];

	memset(&list, 0x0, sizeof(list));

	iTypeValue = 1;
	for(i = 0; i < 9 ; i++)
	{
		if (pOneDataList[i]->iPossibleCount != 0)
		{
			type = generateType(&(pOneDataList[i]->iPossibleValue[0]));
			//printf("Type is 0x%x\n", type);

			flag = 0;
			for (j = 0; j < iTypeValue; j++)
			{
				if (type == list[j].iType)
				{
					list[j].iCount++;
					flag = 1;
				}
			}

			if (flag == 0)
			{
				list[iTypeValue-1].iType = type;
				list[iTypeValue-1].iCount = 1;
				k = 0;
				for (j = 0; j < 9; j++)
				{
					if (pOneDataList[i]->iPossibleValue[j] != 0)
					{
						list[iTypeValue-1].iPossibleValue[k++] = j;
					}
				}
				iTypeValue++;
			}
		}
	}
	//printf("Type Count is %d\n", iTypeValue);

#if 1
	for (i = 0; i < iTypeValue; i++)
	{
		if (list[i].iCount == iLevel)
		{
			for (j = 0; j < 9; j++)
			{
				if (pOneDataList[i]->iPossibleCount != iLevel)
				{
					for (k = 0; k < 9; k++)
					{
						for (l = 0; l < iLevel; l++)
						{
							x = list[i].iPossibleValue[l];
							printf("%d is not possible\n",x);
							if (pOneDataList[i]->iPossibleValue[x] != 0)
							{
								pOneDataList[i]->iPossibleValue[x] = 0;
								pOneDataList[i]->iPossibleCount --;
							}
						}
					}
				}
			}
		}
	}
#endif
}

void excludeData_2(void)
{
	int i,j;

	for (i = 0; i < 27; i++)
	{
		ttt(&(pDataGroup[i][0]),2);
	}
}


void excludeData_1(void)
{
	int i,j,k,l,x;

	for (i = 0; i < 27; i++)
	{
		for (j = 0; j < 9; j++)
		{
			x = pDataGroup[i][j]->iTrueValue;
			if (x != 0)
			{
				for (k = 0; k < 9; k++)
				{
					if (pDataGroup[i][k]->iPossibleValue[x-1] != 0)
					{
						//printf("remove one\n");
						pDataGroup[i][k]->iPossibleValue[x-1] = 0;
						pDataGroup[i][k]->iPossibleCount --;
					}
				}
			}
		}
	}
}

int guessData_1(void)
{
	int i,j,k,l,iTotal,iFlag;

	for (i = 0; i < 27; i++)
	{
		for (k = 0; k < 9; k++)
		{
			iTotal = 0;
			for (j = 0; j < 9; j++)
			{
				if (pDataGroup[i][j]->iPossibleValue[k] == 1)
				{
					iTotal ++;
					l = j;
				}
			}
			if (iTotal == 1)
			{
				pDataGroup[i][l]->iTrueValue = k+1;
				pDataGroup[i][l]->iPossibleCount = 0;
				for (j = 0; j < 9; j++)
				{
					pDataGroup[i][l]->iPossibleValue[j] = 0;
				}
				printf("RRR\n");
				return 1;
			}
		}
	}

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (Data[i][j].iPossibleCount == 1)
			{
				for (k = 0; k < 9; k++)
				{
					if (Data[i][j].iPossibleValue[k] == 1)
					{
						Data[i][j].iTrueValue = k+1;
						Data[i][j].iPossibleValue[k] = 0;
						Data[i][j].iPossibleCount = 0;
						printf("SSSSSSS\n");
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

void showPossible(void)
{
	int i,j,k;

	for (i = 0; i < 9 ; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("Count is %d :", Data[i][j].iPossibleCount);
			for (k = 0; k < 9; k++)
			{
				if (Data[i][j].iPossibleValue[k] != 0)
				{
					printf("%d ", k);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
}


int main(int argc,char **argv)
{
	int x,i;
	importData(argv[1]);

	showData();

	excludeData_1();
	x = 1;
	while(guessData_1())
	{
		excludeData_1();
		x++;
	}

	showData();

	showPossible();
	excludeData_2();
	showPossible();
	guessData_1();
	guessData_1();

/*
	excludeData_2();

	while(guessData_1())
	{
		excludeData_2();
		excludeData_1();
	}
	*/

	showData();
	return 0;
}
