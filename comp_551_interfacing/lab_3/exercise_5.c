/*
I choose clock frequency XTAL = 4MHz.
Each tick will consume: TCY = 4/4MHz = 1us
The number of ticks in 1 second delay will be: 1s/1us = 1,000,000 ticks
Because 1,000,000 is out of range, so I use prescaler 1/16: 1,000,000/16 = 62,500 ticks = 0xF424 ticks
Therefore, the register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0xF424 = 0x0BDC
I use prescaler 1/16, so the value of T0CON = 0x03
*/

#include <P18F458.h>
#pragma config WDT = OFF

void delay_1second()  // Delay 1 second function	
{
	T0CON = 0x03; // Set Timer0, 16-bit mode, 1:16 prescaler
	TMR0H = 0x0B; // Load value 0x0BDC to <TMR0H:TMR0L>
	TMR0L = 0xDC;
	T0CONbits.TMR0ON = 1; // Turn on Timer0

wait:
	if (INTCONbits.TMR0IF == 0) // Wait for Timer0 to roll over
	{
		goto wait;                
	}
	else  // Roll over occurs
	{
		T0CONbits.TMR0ON = 0; // Turn OFF Timer0
		INTCONbits.TMR0IF = 0;  // Reset Timer0 flag
	}
}

void main(void) 
{
	int j;
	TRISB = 0;  // Set all PORTB pins as output                                      
	while (1)                      
	{
		for (j = 0; j < 20000; j++) // Run 20000 times
		{	
			PORTB = 0x5A; // Set 0x5A as the output
			delay_1second();
			PORTB = ~PORTB; // All the bits of PORTB will be toggled
			delay_1second();          
		}
	}
}
