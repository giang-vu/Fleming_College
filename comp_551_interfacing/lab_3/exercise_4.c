#include <P18F458.h>
#pragma config WDT = OFF

void delay (void)
{
	int i;
	for (i = 0; i < 100; i++);
}

void main(void) 
{
	int j;
	TRISB = 0;  // Set all PORTB pins as output
	PORTB = 0x5A; // Set 0x5A as the output
	while (1)
	{
		for (j = 0; j < 20000; j++) // Run 20000 times
		{
			delay();
			PORTB = ~PORTB;
			/* Because 0xA5 = ~0x5A, all the bits of PORTB will be toggled */
		}
	}
}
