/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */
/*
In this program, I coded three functions in order to run the codebreaker game. 
I first coded the set_seed function that will take an input as a array of characters. 
The function will check the the validity of the input by checking if there is one 
integer number in the string, using the sscanf function. If the string is valid it will 
use the srand function to generate a seed that is used to generate the four solutions. 
If the string is not valid then it will print out an error message and return 0.

The next function that I implemented was the start_game function. In this function 
I had to generate each of the solution values that the user will attempt to guess. 
In order to compute those values we had to first use the rand function to create a 
random number, in the range that we set by modding the function by 8 and adding one 
(range would be 1-8). I set a random number for each of the 4 solution values. Then 
I set the value of the starting guess. Then I copied the random value into static 
solution variables which will be used to implement the make_guess function.

The next function that I implemented was the make guess function which would check the 
validity of the guess first. If the guess was not valid, it would print out a error message. 
If the guess was indeed valid then the function could check how many perfect and misplaced 
matches were in the guess. Then the function would print out how many perfect and misplaced 
matches were in the guess. First of all, to check the validity of the guess I made sure the 
guess had 4 integers all in the 1 to 8 range, and that there were no other inputs than integers. 
This validity is checked using the sscanf function and using the inputs of the user guess. 
These inputs were copied to the pointers one, two, three, and four. These pointers are used 
to be compared to the solution variables, to determine if they are perfect matches, misplaced 
matches, or nothing. In order to check the number of perfect matches, I created four if 
statements that will check if the value that was inputted by the user is equal to the value 
of the solution at that position. If it is then it is a perfect match and it will increment 
the number of perfect matches. This if statement will also state that if the input is equal 
to the solution then there is a perfect match and will be paired. In order to find the number 
of misplaced matches, I will check if the user input value is located in a different position 
in the solution. In order to do this I compared the value of each input to all of the solution 
values except the one it corresponds to. If it finds that it is equal then it will increment 
the value for the misplaced matches. I also had to make sure that the input isn't already paired. 
If it wasn't paired then, I can check if the value is located in a different position in the 
solution. Now I had the values for the perfect and the misplaced matches. I then printed the 
statement with the number of perfect and misplaced matches in the input to the user. 
This information will let the user make a better guess. 
*/


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
  int seed;
  char post[2];
  int is_valid = sscanf(seed_str, "%d%1s", &seed, post);//checks if the inputted string has only one integer
  if(is_valid==1){
    srand(seed);//sets the seed for the random numbers generated in the start_game function
    return 1;//returns 1 if the string is valid
  }else{
    printf("set_seed: invalid seed\n");// if the string is not valid then, it will print out this error message
    return 0;
  }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
  *one = rand() % 8 + 1;// each of these will use the rand function to generate a random number for each fothe numbers in the solution
  *two = rand() % 8 + 1; // the rand function is modded by 8 and added by 1 to make the range from 1 to 8
  *three = rand() % 8 + 1;
  *four = rand() % 8 + 1;
  guess_number = 1;// sets the starting guess
  solution1 = *one; //the next four lines copy the random computed value into each respective solution variable, which is used later on to implement make guess
   solution2 = *two;
   solution3 = *three;
   solution4 = *four;
   
  
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
  char post[2];
  int w,x,y,z;//these are the inputs from the user
  int is_valid = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);//checks how many integers are read in the input
  if(is_valid == 4 && w>=1 && w<=8 && x>=1 && x<=8 && y>=1 && y<=8 && z>=1 && z<=8){//checks the validity of the input, by also checking the input lands in the required range.
    int perfect_matches=0;//initalizing the number of perfect matches
    int misplaced_matches=0;//initalizing the number of misplaced matches
    int one_paired, two_paired, three_paired, four_paired = 0;//this variable will store the information on whether the the input is the same value as the solution value for that position in the input. This variable is used to compute the perfect and misplaced matches.
    *one = w;//the next four lines store the data inputted from the user into the parameter variables which will be used to compare to the solution value to determine if the value is in the correct position or in a certain position in the solution. 
     *two = x;
     *three = y;
     *four = z;
     //the next four if statements will check if the value that was inputted by the user is equal to the value of the solution at that position. if it is then it is a perfect match and it will increment the number of perfect matches. This if statement will also state that if the input is equal to the solution then there is a perfect match and will be paired.
     if(*one == solution1){
       perfect_matches++;
       one_paired = 1;
       
     }
     if(*two == solution2){
       perfect_matches++;
       two_paired = 1;
       
     }
     if(*three == solution3){
       perfect_matches++;
       three_paired = 1;
       
     }
     if(*four == solution4){
       perfect_matches++;
       four_paired = 1;
       
     }
     //Checking for misplaced matches
     //These will check if the user input value is located in a different position in the solution. In order to do this I compared the value of each input to all of the solution values except the one it corresponds to. If it finds that it is equal then it will increment the value for the misplaced matches. I also had to make sure that the input isn't already paired. If it wasn't paired then, I can check if the value is located in a different position in the solution.
     //first guess
     if(one_paired != 1){
       if(two_paired != 1 && *one == solution2){
	 misplaced_matches++;	
       }
       else if(three_paired != 1 && *one == solution3){
	 misplaced_matches++;	 
       }
       else if(four_paired != 1 && *one == solution4){
	 misplaced_matches++;	 
       }       
     }
     //second guess
     if(two_paired != 1){
       if(one_paired != 1 && *two == solution1){
	 misplaced_matches++; 
       }
       else if(three_paired != 1 && *two == solution3){
	 misplaced_matches++;	 
       }
       else if(four_paired != 1 && *two == solution4){
	 misplaced_matches++;
       }       
     }
     //third guess
     if(three_paired != 1){
       if(two_paired != 1 && *three == solution2){
	 misplaced_matches++;
       }
       else if(one_paired != 1 && *three == solution1){
	 misplaced_matches++;
       }
       else if(four_paired != 1 && *three == solution4){
	 misplaced_matches++;
       }       
     }
     //fourth guess
     if(four_paired != 1){
       if(two_paired != 1 && *four == solution2){
	 misplaced_matches++;
       }
       else if(three_paired != 1 && *four == solution3){
	 misplaced_matches++;
       }
       else if(one_paired != 1 && *four == solution1){
	 misplaced_matches++;
       }       
     }
     printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_matches, misplaced_matches);//This is the output that the user will see after each time they enter an input. This information will allow for the user to make a better guess.
     guess_number++;//increments the guess number
     return 1; //valid guess
  }else{
    printf("make_guess: invalid guess\n");//invalid guess ouput
    return 0;//invalid guess
  }
}

