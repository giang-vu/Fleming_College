#include <stdio.h>                       // Include stdio.h library
#pragma config WDT = OFF                 // Disable Watchdog Timer

void main (void)                         // Declare the main function
{                                        // Open the main function
  int i;                                 // Declare variable i as integer
	for (i = 0; i < 5; i++)
	/* Execute the for loop with i running from 0 to 4, each loop the value of i is increased by 1*/  
	{                                      // Open the for loop to add code
		printf ("Hello, world!\n");          // Print out for each value of i
	}                                      // Close the for loop
	while (1);                             // Stop an infinite loop 
}                                        // Clode the main function
