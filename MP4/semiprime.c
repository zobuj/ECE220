#include <stdlib.h>
#include <stdio.h>
/*
The first error encountered in this file was in is_prime, whre inside of the for loop the code would return a "1" if the number was divisible by each number up to that number starting at 2 (which is the test for prime numbers). If the number was divisible then the number was not a prime number, so instead of returning a "1" if it was not prime, we wanted it to return a "0". This error causes errors in the print_semiprimes functions because the each number that is prime will not be printed. The next error in the code is in print_semiprimes at line 39. K should be defined as "i/j" instead of "i%j" because "i%j" will print out each number of the inputted range. Also the operation "i%j" at line 39 will always make like 40 to check if zero is prime, which will return as "1" due to the is_prime function, which will then cause the function to print out the number. The next error in the code is at line 43. I added a break statement at this point to ensure the loop is ended, and it moves to the next number in the interval. This will ensure any correct values are printed only once. The final error in the code is that I set ret to equal "1" at line 42 before the break and after we know that there is a semiprime in the range of the user inputs. If I did not do this then print_semiprimes would return zero always no matter what.
 */

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
	  return 0;//error here, interchanged with line 19, must be zero because loop tests if the number is not prime
        }
    }
    return 1;//error here, if nothing is returned in the loop then the number must be prime
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
		  k = i/j;//error here, changed from mod to div
                    if (is_prime(k)) {
		      printf("%d ", i);
		      ret = 1;
			break;//error here, added a break, if not some correct values are printed twice, ensures that only one correct value is printed
                    }
                }
            }
        }
    }
    printf("\n");
    return ret;

}