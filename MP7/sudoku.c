#include "sudoku.h"

/*
In this mp we first 3 functions to check if a certain value can be placed into the a specific cell.
The functions are to check if the value is not in another place in the row, column, or 3x3 zone it is located. 
We used iteration to loop through the row, column, and zone. Then we created a fourth function called is_val_valid 
that uses the 3 previous functions. If it is valid in the row, column, and zone then it is valid. The final function 
that we implemented was a solve sudoku function that uses the other functions that we implemented. This function 
uses a recursive backtracking algorithim that finds a correct value for each of the cells. This function calls 
the is value valid function to check if the value may be placed in that position in the board.
 */

//-------------------------------------------------------------------------------------------------

// Start here to work on your MP7

//-------------------------------------------------------------------------------------------------

//partners: pjj3, xrouth2

// You are free to declare any private functions if needed.



// Function: is_val_in_row

// Return true if "val" already existed in ith row of array sudoku.



int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {



  assert(i>=0 && i<9);



  // BEG TODO

  for (int j = 0; j < 9; j++) { // this for loop iterates through the row of the board

    if (sudoku[i][j] == val) { // if the declared value is equivalent to the current value in the row

      return 1; //then the function will return 1, meaning the value is in fact present in the row

    }

  }

  

  return 0; //the function will return 0 if the value is not present in the row

  // END TODO

}



// Function: is_val_in_col

// Return true if "val" already existed in jth column of array sudoku.



int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {



  assert(j>=0 && j<9);



  // BEG TODO

  for (int i = 0; i < 9; i++) { //this for loop iterates through the column of the board

    if (sudoku[i][j] == val) { //if the declared value is equivalent to the current value in the column

      return 1; //then the value is in fact present in the column

    }

  }

  

  return 0; //the function will return 0 if the value is not present in the row

  // END TODO

}



// Function: is_val_in_3x3_zone

// Return true if val already existed in the 3x3 zone corresponding to (i, j)

int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

   

  assert(i>=0 && i<9);

  

  // BEG TODO



  // Calculate what zone it is in.

  int start_i, start_j;

// these two calculations will find the start position in the board for the loop

  start_i = i - (i % 3);  

  start_j = j - (j % 3);



  for (int p = start_i; p < (start_i  + 3); p++) { //this outer loop iterates through the columns of the 3 x 3 zone

    for (int q = start_j; q < (start_j + 3); q++) { // this inner loop iterates through the rows of the 3 x 3 zone

        if (sudoku[p][q] == val) { // if the declared value is equivalent to the value in the current position in the 3 x 3 zone

          return 1; // then it will return 1, which means the value was in fact present in the 3 x 3 zone 

        }

    }

  }



  return 0; // it will return 0, if it not present in the zone

  // END TODO

}



// Function: is_val_valid

// Return true if the val is can be filled in the given entry.



int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

     

  assert(i>=0 && i<9 && j>=0 && j<9);



  // BEG TODO

//this for loop will check if the either the value is in the 3 x 3 zone, or in the column, or in the row of the board. If any of these values are true then the value is not valid, that same value may not be inputted again in the zone, the column or the row that it is located.

  if ((is_val_in_3x3_zone(val, i, j, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_row(val, i, sudoku))) {

    return 0;

  } 

  return 1; // the function will return 1 if the value is valid, which means that the value is neither in the zone, the column or the row

  // END TODO

}



// Procedure: solve_sudoku

// Solve the given sudoku instance.

//This function will utilize each of the functions created above to solve the entire sudoku board.

int solve_sudoku(int sudoku[9][9]) {



  // BEG TODO.

//These two loops will check if the all of the cells to see if they have numbers
  int i = 0;
  int j = 0;
  for (i = 0; i < 9; i++) {

    if (i == 9) {

      printf("%d",i);

    }

    for (j = 0; j < 9; j++) {

      if (j == 9) {

        printf("%d",j);

      } 

      if (sudoku[i][j] == 0) { // if the value in the cell is zero then it will go to a skip to a part in the function that will fill the cell with a number

        goto exit;

      }

    }

  }



  

  exit: //algorithm to find a number that is valid to place in the cell
  
  if (i == 9 && j == 9) {

    return 1;

  }

  for (int num = 1; num <= 9; num++) { //this loop iterates through all of the possibilities of numbers to go into the cell

    

    if (is_val_valid(num, i, j, sudoku)) {// this if statement will check if the current number in the loop is valid to be placed in the cell

      sudoku[i][j] = num; // this will set the place on the board to the value in the loop

      if (solve_sudoku(sudoku)) { 

        return 1; // if the board is solved then the recursive loop will end

      }

      sudoku[i][j] = 0; // will fill the cell with zero if it was not filled

    }

  }



  return 0;

  // END TODO.

}



// Procedure: print_sudoku

void print_sudoku(int sudoku[9][9])

{

  int i, j;

  for(i=0; i<9; i++) {

    for(j=0; j<9; j++) {

      printf("%2d", sudoku[i][j]);

    }

    printf("\n");

  }

}



// Procedure: parse_sudoku

void parse_sudoku(const char fpath[], int sudoku[9][9]) {

  FILE *reader = fopen(fpath, "r");

  assert(reader != NULL);

  int i, j;

  for(i=0; i<9; i++) {

    for(j=0; j<9; j++) {

      fscanf(reader, "%d", &sudoku[i][j]);

    }

  }

  fclose(reader);

}