#include <stdio.h>
#pragma config WDT = OFF
#define P 0.45                        // Define a constant value P = 0.45

void main (void)
{
	int i, kg;                      // Declare variable i and kg as integer 
	for (i = 0; i <= 200; i+=10)
	/* Execute the for loop with i running from 0 to 200, each loop the value of i is increased by 10 */
	{
		kg = P * i;               // Assign kg the decimal value of P x i
		printf ("%d pounds = %d kilograms\n", i, kg);
		// Print out for each value of i
	}                             
	while (1);
}
