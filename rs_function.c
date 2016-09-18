/*********************************************************************************
  *Copyright(C),2016-2017,whitestonex
  *FileName:    rs_function.c
  *Author:      whitestonex
  *Version:     0.1
  *Date:        2016-09-18
  *Description: resolve sudoku by different guess;
  *Others:
  *History:
     1.Date:
       Author:
       Modification:
**********************************************************************************/


#include "rs_global.h"




static void initData(void)
{
    int i,j,k,l,x,y;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (sudokuBt[i][j].iValue != 0)
            {
                sudokuBt[i][j].iPossibleCount = 0;
                sudokuBt[i][j].iPossibleType = 0;
            }
            else
            {
                sudokuBt[i][j].iPossibleCount = 9;
                sudokuBt[i][j].iPossibleType = 0x1FF;
                for (k = 0; k < 9; k++)
                {
                    sudokuBt[i][j].arrayPossibleFlag[k] = 1;
                    sudokuBt[i][j].arrayPossibleValue[k] = k+1;
                }
            }
        }
    }

    memset(&pCheckList,0x0,sizeof(pCheckList));

    k = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            pCheckList[k][j] = &sudokuBt[i][j];
        }
        k++;
    }

    for (j = 0; j < 9; j++)
    {
        for (i = 0; i < 9; i++)
        {
            pCheckList[k][i] = &sudokuBt[i][j];
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
                    pCheckList[k][l++] = &sudokuBt[3*i+x][3*j+y];
                }
            }
            k++;
        }
    }
}



int rsLoadData(char *pcDataFile)
{
    FILE *pF = NULL;
    char cLine[32];
    int i, j;

    pF = fopen(pcDataFile, "r");
    if (pF == NULL)
    {
        WSX_LOG_ERROR("Load sudoku data file %s failed", pcDataFile);
        return -1;
    }

    memset(&sudokuBt[0][0], 0x0, sizeof(sudokuBt));

    i = 0;
    while(!feof(pF))
    {
        memset(cLine, 0x0, sizeof(cLine));
        fgets(cLine, sizeof(cLine), pF);

        for (j = 0; j < 9; j++)
        {
            sudokuBt[i][j].iValue = cLine[2*j]-'0';
        }
        i++;
    }

    fclose(pF);

    initData();

    return 0;
}

void rsPrintSudoku(void)
{
    int i, j, k;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%d  ", sudokuBt[i][j].iValue);
        }
        printf("\n");
    }

#if 0
    printf("========\n");

    for (k = 0; k < 3 ; k++)
    {
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                printf("%d  ", pCheckList[9*k+i][j]->iValue);
            }
            printf("\n");
        }
        printf("\n");
    }
#endif

}
