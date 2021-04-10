//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"

void* solve_sudoku_with_parallel_backtracking(void* sudoku_array_void){
	int is_valid, is_incomplete;
	int i, j, k, number;
	int* copies_of_sudoku[9];
	int* is_solved_parallel[9];
	int* is_solved = malloc(sizeof(int));
	int sudoku_matrix[9][9];
	int row, column;
	int* sudoku_array;
	int created_threads[9] = {0};

	sudoku_array = (int *) sudoku_array_void;


	pthread_t backtracking_answers[9];

	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			sudoku_matrix[i][j] = sudoku_array[9*i + j];


	is_incomplete = find_next_empty_cell(sudoku_matrix, &row, &column);
	if(!is_incomplete){
		is_valid = final_global_verifier(sudoku_matrix);
			if(is_valid == 1){
				*is_solved = 1;
				printf("There is a solution :)!\n\n");
				printf("The solution is:\n\n");
				for(i = 0; i < 9; i++){
					for(j = 0; j < 9; j++)
						printf(" %d", sudoku_matrix[i][j]);
					printf("\n");
				}
				return (void *) is_solved;
			}
			else{
				*is_solved = 0;
				return (void *) is_solved;
			}
		}

		for(i = 0; i < 9; i++){
			is_solved_parallel[i] = malloc(sizeof(int));
			copies_of_sudoku[i] = malloc(81*sizeof(int));
		}

		for(i = 0; i < 9; i++)
			*is_solved_parallel[i] = 0;

	
		for(k = 0; k < 9; k++){
			for(i = 0; i < 9; i++){
				for(j = 0; j < 9; j++)
					copies_of_sudoku[k][9*i + j] = sudoku_matrix[i][j];
			}
		}
	
		for(number = 1; number <= 9; number++){
				sudoku_matrix[row][column] = number;
				if(global_verifier(sudoku_matrix, row, column)){
					copies_of_sudoku[number-1][9*row + column] = number;
					if (pthread_create(&backtracking_answers[number-1], NULL, &solve_sudoku_with_parallel_backtracking, (void *) copies_of_sudoku[number-1]) != 0)
						perror("Failed to create thread\n");
					else{
						created_threads[number-1] = 1;
					}
				}
			}
				
		for(i = 0; i < 9; i++){
			if(created_threads[i]){
				if (pthread_join(backtracking_answers[i], (void **) &is_solved_parallel[i]) != 0)
					perror("Failed to create thread\n");
				else{
					if(* (int*)is_solved_parallel[i] == 1){
						*is_solved = 1;
						return (void *) is_solved;
					}
				}
			}
		}
					
		for(i = 0; i < 9; i++)
			free(is_solved_parallel[i]);
		for(i = 0; i < 9; i++)
			free(copies_of_sudoku[i]);
				
			
	return (void *) is_solved;
}