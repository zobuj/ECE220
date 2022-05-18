
/*
This code is computes the coefficients of a row from pascal's
triangle using a given formula. The user inputs a row, and the code loops
and calculates the coeffcients for that row. The coefficients come from the
expansion of the polynomial (1+x)^n
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;



  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here

  unsigned long k=1;//coefficient
  for(int n=0; n<=row; n++){//Outer loop, loops through each of the rows
    for(int i = 1; i<=n; i++){//Inner loop, calculates the numbers for each row
      k=(k*(row + 1 - i))/(i);//formula to compute pascal's triangle
    }
    printf("%lu ",k);//prints out the coefficient
    k=1;//resets the coefficient to 1 so formula works properly
  }
  printf("\n");

  return 0;
}