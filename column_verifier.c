//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"

//Function that verifies the validity (output 1) or invalidity (output 0) of columns or if the columns are not complete, but still valid (output 2)
void* column_verifier(void* arg){
	int i, j, result = 1;
	int* sudoku = arg;
	int* res = malloc(sizeof(int));

	//Hash for counting the presence (or absence) of elements in the columns
	int test_matrix[9][9] = {0};

	//Counting presence of elements in the columns and checking for validity
	for(i = 0; i < 9; i++){
		for(j =0; j < 9; j++){
			if(sudoku[j*9 + i] != nan)
				test_matrix[i][sudoku[j*9 + i] - 1]++;
		}
	}

	///This first loop tests if there is repetition of numbers in the coulmns of Sudoku
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(test_matrix[i][j] > 1){
				result = 0;
				*res = result;
				return (void *) res;
			}
		}
	}

	///This second loop tests if there are empty spaces in the coulmns of Sudoku
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(test_matrix[i][j] == nan){
				result = 2;
				*res = result;
				return (void *) res;
			}
		}
	}

		
	//Columns are valid and complete if result = 1
	result = 1;
	*res = result;

	return (void *) res;	
}