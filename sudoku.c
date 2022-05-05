#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  pthread_t tid;
  int psize;
  int **grid;
  bool valid;
  bool complete;
} GridStruct;

pthread_t row_tid;
pthread_t column_tid;
pthread_t helper_tid;
SubGridStruct *sub_grid_struct;
GridStruct *grid_struct_row;
GridStruct *grid_struct_column;
pthread_mutex_t num_lock;

//获取SubGrid的值
//psize为子网格的大小
int getSubGridValue(int psize, int **grid, int subGrid, int subX, int subY)
{
  int value;
  int sub_startX = psize * ((subGrid - 1) / psize) + 1;
  int sub_startY = psize * ((subGrid - 1) % psize) + 1;
  value = grid[sub_startX + subX - 1][sub_startY + subY - 1];

  return value;
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
//传入sub_grid_struct数组第i个子网格的地址
bool subGridValid(SubGridStruct * sub_grid_struct)
{
  bool flag = true;
  int sub_psize = sub_grid_struct->psize;
  bool sub_grid_flags[sub_psize * sub_psize + 1];
  for(int i = 1; i <= sub_psize * sub_psize; i++) {
    sub_grid_flags[i] = false;
  }
  //判断过程
  for(int row = 1; row <= sub_psize; row++) {
    for(int column = 1; column <= sub_psize; column++) {
      if(sub_grid_flags[sub_grid_struct->grid[row][column]] == false) {
        sub_grid_flags[sub_grid_struct->grid[row][column]] = true;
      } else {
        flag = false;
        return flag;
      }
    }
  }
  

  return flag;
}

// subGrid是否已经完成
bool subGridComplete(SubGridStruct * sub_grid_struct)
{
  bool flag = true;

  int sub_psize = sub_grid_struct->psize;
  for(int row = 1; row <= sub_psize; row++) {
    for(int column = 1; column <= sub_psize; column++) {
      if(sub_grid_struct->grid[row][column] == 0) {
        flag = false;
        return flag;
      }
    }
  }

  return flag;
}

// subGrid线程执行的方法
// 传入指向sub_grid_struct数组元素i的指针
void *subGridHelper(void *arg)
{
  //判断子网格是否完成，若完成则判断是否有效
  SubGridStruct *sub_grid_struct = (SubGridStruct *)arg;
  if(subGridComplete(sub_grid_struct) == false) {
    sub_grid_struct->complete = false;
  } else if(subGridValid(sub_grid_struct) == false) {
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
    for(int column = 1; column < psize + 1; column++) {
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
  int zero_count = 0;
  bool row_flags[psize + 1][psize + 1];
  int row_idx;
  int column_idx;

  for(int row = 1; row <= psize; row++) {
    for(int column = 1; column <= psize; column++) {
      if(grid[row][column] == 0) {
        zero_count++;
        row_idx = row;
        column_idx = column;
      } else {
        row_flags[row][grid[row][column]] = true;
      }
    }
    if(zero_count == 1) {
      for(int i = 1; i <= psize; i++) {
        if(row_flags[row][i] != true) {
          grid[row_idx][column_idx] = i;
          flag = true;
        }
      }
    } else if(zero_count >= 2) {
      flag = false;
    }
    zero_count = 0;
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
  } else {
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
  bool column_flags[psize + 1][psize + 1];
  for(int row = 1; row <= psize; row++) {
    for(int column = 1; column <= psize; column++) {
      column_flags[row][column] = false;
    }
  }

  for(int column = 1; column <= psize; column++) {
    for(int row = 1; row <= psize; row++) {
      if(column_flags[grid[row][column]][column] == false) {
        column_flags[grid[row][column]][column] = true;
      } else {
        flag = false;
        return flag;
      }
    }
  }

  return flag;
}

//列是否完成
bool columnComplete(int psize, int **grid)
{
  bool flag = true;
  int zero_count = 0;
  bool column_flags[psize + 1][psize + 1];
  int row_idx;
  int column_idx;

  for(int column = 1; column <= psize; column++) {
    for(int row = 1; row <= psize; row++) {
      if(grid[row][column] == 0) {
        zero_count++;
        row_idx = row;
        column_idx = column;
      } else {
        column_flags[grid[row][column]][column] = true;
      }
    }
    if(zero_count == 1) {
      for(int i = 1; i <= psize; i++) {
        if(column_flags[i][column] != true) {
          grid[row_idx][column_idx] = i;
          flag = true;
        }
      }
    } else if(zero_count > 1) {
      flag = false;
    }
    zero_count = 0;
  }

  return flag;
}

//列扫描线程执行的方法
void *columnHelper(void *arg)
{
  //判断列是否完成，若完成则判断是否有效；
  GridStruct *grid_struct = (GridStruct *)arg;
  //判断行是否完成，若完成则判断是否有效；
  if(columnComplete(grid_struct->psize, grid_struct->grid) == false) {
    grid_struct->complete = false;
  } else {
    if(columnValid(grid_struct->psize, grid_struct->grid) == false) {
      grid_struct->valid = false;
    }
  }

  return NULL;
}

//扫描线程执行的方法，如需要可用
void *helper(void *arg)
{
  rowHelper(grid_struct_row);
  columnHelper(grid_struct_column);

  return NULL;
}

//执行任务，这里初始化线程等
void task(int psize, int **grid, SubGridStruct *subGridStruct)
{
  int err;
  //初始化行和列的GridStruct *grid_struct
  grid_struct_row = (GridStruct *)calloc(1, sizeof(GridStruct));
  grid_struct_column = (GridStruct *)calloc(1, sizeof(GridStruct));

  grid_struct_row->psize = psize;
  grid_struct_row->grid = grid;
  grid_struct_row->complete = true;
  grid_struct_row->valid = true;

  grid_struct_column->psize = psize;
  grid_struct_column->grid = grid;
  grid_struct_column->complete = true;
  grid_struct_column->valid = true;
  //创建行的线程和列的线程
  err = pthread_create(&grid_struct_row->tid, NULL, rowHelper, grid_struct_row);
  if(err != 0) {
    fprintf(stderr, "pthread_create error.\n");
  }
  err = pthread_create(&grid_struct_column->tid, NULL, rowHelper, grid_struct_row);
  if(err != 0) {
    fprintf(stderr, "pthread_create error.\n");
  }
  //循环创建子网格的线程
  for(int i = 1; i <= psize; i++) {
    err = pthread_create(&subGridStruct[i].tid, NULL, subGridHelper, &subGridStruct[i]);
    if(err != 0) {
      fprintf(stderr, "pthread_create error.\n");
    }
  }
}

//设置结果
//将此函数用在checkSudoku中，线程执行之后
void setResult(int psize, bool *complete, bool *valid, SubGridStruct *subGridStruct)
{
  if(grid_struct_row->complete == false || grid_struct_column->complete == false) {
    *complete = false;
  }

  if(grid_struct_row->valid == false || grid_struct_column ->valid == false) {
    *valid = false;
  }
}

//检查
void checkSudoku(int psize, int **grid, bool *complete, bool *valid)
{ 
  int err;
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

  //pthread_mutex_init(&num_lock, NULL);
  //使用task,创建行、列、子网格的线程 
  task(psize, grid, sub_grid_struct);

  err = pthread_join(grid_struct_row->tid, NULL);
  if(err != 0) {
    fprintf(stderr, "pthread_join error.\n");
  }
  err = pthread_join(grid_struct_column->tid, NULL);
  if(err != 0) {
    fprintf(stderr, "pthread_join error.\n");
  }
  for(int i = 1; i <= psize; i++) {
    err = pthread_join(sub_grid_struct[i].tid, NULL);
    if(err != 0) {
      fprintf(stderr, "pthread_join error.\n");
    }
  }

  err = pthread_create(&helper_tid, NULL, helper, NULL);
  if(err != 0) {
    fprintf(stderr, "pthread_create error.\n");
  }
  err = pthread_join(helper_tid, NULL);
  if(err != 0) {
    fprintf(stderr, "pthread_join error.\n");
  }
  //线程执行后设置验证的结果
  setResult(psize, complete, valid, sub_grid_struct);

  free(grid_struct_row);
  free(grid_struct_column);
  free(sub_grid_struct);
}

//读取数独数据
int readSudoku(char *filename, int ***grid)
{
  int psize;
  FILE *fp_in;
  char read_line[MAX_LINE_LEN];
  char *pch;

  if((fp_in = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Failed to open %s.\n", filename);
    exit(EXIT_FAILURE);
  }
  fgets(read_line, MAX_LINE_LEN, fp_in);
  pch = strtok(read_line, "\n");
  psize = atoi(pch);

  *grid = (int **)calloc(psize + 1, sizeof(int *));
  for(int i = 0; i < psize + 1; i++) {
    (*grid)[i] = (int *)calloc(psize + 1, sizeof(int));
  }

  for(int i = 1; i <= psize; i++) {
    fgets(read_line, MAX_LINE_LEN, fp_in);
    pch = strtok(read_line, " \n");
    (*grid)[i][1] = atoi(pch);
    for(int j = 2; j <= psize; j++) {
      pch = strtok(NULL, " \n");
      (*grid)[i][j] = atoi(pch);
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
