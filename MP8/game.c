#include "game.h"
/*
    Introduction Paragraph:
    In this MP we remade 2048 to be playable in a terminal.
    In order for the game we had to complete a variety of functions
    so the game would work witht proper functionality. The first
    function that we made was a make game function that set up the board
    and initalized values for rows, cols and the score. The next function
    that we implemented was remake game which reinitalized old game data.
    We then completed the get_cell function which will return a pointer
    to a specfied cell in the board. The cell is specfied with inputted rows
    and columns. The next functions that we implemented dealt with user input.
    Depending on the direction that the user inputted, the board will move in
    that direction. This means that the values currently on the board will move
    to the highest possible position, and if they reach a cell equivalent in value
    then it will merge with that cell. The final function that we needed to implement
    was the legal move check. This function will check if there are any more moves that
    the user can make. This function will also consider the board filled if sliding in
    any direction will not change the state of the board, and the board is filled.
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

    mygame->rows = rows; //store the number of rows and columns
    mygame->cols = cols;
    mygame->score = 0; // set the intitall score to zero

    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
           mygame->cells[(i * cols) + j] = -1; //all cells will have the value of -1
        }
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	//YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows; // store the number of new rows and columns
    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->score = 0; // set the score to zero

    int i, j;
    for (i = 0; i < new_rows; i++) {
        for (j = 0; j < new_cols; j++) {
           (*_cur_game_ptr)->cells[(i * new_cols) + j] = -1; // set every cell to have the value of -1
        }
    }

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    // If the coords are in bounds
    if ((row < (cur_game->rows)) && (col < (cur_game->cols))) {
        // Return the address of the cell in memory
        return &(cur_game->cells[(row * (cur_game->cols)) + col]);
    }
    
    return NULL;
}

/* Takes an array of pointers and slides it to the higher end*/
int slide_array(cell* ptrsArray[], int len, int* score) {
    // Keep track of our return value 1 = Different 0 = Same
    int ret = 0;

    int i, j;
    // Loop through the values from high to low
    for (i = len - 1; i >= 0; i--) {
        // Find a value that isn't -1
        cell cur_val = *(ptrsArray[i]);
        if (cur_val != -1) {
            // Slide the tile:
            // Loop through the array from low to high
            for (j = i + 1; j < len; j++) {
                // Ran into something we can't slide into / merge with.
                if ((*ptrsArray[j]) != -1 && (*ptrsArray[j]) != cur_val) {
                    break;
                }

                // Ran into a -1, so we can slide to high.
                else if((*ptrsArray[j]) == -1) {
                    ret = 1;
                    (*ptrsArray[j-1] = -1);
                    (*ptrsArray[j]) = cur_val;
                }

                // Ran into a matching tile
                else if ((*ptrsArray[j]) == cur_val) {
                    ret = 1;
                    (*ptrsArray[j-1] = -1);
                    (*ptrsArray[j]) = cur_val * 2;
                    // udpate the score
                    *score += (cur_val * 2);

                }
            }
        }
    }
    return ret;
}


int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int len = (cur_game->rows);
    //printf("len:%d\n", len);

    // Allocate a block of memory to store our array
    // ptrsArray is a pointer to a group of memory that stores cell pointers
    cell** ptrsArray = (cell**) malloc(len * sizeof(cell**));
    int ret = 0;
    int i, j;
    //Loop over all the cols
    for (j = 0; j < (cur_game->cols); j++) {
        // Loop through the cols
        for (i = 0; i < len; i++) {
            ptrsArray[i] = get_cell(cur_game, (len-1)-i, j);
        }
        
        ret = ret | slide_array(ptrsArray, len, &cur_game->score);
    }
    free(ptrsArray);

    return ret;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int len = (cur_game->rows);
    //printf("len:%d\n", len);

    // Allocate a block of memory to store our array
    // ptrsArray is a pointer to a group of memory that stores cell pointers
    cell** ptrsArray = (cell**) malloc(len * sizeof(cell**));
    int ret = 0;
    int i, j;
    //Loop over all the cols
    for (j = 0; j < (cur_game->cols); j++) {
        // Loop through the cols
        for (i = 0; i < len; i++) {
            ptrsArray[i] = get_cell(cur_game, i, j);
        }

        ret = ret | slide_array(ptrsArray, len, &cur_game->score);
    }
    free(ptrsArray);
    return ret;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int len = (cur_game->cols);
    //printf("len:%d\n", len);

    // Allocate a block of memory to store our array
    // ptrsArray is a pointer to a group of memory that stores cell pointers
    cell** ptrsArray = (cell**) malloc(len * sizeof(cell**));

    // Int to keep track of whether the board changed or not. 1 = Different 0 = Same
    int ret = 0;

    int i, j;
    //Loop over all the rows
    for (i = 0; i < (cur_game->rows); i++) {
        // Loop through the rows
        for (j = 0; j < len; j++) {
            ptrsArray[j] = get_cell(cur_game, i, (len-1)-j);
        }
        
        ret = ret | slide_array(ptrsArray, len, &cur_game->score);
    }
    free(ptrsArray);

    return ret;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int len = (cur_game->cols);
    //printf("len:%d\n", len);

    // Allocate a block of memory to store our array
    // ptrsArray is a pointer to a group of memory that stores cell pointers
    cell** ptrsArray = (cell**) malloc(len * sizeof(cell**));

    int ret = 0;

    int i, j;
    //Loop over all the rows
    for (i = 0; i < (cur_game->rows); i++) {
        // Loop through the rows
        for (j = 0; j < len; j++) {
            ptrsArray[j] = get_cell(cur_game, i, j);
        }
        
        ret = ret | slide_array(ptrsArray, len, &cur_game->score);
        
    }
    free(ptrsArray);

    return ret;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int i, j, p, q;

    for (i = 0; i < cur_game->rows; i++) {
        for (j = 0; j < cur_game->cols; j++) {
            cell cur_val = (*get_cell(cur_game, i, j));
            // Check if the square is empty
            if (cur_val == -1) {
                return 1;
            }
            // Check adjacent squares
            
            // Check top 
            q = j;
            p = (0 > i - 1) ? 0 : i - 1;
            if (p != i) {
                if (cur_val == *get_cell(cur_game, p, q)) {
                    return 1;
                }
            }

            // Check bottom
            p = (cur_game->rows - 1 > i + 1) ? i + 1 : cur_game->rows - 1;
            if (p != i) {
                if (cur_val == *get_cell(cur_game, p, q)) {
                    return 1;
                }
            }

            // Check left
            p = i;
            q = (0 > j - 1) ? 0 : j - 1;
            if (q != j) {
                if (cur_val == *get_cell(cur_game, p, q)) {
                    return 1;
                } 
            }

            q = (cur_game->cols - 1 > j + 1) ? j + 1 : cur_game->cols - 1;
             if (q != j) {
                if (cur_val == *get_cell(cur_game, p, q)) {
                    return 1;
                } 
            }
        }
    }
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}