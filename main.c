//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

/*This is the main function. You can give a Sudoku Matrix with empty cell represented by 'nan' or equivalently by zeros. The variable 'multithread' decides if you want to 
do a verfication of the Sudoku Matrix in a parallel way or in a sequential way. Finally, when you activate (=1) the variable 'parallel_backtracking' the algorithm will 
do a parallel backtracking and also a parallel verification of the Sudoku constraints.
*/

#include "header_sudoku.h"
	
int main(){
	int i, j, is_there_solution, multithread = 0, parallel_backtracking = 1;
	clock_t tic, toc;

	//Sudoku is a 9x9 matrix where 'nan' means missing value
	int sudoku[9][9] = {{7,2,6,4,9,3,nan,nan,nan},
						{3,1,5,7,2,8,9,4,6},
						{4,8,9,6,5,1,2,3,7},
						{8,5,2,1,4,7,6,9,3},
						{6,7,3,9,8,5,1,2,4},
						{9,4,1,3,6,2,7,5,8},
						{1,9,4,8,3,6,5,7,2},
						{5,6,7,2,1,4,3,8,9},
						{2,3,8,5,7,9,4,6,1}};



	printf("HELLO TO THE SUDOKU SOLVER!\n\n");
	printf("We inform that 0s are empty spaces in the sudoku!\n\n");
	printf("The initial incomplete Sudoku is:\n\n");

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++)
			printf(" %d", sudoku[i][j]);
		printf("\n");
	}

	printf("\n\n");


	if(parallel_backtracking){
		tic = clock();
		is_there_solution =  * (int*)solve_sudoku_with_parallel_backtracking(sudoku);
		toc = clock();

		if(is_there_solution){
			printf("\n\n");
			printf("For solving this funny puzzle with backtracking and verification using multithreads we have spent: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);
		}
		else
			printf("There is not a solurtion :(\n");

	}
		
	else{
			tic = clock();
			is_there_solution =  solve_sudoku(sudoku, multithread);
			toc = clock();
		}
	

	if(!parallel_backtracking){

		if(is_there_solution)
			printf("There is a solution :)!\n\n");
		else
			printf("There is not a solurtion :(\n");
		
		if(is_there_solution){
			printf("The solution is:\n\n");

			for(i = 0; i < 9; i++){
				for(j = 0; j < 9; j++)
					printf(" %d", sudoku[i][j]);
				printf("\n");
			}
		
			printf("\n\n");
			if(multithread)
				printf("For solving this funny puzzle with only verification using multithreads we have spent: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);
			else
				printf("For solving this funny puzzle with sequential execution we have spent: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);
		}
	}
	
	return 0;
}
