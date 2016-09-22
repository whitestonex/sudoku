#ifndef _RS_GLOBAL_H_ 
#define _RS_GLOBAL_H_ 


#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "wsx_common.h"

typedef struct oneButton
{
    int iValue;
    int iPossibleCount;
    int iPossibleType;    
    int arrayPossibleFlag[9];
    int arrayPossibleValue[9];
} strButton;

typedef struct compareCollect
{
    int iCount;
    int iPossibleType;
    int arrayPosition[9];
    int arrayPossibleValue[9];
} strCompare;


extern strButton sudokuBt[9][9];
extern strButton *pCheckList[27][9];

#endif