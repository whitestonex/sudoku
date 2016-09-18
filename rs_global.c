/*********************************************************************************
  *Copyright(C),2016-2017,whitestonex
  *FileName:    rs_global.c
  *Author:      whitestonex
  *Version:     0.1
  *Date:        2016-09-18
  *Description: define the global variables
  *Others:
  *History:
     1.Date:
       Author:
       Modification:
**********************************************************************************/

#include "rs_global.h"


int getDBGLevel(void)
{
    return 5;
}


strButton sudokuBt[9][9];
strButton *pCheckList[27][9];