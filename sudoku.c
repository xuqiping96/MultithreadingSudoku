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

typedef struct
{
  int psize;
  int **grid;
  bool valid;
  bool complete;
} GridStruct;

pthread_t row_tid;
pthread_t column_tid;
SubGridStruct *sub_grid_struct;
GridStruct grid_struct_row;
GridStruct grid_struct_column;

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
//对sub_grid_struct[subGrid]进行判断，psize为sub_grid_struct[subGrid].psize，grid为sub_grid_struct[subGrid].grid
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
  //判断子网格是否完成，若完成则判断是否有效
  SubGridStruct *sub_grid_struct = (SubGridStruct *)arg;
  if(subGridComplete(sub_grid_struct->psize, sub_grid_struct->grid, sub_grid_struct->id) == false) {
    sub_grid_struct->complete = false;
  } else if(subGridValid(sub_grid_struct->psize, sub_grid_struct->grid, sub_grid_struct->id) == false) {
    sub_grid_struct->valid = false;
  }

  return NULL;
}

//行是否有效
bool rowValid(int psize, int **grid)
{
  bool flag = true;
  bool row_flags[psize + 1][psize + 1];
  for(int row = 0; row < psize + 1; row++) {
    for(int column = 0; column < psize + 1; column++) {
      row_flags[row][column] = false;
    }
  }

  for(int row = 1; row < psize + 1; row++) {
    for(int column = 1; column < psize + 1; column++) {
      if(row_flags[row][grid[row][column]] == false) {
        row_flags[row][grid[row][column]] = true;
      } else {
        flag = false;
        return flag;
      }
    }
  }
  return flag;
}

//行是否已经完成
bool rowComplete(int psize, int **grid)
{
  bool flag = true;
  for(int row = 1; row <= psize; row++) {
    for(int column = 1; column <= psize; column++) {
      if(grid[row][column] == 0) {
        flag = false;
        return flag;
      }
    }
  }

  return flag;
}


//行扫描线程执行的方法
//传入grid结构体
void *rowHelper(void *arg) {
  GridStruct *grid_struct = (GridStruct *)arg;
  //判断行是否完成，若完成则判断是否有效；
  if(rowComplete(grid_struct->psize, grid_struct->grid) == false) {
    grid_struct->complete = false;
    if(rowValid(grid_struct->psize, grid_struct->grid) == false) {
      grid_struct->valid = false;
    }
  }

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
  //判断列是否完成，若完成则判断是否有效；

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
  //初始化行和列的GridStruct *grid_struct
  grid_struct_row.complete = true;
  grid_struct_row.valid = true;
  grid_struct_row.psize = psize;
  grid_struct_row.grid = grid;
  grid_struct_column.complete = true;
  grid_struct_column.valid = true;
  grid_struct_column.psize = psize;
  grid_struct_column.grid = grid;
  //创建行的线程和列的线程
  
  //循环创建子网格的线程
}

//设置结果
//将此函数用在checkSudoku中，线程执行之后
void setResult(int psize, bool *complete, bool *valid, SubGridStruct *subGridStruct)
{
  for(int i = 1; i <= psize; i++) {
    if(subGridStruct[i].complete == false) {
      *complete = false;
    }
    if(subGridStruct[i].valid == false) {
      *valid = false;
    }
  }
}

//检查
void checkSudoku(int psize, int **grid, bool *complete, bool *valid)
{ 
  //动态分配子网格结构，使用getSubGridValue初始化各个子网格
  sub_grid_struct = (SubGridStruct *)calloc(psize + 1, sizeof(SubGridStruct));
  for(int i = 1; i < psize + 1; i++) {
    sub_grid_struct[i].id = i;
    sub_grid_struct[i].psize = (int)sqrt((int)psize);
    sub_grid_struct[i].complete = *complete;
    sub_grid_struct[i].valid = *valid;
    sub_grid_struct[i].grid = (int **)calloc(sub_grid_struct[i].psize + 1, sizeof(int *));
    for(int row = 0; row < sub_grid_struct[i].psize + 1; row++) {
      sub_grid_struct[i].grid[row] = (int *)calloc(sub_grid_struct[i].psize + 1, sizeof(int));
    }
    for(int subX = 1; subX <= sub_grid_struct[i].psize; subX++) {
      for(int subY = 1; subY <= sub_grid_struct[i].psize; subY++) {
        sub_grid_struct[i].grid[subX][subY] = getSubGridValue(sub_grid_struct[i].psize, grid, sub_grid_struct[i].id, subX, subY);
      }
    }
  }
  //使用task,创建行、列、子网格的线程 
  task(psize, grid, sub_grid_struct);

  //线程执行后设置验证的结果

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
  bool valid = true;
  bool complete = true;

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
