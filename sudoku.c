#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE_LEN 256

//结构体
//先验证谜题是否完成（是否有0），再验证是否有效（结果是否正确）
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

  for(int column = 1; column <= psize; column++) {
    if((*grid)[column] == 0) {
      flag = false;
      return flag;
    }
  }

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
//传入&&grid[1][i]，i为第i列，即第i个列的线程
bool columnComplete(int psize, int **grid)
{
  bool flag = true;
  int **column_data = grid;

  for(int i = 1; i <= psize; i++) {
    if(**column_data == 0) {
      flag = false;
      return flag;
    }
    column_data++;
  }

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
  FILE *fp_in;
  char *read_line;

  if((fp_in = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Failed to open %s.\n", filename);
    exit(EXIT_FAILURE);
  }
  fgets(read_line, MAX_LINE_LEN, fp_in);
  psize = atoi(strtok(read_line, "\n"));

  *grid = (int **)calloc(psize + 1, sizeof(int *));
  for(int i = 0; i < psize + 1; i++) {
    (*grid)[i] = (int *)calloc(psize + 1, sizeof(int));
  }

  for(int i = 1; i <= psize; i++) {
    fgets(read_line, MAX_LINE_LEN, fp_in);
    (*grid)[i][1] = atoi(strtok(read_line, " \n"));
    for(int j = 2; j <= psize; j++) {
      (*grid)[i][j] = atoi(strtok(NULL, " \n"));
    }
  }

  fclose(fp_in);

  return psize;
}

//打印数独
void printSudokuPuzzle(int psize, int **grid)
{
  for(int row = 1; row <= psize; row++) {
    for(int column = 1; column <= psize; column++) {
      printf("%d ", grid[row][column]);
    }
    printf("\n");
  }
}

//释放数独资源
void deleteSudokuPuzzle(int psize, int **grid)
{
  for(int i = 0; i < psize + 1; i++) {
    free(grid[i]);
  }
  free(grid);
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
