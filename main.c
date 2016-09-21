/*********************************************************************************
  *Copyright(C),2016-2017,whitestonex
  *FileName:    main.c
  *Author:      whitestonex
  *Version:     0.1
  *Date:        2016-09-18
  *Description:	this is main entrance of resolve sudoku, load a data file as input
  				out put a resolved sudoku;
  *Others:
  *History:
     1.Date:
       Author:
       Modification:
**********************************************************************************/

#include "rs_global.h"
#include "rs_function.h"



int main(int argc, char *argv[])
{
	rsLoadData(argv[1]);


	rsPrintSudoku();

  FUN1();
  printf("\n\n");

  rsPrintSudoku();
  
  rsPrintdebug();
  return 1;
}