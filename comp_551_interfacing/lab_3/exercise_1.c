#include <P18F458.h>
#pragma config WDT = OFF

/* Add a delay function to see the output in the Logic Analyzer clearly */
void delay (void)
{
	int i;
	for (i = 0; i < 100; i++);
}

void main(void) 
{
	unsigned char j;
	TRISB = 0;                          // Set all PORTB pins as output
	while (1)                           // Repeat forever
	{
		for (j = 255; j >= 0; j--)    // Send values from FFH to 00H 
		{
			delay();                // Call the delay function
			PORTB = j;              // Represent the value 
		}
	}
}
