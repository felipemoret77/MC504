//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"

int give_square_by_cell_position(int i, int j){

	if(i < 3){
		if(j < 3)
			return 0;
		if(j < 6)
			return 1;
		return 2; 
	}

	if(i < 6){
		if(j < 3)
			return 3;
		if(j < 6)
			return 4;
		return 5; 
	}

	if(j < 3)
		return 6;
	if(j < 6)
		return 7;
	return 8; 

}