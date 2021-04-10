//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"


//Simple function to duplicate a matrix
void copy_matrix(int matrix1[9][9], int matrix2[9][9]){
	int i, j;

	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			matrix1[i][j] = matrix2[i][j];
	}
	