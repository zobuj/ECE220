# Introduction Paragraph

In this mp we first 3 functions to check if a certain value can be placed into the a specific cell.
The functions are to check if the value is not in another place in the row, column, or 3x3 zone it is located. 
We used iteration to loop through the row, column, and zone. Then we created a fourth function called is_val_valid 
that uses the 3 previous functions. If it is valid in the row, column, and zone then it is valid. The final function 
that we implemented was a solve sudoku function that uses the other functions that we implemented. This function 
uses a recursive backtracking algorithim that finds a correct value for each of the cells. This function calls 
the is value valid function to check if the value may be placed in that position in the board.
