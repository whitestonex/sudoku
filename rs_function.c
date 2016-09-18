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





int rsLoadData(char *pcDataFile)
{
    FILE *pF = NULL;
    char cLine[32];

    pF = fopen(pcDataFile, "r");
    if (pF == NULL)
    {
        WSX_LOG_ERROR("Load sudoku data file %s failed", pcDataFile);
        return -1;
    }

    while(!feof(pF))
    {
        memset(cLine, 0x0, sizeof(cLine));
        fgets(cLine, sizeof(cLine), pF);

    }



    fclose(pF);

    return 0;
}

void rsPrintSudoku(void)
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%d  ", sudokuBt[i][j].iValue);
        }
        printf("\n");
    }
}
