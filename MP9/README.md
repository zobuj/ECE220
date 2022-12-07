# Introduction Paragraph: 
During this MP we worked coding a maze solver
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
