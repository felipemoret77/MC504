//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//nan - "not a number", defines when a cell is empty in the sudoku matrix
#define nan 0


//Struct that represents a sub_square 3x3 in the Sudoku
typedef struct Sudoku_And_Sub_Square_Number{
	int* sudoku;
	int sub_square_number;
	} Sudoku_And_Sub_Square_Number;


//Simple function to duplicate a matrix
void copy_matrix(int matrix1[9][9], int matrix2[9][9]);

//FUnction that gives the number (0,..,8) of the sub_sqaure 3x3 that a number in positio (i,j) in the orifinal matrix belongs
int give_square_by_cell_position(int i, int j);

//Function that verifies the validity (output 1) or invalidity (output 0) of lines or if the lines are not complete, but still valid (output 2)
void* line_verifier(void* arg);

//Function that verifies the validity (output 1) or invalidity (output 0) of columns or if the columns are not complete, but still valid (output 2)
void* column_verifier(void* arg);

//Function that verifies the validity (output 1) of a sub_square or invalidity (output 0) or if the sub_sqaure is not complete, but still valid (output 2^i where i is the number of missing values)
void* sub_square_verifier(void* arg);

//Function that verifies if a given Sudoku is valid (lines, columns and a specific sub_square where a new element is inserted) in a multithread manner
long long unsigned int global_verifier(int sudoku[9][9], int row, int col);

//Function that verifies if a given Sudoku is valid (lines, columns and a specific sub_square where a new element is inserted) in a sequential manner
long long unsigned int global_verifier_sequential(int sudoku[9][9], int row, int col);

//Function that verifies if a complete Sudoku is valid in a multithread manner
long long unsigned int final_global_verifier(int sudoku[9][9]);

//Function that verifies if a complete Sudoku is valid in a sequential manner
long long unsigned int final_global_verifier_sequential(int sudoku[9][9]);

//Function that finds if there is or not an empty cell in the Sudoku matrix, if there is not it returns 0, if there is it returns 1 and the position of the empty cell
int find_next_empty_cell(int sudoku[9][9], int* row, int* column);

//Function that solves the Sudoku using a backtracking strategy. If multithread = 1, it uses parallel programming for the validation, if multithread = 0, the validation is sequential
int solve_sudoku(int sudoku[9][9], int multithread);

//Function that solves the Sudoku using a multithread backtracking and multithread verification strategy at the same time 
void* solve_sudoku_with_parallel_backtracking(void* sudoku_array_void);