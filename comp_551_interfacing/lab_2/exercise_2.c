#include <stdio.h>                       
#pragma config WDT = OFF                 

void main (void)                         
{                                        
	int i;                              
	i = 0;                                // Declare the intial value of i
	while (i < 10)                        // Execute while loop when i < 10
	{                                  
		printf ("Hello, world!\n");   // Print out for each value of i 
		i++;                          // Increase the value of i by 1
	}                                  
	while (1);                         
}                                        
