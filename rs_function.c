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

int function_2(int iListIndex)
{
    int i, j, k;
#if 0
    for (k = 8; k > 2; k--)
    {
        j = 0;
        for (i = 0; i < 9; i++)
        {
            if(pCheckList[iListIndex][i]->iPossibleCount == k)
            {
                j ++
            }
        }
        if (j == k)
        {
            function_3(iListIndex, k);
        }
    }
#endif
    return 0;
}



int removeSame2(int iListIndex)
{
    int i,j,k,l;
    int iDifferentTypeCount = 0;
    int iMatchFlag = 0;
    int iRemoveFlag = 0;
    int iPossibleCount = 0;
    strCompare X[9];
#if 0
if (iListIndex != 26)
{
    return 0;
}
#endif
    memset(X, 0x0, sizeof(X));

    for (i = 0; i < 9; i++)
    {
        if (pCheckList[iListIndex][i]->iPossibleCount == 2)
        {
//            printf("%d possible count is 2 and iDifferentTypeCount is %d\n",i,iDifferentTypeCount);
            iMatchFlag = 0;
            for (j = 0; j < iDifferentTypeCount+1; j++)
            {
                if (pCheckList[iListIndex][i]->iPossibleType == X[j].iPossibleType)
                {
                    X[j].arrayPosition[X[j].iCount] = i;
                    X[j].iCount ++;
                    iMatchFlag = 1;
                    break;
                }
            }

            if (iMatchFlag == 0)
            {
                X[iDifferentTypeCount].iPossibleType = pCheckList[iListIndex][i]->iPossibleType;
                X[iDifferentTypeCount].iCount = 1;
                for (j = 0; j < 2; j++)
                {
                    X[iDifferentTypeCount].arrayPossibleValue[j] = pCheckList[iListIndex][i]->arrayPossibleValue[j];
                }
                iDifferentTypeCount++;
            }
        }
    }

#if 0
    int iCount;
    int iPossibleType;
    int arrayPosition[9];
    int arrayPossibleValue[9];
#endif
#if 0
printf("There are %d\n", iDifferentTypeCount);
for (i = 0; i < iDifferentTypeCount; i++)
{
    printf("There are %d same for this type %d means %d and %d\n", X[i].iCount, X[i].iPossibleType, X[i].arrayPossibleValue[0],X[i].arrayPossibleValue[1]);
}
#endif


    for (i = 0; i < iDifferentTypeCount; i++)
    {
        if (X[i].iCount == 2)
        {
            for (j = 0; j < 9; j++)
            {
                if ((j != X[i].arrayPosition[0]) && (j != X[i].arrayPosition[1]))
                {
                    iPossibleCount = pCheckList[iListIndex][j]->iPossibleCount;
//printf("index %d have %d possible\n", j, iPossibleCount);                    
                    for (k = 0; k < iPossibleCount; k++)
                    {
                        if ((pCheckList[iListIndex][j]->arrayPossibleValue[k] == X[i].arrayPossibleValue[0])||(pCheckList[iListIndex][j]->arrayPossibleValue[k] == X[i].arrayPossibleValue[1]))
                        {
                            pCheckList[iListIndex][j]->arrayPossibleValue[k] = 0;
                            pCheckList[iListIndex][j]->iPossibleCount --;
                            pCheckList[iListIndex][j]->iPossibleType -= (1<<pCheckList[iListIndex][j]->arrayPossibleValue[k]);
                            iRemoveFlag = 1;
                        }
                    }

                    if (iRemoveFlag == 1)
                    {
                        for (k = 0,l = 0; k < iPossibleCount; k++)
                        {
                            if (pCheckList[iListIndex][j]->arrayPossibleValue[k] != 0)
                            {
                                pCheckList[iListIndex][j]->arrayPossibleValue[l] = pCheckList[iListIndex][j]->arrayPossibleValue[k];
                                l++; 
                            }
                        }
                    }
                } 
            }
        }
    }

    return iRemoveFlag;
}




int preHandleList(int iListIndex)
{
    int i, j, k, l;
    int iPosition = 0;
    int iGetFlag = 0;
    int iSum = 0;

    for (i = 0; i < 9; i++)
    {
        if (pCheckList[iListIndex][i]->iValue != 0)
        {
            iPosition = pCheckList[iListIndex][i]->iValue - 1;
            for (j = 0; j < 9; j++)
            {
                if (pCheckList[iListIndex][j]->arrayPossibleFlag[iPosition] == 1)
                {
                    iGetFlag = 1;
                    pCheckList[iListIndex][j]->arrayPossibleFlag[iPosition] = 0;
                    pCheckList[iListIndex][j]->iPossibleType -= (1<<iPosition);

                    for (k = 0, l = 0; k < pCheckList[iListIndex][j]->iPossibleCount; k++)
                    {
                        if (pCheckList[iListIndex][j]->arrayPossibleValue[k] != pCheckList[iListIndex][i]->iValue)
                        {
                            pCheckList[iListIndex][j]->arrayPossibleValue[l] = pCheckList[iListIndex][j]->arrayPossibleValue[k]; 
                            l++;
                        }
                    }

                    pCheckList[iListIndex][j]->iPossibleCount --;
                }
            }
        }
    }


    iGetFlag += removeSame2(iListIndex);

    for (i = 0; i < 9; i++)
    {
        if (pCheckList[iListIndex][i]->iPossibleCount == 1)
        {
            pCheckList[iListIndex][i]->iPossibleCount = 0;
            pCheckList[iListIndex][i]->iPossibleType = 0;
            pCheckList[iListIndex][i]->iValue = pCheckList[iListIndex][i]->arrayPossibleValue[0];
            if (pCheckList[iListIndex][i]->iValue == 0)
            {
                WSX_LOG_ERROR("Wrong guess value is 0");
            }
            else
            {
                
            }
        }
    }

    for (j = 0; j < 9; j ++)
    {
        iSum = 0;
        for (i = 0; i < 9; i++)
        {
            if (pCheckList[iListIndex][i]->arrayPossibleFlag[j]==1)
            {
                iSum ++;
                iPosition = i;
            }
        }
        if (iSum == 1)
        {
            pCheckList[iListIndex][iPosition]->iValue = j+1;
            pCheckList[iListIndex][iPosition]->iPossibleCount = 0;
            pCheckList[iListIndex][iPosition]->iPossibleType = 0;
            for (i = 0; i < 9; i++)
            {
                pCheckList[iListIndex][iPosition]->arrayPossibleFlag[i] = 0;
                pCheckList[iListIndex][iPosition]->arrayPossibleValue[i] = 0;
            }
        }
    }

    return iGetFlag;
}

void FUN1(void)
{
    int iFlag = 0;
    int i,j;

    j = 0;
    while (1)
    {
        iFlag = 0;
        for (i = 0; i < 27 ; i ++)
        {
            iFlag += preHandleList(i);
            j++;
        }
        if (iFlag == 0)
        {
            break;
        }
    }
    
    printf("\nJ is %d\n", j);
}


void rsResolve(void)
{
    int i,iFlag,iLevel;

    iLevel = 1;
#if 0
    while (iLevel<= 9)
    {
        iFlag = 0;
        for (i = 0; i < 27; i++)
        {
            preHandleList();
            iFlag += function_1(i, iLevel);
        }

        if (iFlag == 0)
        {
            iLevel++;
        }
        else
        {
            iLevel = 1;
        }
    }
#endif
}


void rsPrintdebug(void)
{
    int i, j, k;

    for (i = 0; i < 27; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (pCheckList[i][j]->iValue==0)
            {
                printf("%d-%d: (%d):",i,j,pCheckList[i][j]->iPossibleCount);
                for (k = 0 ;k < pCheckList[i][j]->iPossibleCount; k++)
                {
                    printf("%d ", pCheckList[i][j]->arrayPossibleValue[k]);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
}