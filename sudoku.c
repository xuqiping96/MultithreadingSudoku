//头文件
#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//结构体
typedef struct
{
  pthread_t tid;
  int id;
  int psize;
  int **grid;
  bool valid;
  bool complete;
} SubGridStruct;

//获取SubGrid的值
int getSubGridValue(int psize, int **grid, int subGrid, int subX, int subY)
{
  return 0;
}

//打印SubGrid索引值
void printSubGridIndex(int psize, int **grid, int subGrid)
{
}

//打印SubGrid
void printSubGrid(int psize, int **grid)
{
}

// subGrid是否有效
bool subGridValid(int psize, int **grid, int subGrid)
{
  bool flag = true;
  return flag;
}

// subGrid是否已经完成
bool subGridComplete(int psize, int **grid, int subGrid)
{
  bool flag = true;
  return flag;
}

// subGrid线程执行的方法
void *subGridHelper(void *arg)
{
  return NULL;
}

//行是否有效
bool rowValid(int psize, int **grid)
{
  bool flag = true;
  return flag;
}

//行是否已经完成
bool rowComplete(int psize, int **grid)
{
  bool flag = true;
  return flag;
}

//行扫描线程执行的方法
void *rowHelper(void *arg)
{
  return NULL;
}

//列是否有效
bool columnValid(int psize, int **grid)
{
  bool flag = true;
  return flag;
}

//列是否完成
bool columnComplete(int psize, int **grid)
{
  bool flag = true;
  return flag;
}

//列扫描线程执行的方法
void *columnHelper(void *arg)
{
  return NULL;
}

//扫描线程执行的方法，如需要可用
void *helper(void *arg)
{
  return NULL;
}

//执行任务，这里初始化线程等
void task(int psize, int **grid, SubGridStruct *subGridStruct)
{
}

//设置结果
void setResult(int psize, bool *complete, bool *valid, SubGridStruct *subGridStruct)
{
}

//检查
void checkSudoku(int psize, int **grid, bool *complete, bool *valid)
{
}

//读取数独数据
int readSudoku(char *filename, int ***grid)
{
  int psize;
  return psize;
}

//打印数独
void printSudokuPuzzle(int psize, int **grid)
{
}

//释放数独资源
void deleteSudokuPuzzle(int psize, int **grid)
{
}

//主函数入口，此函数不要增加其他内容了，无须改动
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("usage: ./sudoku puzzle.txt\n");
    return EXIT_FAILURE;
  }

  int **grid = NULL;
  int sudokuSize = 0;
  bool valid = false;
  bool complete = false;

  sudokuSize = readSudoku(argv[1], &grid);
  checkSudoku(sudokuSize, grid, &complete, &valid);
  printf("Complete Sudoku? ");
  printf(complete ? "true\n" : "false\n");

  if (complete)
  {
    printf("Valid Sudoku? ");
    printf(valid ? "true\n" : "false\n");
  }

  printSudokuPuzzle(sudokuSize, grid);
  deleteSudokuPuzzle(sudokuSize, grid);
  return EXIT_SUCCESS;
}
