main_solver: main.c copy_matrix.c give_square_by_cell_position.c line_verifier.c column_verifier.c sub_square_verifier.c global_verifier.c global_verifier_sequential.c final_global_verifier.c final_global_verifier_sequential.c find_next_empty_cell.c solve_sudoku.c solve_sudoku_with_parallel_backtracking.c
	gcc -o main_solver main.c copy_matrix.c give_square_by_cell_position.c line_verifier.c column_verifier.c sub_square_verifier.c global_verifier.c global_verifier_sequential.c final_global_verifier.c final_global_verifier_sequential.c find_next_empty_cell.c solve_sudoku.c solve_sudoku_with_parallel_backtracking.c -I.


