//MC504 - 1s2021 - Projeto 01 - Solução do Sudoku usando multiplas threads
//Aluno: Felipe Bueno Moret, RA: 155297

#include "header_sudoku.h"

long long unsigned int global_verifier_sequential(int sudoku[9][9], int row, int col){

	int i;
	long long unsigned int final_result = 1;


	//This struct pass the sudoku  matrix and a sub_square number for the responsible thread, sub_quares are numerated from 0 to 8
	struct Sudoku_And_Sub_Square_Number sub_square;

	//Generating the right sub_square

	sub_square.sudoku = (int *)sudoku;
	sub_square.sub_square_number =  give_square_by_cell_position(row, col);
	

	//Variable for storing result of validity of the sub_squares
    int* res_sub_square;
    //Variable for storing the result of validity of the lines
    int* res_lines;
    //Variable for storing the result of validity of the columns
    int* res_columns;

    //Threads for verifying the correspondent sub_square 3x3
    pthread_t sub_square_thread;
    //Thread for verifying all the lines
	pthread_t line_verifier_thread;
	//Thread for verifying all the columns
	pthread_t column_verifier_thread;

	if (pthread_create(&line_verifier_thread, NULL, &line_verifier, (void *) sudoku) != 0)
			perror("Failed to create thread\n");

	//Waiting the end of execution of the threads that are responsible for validating the lines of the Sudoku
	if (pthread_join(line_verifier_thread, (void **) &res_lines) != 0)
		perror("Failed to create thread\n");

	if (pthread_create(&column_verifier_thread, NULL, &column_verifier, (void *) sudoku) != 0)
			perror("Failed to create thread\n");

	//Waiting the end of execution of the threads that are responsible for validating the coulmns of the Sudoku
	if (pthread_join(column_verifier_thread, (void **) &res_columns) != 0)
		perror("Failed to create thread\n");


	if (pthread_create(&sub_square_thread, NULL, &sub_square_verifier, (void *) &sub_square) != 0)
			perror("Failed to create thread\n");
	

	//Waiting the end of execution of the thread that is responsible for validating the correspondent sub_squares 
	if (pthread_join(sub_square_thread, (void **) &res_sub_square) != 0)
			perror("Failed to create thread\n");	
	

	//Final result/validation of the  sub_square 3x3
	final_result *= *res_sub_square;

	//Incorporating lines validation 
	final_result *= *res_lines;
	//Incorporating columns validation 
	final_result *= *res_columns;
	

	//Deallocating dynamic memory
	free(res_sub_square);
	free(res_lines);
	free(res_columns);

	return final_result;
}