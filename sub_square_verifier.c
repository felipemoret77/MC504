//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"

//Function that verifies the validity (output 1) of a sub_square or invalidity (output 0) or if the sub_sqaure is not complete, but still valid (output 2^i where i is the number of missing values)
void* sub_square_verifier(void* arg){
	int i, j, result = 1;
	int* sudoku = ((Sudoku_And_Sub_Square_Number*) arg)->sudoku;
	int sub_square_number = ((Sudoku_And_Sub_Square_Number*) arg)->sub_square_number;
	int* res = malloc(sizeof(int));

	//Hash for counting the presence (or absence) of elements in the sub_square
	int test_vector[9] = {0,0,0,0,0,0,0,0,0};

	//Counting elements in the sub_square
	for(i = (sub_square_number/3)*3; i < (sub_square_number/3)*3 + 3; i++){
    	for(j = (sub_square_number%3)*3; j < (sub_square_number%3)*3 + 3; j++){
    		if(sudoku[i*9 +j] != nan)
    			test_vector[sudoku[i*9 +j] - 1]++;
    	}
    }


    //Checking if there are repeated numbers in the sub square
	for(j = 0; j < 9; j++){
		if(test_vector[j] > 1){
			result = 0;
			*res = result;
			return (void *) res;
		}
	}

	//Checking if there are missing numbers in the sub square
	for(j = 0; j < 9; j++){
		if(test_vector[j] == nan){
			//COde 2 means that there are missing values in the subquare but it is yet valid
			result = 2;
			*res = result;
			return (void *) res;
		}
	}

	//Code 1 means that there are no missing cells and the sub square is valid
	result = 1;
	*res = result;

	return (void *) res;	
}