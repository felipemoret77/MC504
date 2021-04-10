//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"

int find_next_empty_cell(int sudoku[9][9], int* row, int* column){
	int i,j;

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(sudoku[i][j] == nan){
				*row = i;
				*column = j;
				return 1;
			}
		}
	}
	return 0;
}