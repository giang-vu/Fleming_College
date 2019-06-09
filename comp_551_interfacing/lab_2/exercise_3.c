#include <stdio.h>                       
#pragma config WDT = OFF                 

void main (void)                         
{                                        
	int i;                             
	i = 0;                             
	do                                	// Execute the following loop
	{                                  
		printf ("Hello, world!\n");     // Print out for each value of i
		i++;                        	// Increase the value of i by 1
	}                                  
	while (i < 15);                   	// Stop the loop when i = 15
	while (1);                         
}
