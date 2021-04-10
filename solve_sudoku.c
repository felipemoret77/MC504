//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"

int solve_sudoku(int sudoku[9][9], int multithread){
	int is_solved = 0, is_valid, is_incomplete;
	int i, j, number;
	int row, column;

	is_incomplete = find_next_empty_cell(sudoku, &row, &column);
	if(!is_incomplete){
		if(multithread){
			is_valid = final_global_verifier(sudoku);
			if(is_valid == 1)
				return 1;
			else
				return 0;
		}
		else{
			is_valid = final_global_verifier_sequential(sudoku);
			if(is_valid == 1)
				return 1;
			else
				return 0;
		}
	}
	
	//Loop that tries to fill incomplete cells with numbers from 1 to 9
	for(number = 1; number <= 9; number++){
		sudoku[row][column] = number;
		if(multithread){
			if(global_verifier(sudoku, row, column)){
				is_solved = solve_sudoku(sudoku, multithread);
				if(is_solved)
					break;
			}
		}
		else{
			if(global_verifier_sequential(sudoku, row, column)){
				is_solved = solve_sudoku(sudoku, multithread);
				if(is_solved)
					break;
			}
		}
		
		sudoku[row][column] = nan;
	}
	return is_solved;
}