/*
 * In this MP I worked on coding the "Game of Life". This game
 * is one which is made up of a grid of square cells that are in
 * two possible states, alive or dead. I started by coding the
 * countLiveNeighbor function which counts the number of number 
 * live cells. This number is required for this function, since
 * the code works in a way that it transitions through generations.
 * The cells change from alive to dead depending on the number of
 * alive cells in the eight cells that surround each cell. In the 
 * next function we implemented, updateBoard, we updated the board
 * with every new generation. The board was changed depending on 
 * number of alive cells located in the eight surrounding cells, of
 * a given cell. This function called the countLiveNeighbor to 
 * find the number of live cells. The parameters for keeping the 
 * cell alive (represented as a 1) and changing it to be dead 
 * (represented as a 0) were implemented in this function. 
 * The final function that I implemented in this code is one 
 * that checks the board, to see if the code is ready to terminate 
 * (which depends on whether or not the board will change in the 
 * next generation). This function compares the next board to the 
 * current board, and if it changes then a new board will be printed. 
 * If the next board is the same as the current board then the 
 * program will end. In order to find the next board, this function
 * uses the updateBoard function. 
 *  
 * 
 * partners: pjj3, xrouth2
 */
// Define helper macros
#define onBoard(row, col) (row < boardRowSize) && (row >= 0) && (col < boardColSize) && (col >= 0)
#define gameBoard(row, col) board[(row * boardColSize) + col]

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

    // Initialize ints for our function.
    int liveNeighbors = 0;
    int currRow = row;
    int currCol = col;

    // Loop through the adjacent rows
    for(currRow = row - 1; currRow <= row + 1; currRow++) {
        // Loop through the adjacent columns
        for (currCol = col - 1; currCol <= col + 1; currCol++) {
            // Check if the space is actually on the board
            if (onBoard(currRow, currCol)){
                // If it isn't the same as our current space
                if (!((currRow == row) && (currCol == col))) {
                    // The current cell is alive
                    if (gameBoard(currRow, currCol) == 1) {
                        // Increment live neighbors
                        liveNeighbors++;
                    }
                }
            }
        }
    }
    return liveNeighbors;
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {

    // Create a temp board
    int nextBoard[boardColSize*boardRowSize];
    int currRow = 0;
    int currCol = 0;

    // Loop through each cell
    // Store our results in nextBoard, so we don't accidently 
    // edit the board before we loop through it all
    for(currRow = 0; currRow < boardRowSize; currRow++ ) {
        for (currCol = 0; currCol < boardColSize; currCol++) {

            // Get the amount of live neighbors for our current cell
            int liveNeighbors = countLiveNeighbor(board, boardRowSize, boardColSize, currRow, currCol);

            // If the cell is alive
            if (gameBoard(currRow, currCol) == 1) {
                // Set the cell in nextBoard to be alive also, we can correct this later
                nextBoard[(currRow * boardColSize) + currCol] = 1;
                // If it has two or three live neighbors, it continues to live
                if ((liveNeighbors == 2) || (liveNeighbors == 3)) {
                    continue;
                }
                else {
                    // If it doesn't have two or three live neighbors, it dies.
                    nextBoard[(currRow * boardColSize) + currCol] = 0;
                }
            }
            // The cell is dead
            else {
                // Set the cell in nextBoard to be dead also, we can correct this later
                nextBoard[(currRow * boardColSize) + currCol] = 0;
                if (liveNeighbors == 3) {
                // If it has three live neighbors, make it alive.
                    nextBoard[(currRow * boardColSize) + currCol] = 1;
                }
            }
        }
    }

    // Loop through both boards and copy nextBoard into board
    int i;
    for(i = 0; i < (boardColSize * boardRowSize); i++ ) {
        board[i] = nextBoard[i];
    }

    // In theory, just changing the pointer should be enough to change the whole board
    // I think the memory locations of nextBoard get de-allocated when the function ends, 
    // which is why this doesn't actually work.
    // board = nextBoard;
    // Maybe there is a way to save the memory so this works, i think it should work
    // Maybe an OH question.
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){

    // Create an array to store the values that will be in the next state.
    int nextBoard[boardRowSize * boardColSize];

    // Copy the current values into the board we will use for next board.
    int i;
    for(i = 0; i < (boardColSize * boardRowSize); i++ ) {
        nextBoard[i] = board[i];
    }

    // Calculate the values of the next state
    updateBoard(nextBoard, boardRowSize, boardColSize);

    // Loop through and compare both boards, and if they are different in any way, 
    // we do not have a stable state
    for(i = 0; i < (boardColSize * boardRowSize); i++ ) {
        // If they are different in any way
        if (nextBoard[i] != board[i]) {
            // Not a stable state
            return 0;
        }
    }

    // board and nextBoard are the same, so the state is stable
    return 1;
}

				
				
			
