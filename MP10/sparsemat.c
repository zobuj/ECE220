#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/*Introduction Paragraph: In this mp we wrote code for a data structure that
stores sparse matrices in a more efficient manner than 2D arrays. Sparse matricies
contain many elements with zeros, which wastes a lot of space storing all of those
zeros. It is more efficient to only store the nonzero entries. In order to manage
tuples, which contain information about the row, col, and value, we used a linked list.
The first function we implemented is a load tuples function that opens and reads data from a file.
Then it stores the data into a new matrix. The next function that we coded was the
set_tuples function that sets the element at a specific row and column to a specific value
It also needss to find the correct location for the node within the sorted linked list.
The next function that we needed to implement is the save tuples function that will write the data
in a sparse matrix structure to a file. The next function that we implemented was
the add tuples function which calculates A+B and stores each element into a C matrix.
However instead of just adding each element together, where there are many zeros, it is more
efficient to only add non-zero elements of A and B. Then it will store values into the C matrix.
The final function that we needed to implement is the destroy tuples function which will
release all the memory with any given matrix. 

*/
//Partners: pjj3, xrouth2


sp_tuples * load_tuples(char* input_file)
{
    // Allocate space for our matrix.
    sp_tuples *matrix = (sp_tuples*) malloc(sizeof(sp_tuples));

    // Open the file
    FILE* file = fopen(input_file, "r");
    
    //declared variables for the row, col, and value
    int row, col;
    double value;
    //scanning the file to take the inputs for the size of the matrix
    fscanf(file, "%d %d\n", &(matrix->m), &(matrix->n));
    //initally sets the number of nonzero values in the matrix to zero
    matrix->nz = 0;
    matrix->tuples_head = NULL;
    //iterates through the file taking in data for each of the values
    while (fscanf(file, "%d %d %lf\n", &row, &col, &value) != EOF) {
        set_tuples(matrix, row, col, value);
    }
    //closes the flie and returns the matrix
    fclose(file);
    return matrix;
}


/*
 * gv_tuples -- Takes a matrix and a corresponding location and gets the value at that location.
 *
 * 
 */
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node* curr = mat_t->tuples_head; //points to the head of the list

    int destLocation = (row * mat_t->n) + col; //calculates the needed location
    int currLocation;//present location

    while (curr != NULL) {
        currLocation = (curr->row * mat_t->n) + curr->col;//calculates the present location
        //if the destination location is equal to the current location then we return the value
        if (currLocation == destLocation) { 
            return curr->value;
        }//if not then it will move on to the next value
        curr = curr->next;
    }
    return 0;
}


/*
 * set_tuples -- Takes a matrix and a corresponding row, col and value and inserts 
 *               a new node into the correct position in the linked list
 * INPUTS:       mat_t - A pointer to a matrix on which we insert a value / node.
 *               row, col - The location of the value to be inserted
 *               value - The value
 */
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    // If the requested space is out of bounds, do nothing
    if ((row >= mat_t->m) || (col >= mat_t->n)){
        return;
    }
    // If the matrix is empty, then add a new node to the front of the list.
    if ((mat_t->tuples_head == NULL) && (value != 0)) {
        mat_t->tuples_head = insertNode(NULL, row, col, value);
        mat_t->nz++;
        return;
    }

    // Initialize node pointers for current and next nodes
    sp_tuples_node* curr = mat_t->tuples_head;
    sp_tuples_node* next = curr->next;

    int destLocation = (row * mat_t->n) + col;
    int currLocation = (curr->row * mat_t->n) + curr->col;
    int nextLocation;

    // Node belongs at the beginning of the list
    if ((destLocation < currLocation) && (value != 0)) {
        mat_t->tuples_head = insertNode(curr, row, col, value);
        mat_t->nz++;
        return;
    }
    // Loop through the list until we find the correct position in row major order
    while (curr->next != NULL) {
        // Look ahead in the linked list
        currLocation = (curr->row * mat_t->n) + curr->col;
        nextLocation = (next->row * mat_t->n) + next->col;

        // If the location already is filled
        if (nextLocation == destLocation) {
            // Delete the node
            if (value == 0) {
                curr->next = next->next;
                free(next);
                mat_t->nz--;
            }
            // Fill the node with the correct value
            else {
                next->value = value;
            }
            return;
        }
        // If we want to place a node in between this node and the next node
        if ((currLocation < destLocation) && (destLocation < nextLocation)) {
            // We found our location to insert the node
            // Insert a new node inbetween the two locations
            curr->next = insertNode(next, row, col, value);
            mat_t->nz++;
            return;
        }
        // Move forward in the linked list
        curr = next;
        next = curr->next;
    }
    // We got to the end of the list without breaking.
    if (value != 0) {
        curr->next = insertNode(NULL, row, col, value);
        mat_t->nz++;
    }
    
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* file = fopen(file_name, "w");//opens the file to write into it
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);//prints the number of rows and cols
    if (mat_t->tuples_head == NULL){//if the end of the list is reached then return nothing
        return;
    }
    sp_tuples_node* curr = mat_t->tuples_head;
    
    while (curr != NULL) {
        //print into the file the row, col, and value
        fprintf(file, "%d %d %lf\n", curr->row, curr->col, curr->value);

        curr = curr->next;// move to the next value
    }

    fclose(file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

    if ((matA->tuples_head == NULL) || (matB->tuples_head == NULL)){
        return NULL;
    }
    if ((matA->n != matB->n) || (matA->m != matB->m)) {
        return NULL;
    }

    sp_tuples* matC = (sp_tuples*) malloc(sizeof(sp_tuples));
    //setting the size of the of matrix C and setting the number of nonzero entries to zero
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
    //declare the value
    double value;

    sp_tuples_node* curr = matA->tuples_head;

    // Loop through A and copy A to C
    while (curr != NULL) {
        set_tuples(matC, curr->row, curr->col, curr->value);
        curr = curr->next;
    }
    //loop through B and copy B to C
    curr = matB->tuples_head;
    while (curr != NULL) {
        value = curr->value + gv_tuples(matC, curr->row, curr->col);
        set_tuples(matC, curr->row, curr->col, value);
        curr = curr->next;
    }
    
	return matC;//returns matrix C
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL;

}



//frees all memory associated with the given matrix	
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node* curr = mat_t->tuples_head;
    if (mat_t == NULL) {//if the matrix is empty then return
        return;
    }
    if (mat_t->tuples_head == NULL) {//condition for the final value in the list
        free(mat_t);
        return;
    }

    sp_tuples_node* next = curr->next;
    //while it is not null move to the next value and free that value, then iterate to the next value
	while (next != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(mat_t);
    return;
}  
//Helper function to insert nodes in the list
sp_tuples_node * insertNode(sp_tuples_node* next, int row, int col, double value) {
    sp_tuples_node* node = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
    node->next = next;
    node->value = value;
    node->row = row;
    node->col = col;
    return node;
}


