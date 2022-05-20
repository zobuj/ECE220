#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
Introduction Paragraph: During this MP we worked coding a maze solver
using a recursive depth first search. A solution to the maze would be found
when we started at S and ended at E, moving only up down left and right, and only
through the white spaces. Any space that we visit but does not lead to a solution
will also be marked so that we don't visit them again when we backtrack.
The four functions that we implemented in this MP create the maze, destroy the maze,
print the maze, and solve the maze using the recursive DFS algorithm. Making the maze incorporated allocating memory for the maze, and using file I/O
functions to access a file to retrieve information about the maze. Destroying the 
maze incorporated releasing all of the memory that we allocated for the maze when
when making the maze. Then we printed the maze by making the print maze function. The final
function that we made was the solveMazeDFS function which first checks if the cell is valid
by calling a helper function to see if the cell is within bounds, and checks if the cell
is already visited or a wall. After checking if the cell is valid it will use a base case to
end the recursive calls, which is when we reached the END position in the maze. Then we started the
recursion by setting the current cell we are on as part of the solution path, then trying to move
above, to the right, to the left, and below the cell. It will call the solveMazeDFS function with an
offset for each of the respective directions. If there is no solution for any direction from the current
cell, then we declare the current cell as visited and mark it with a character. We then can find the
solution to the maze.
*/
//Partners: pjj3, xrouth2
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Allocate memory for maze pointer
    maze_t* maze = (maze_t*) malloc(sizeof(maze_t));
    // Open file in read mode
    FILE* mazeFile = fopen(fileName, "r");
    // Read the first line to get width and height
    fscanf(mazeFile, "%d%d\n", &(maze->width), &(maze->height));

    // Initialize array of rows
    maze->cells = (char**) malloc(maze->height * sizeof(char*));
    int i, j;
    char c;
    // Loop over rows
    for (i = 0; i < maze->height; i++) {
        // Initialize memory to store each row
        maze->cells[i] = (char*) malloc(maze->width * sizeof(char));
        // Loop through rows
        for(j = 0; j < maze->width; j++) {
            c = fgetc(mazeFile);
            maze->cells[i][j] = c;
            if (c == START){
                maze->startRow = i;
                maze->startColumn = j;
            }
            if (c == END) {
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        // Get rid of newline
        fgetc(mazeFile);
    }
    // Close the file
    fclose(mazeFile);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    // Free each row
    for(i = 0; i < maze->height; i++) {
        free(maze->cells[i]);
    }
    // Free 1st col
    free(maze->cells);
    // Free all the members / attributes
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i;
    //printf("%d %d\n", maze->width, maze->height);
    // Print the first n characters of an array, where n is our width.
    for(i = 0; i < maze->height; i++) {
        printf("%.*s\n", maze->width, maze->cells[i]);
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Base case

    if (isCellValid(maze, col, row) == 0) {
        return 0;
    }
    
    if (maze->cells[row][col] == END) {
        return 1;
    }
    
    
    // We have a valid cell

    // Mark the cell as part of our current solution path
    if (maze->cells[row][col] != START) {
        maze->cells[row][col] = PATH;
    }
    

    // Now find the next cell that is part of our solution
    // Try above
    if (solveMazeDFS(maze, col, row-1)) return 1;
    // Try right
    if (solveMazeDFS(maze, col+1, row)) return 1;
    // Try down
    if (solveMazeDFS(maze, col, row+1)) return 1; 
    // Try left
    if (solveMazeDFS(maze, col-1, row)) return 1;

    // No neighboring cells led to a solution, so this cell must not be part of a solution.
    if (maze->cells[row][col] != START) {
        maze->cells[row][col] = VISITED;
    }
    return 0;
   
}

/*
 * isCellValid -- Calculates whether a given position is out of bounds or is not an empty cell          
 * INPUTS:     maze -- pointer to maze structure with all necessary maze information
 *             col -- the column of the cell within the maze
 *             row -- the row of the cell within the maze
 * 
 * RETURNS:    1 if the cell is valid, 0 if it is not.
 */
int isCellValid(maze_t * maze, int col, int row) {
    // Check if out of bounds
    if ((row >= maze->height) || (row < 0) || (col < 0) || (col >= maze->width)) {
        return 0;
    }
    char c = maze->cells[row][col];
    // Cell is already visited or is a wall
    if ((c == VISITED) || (c == PATH) || (c == WALL)) {
        return 0;
    }
    return 1;
    

}