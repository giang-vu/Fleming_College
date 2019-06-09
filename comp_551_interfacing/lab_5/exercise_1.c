/*
I use 16-bit timer, external clock, increment on L-to-H transition, no prescale, so the value of T0CON will be:
T0CON = 01101000 = 0x68
*/

#include <P18F458.h>
#pragma config WDT = OFF

void main (void)
{
	TRISAbits.TRISA4 = 1;			// Set RA4 pin as input
	TRISB = 0;					// Set all PORTB pins as output
	T0CON = 0x68;			      // Set Timer0
	TMR0L = 0x00;				// Load value 0x00 to TMR0L	
	PORTB = 0;					// Reset all PORTB pins
	while (1)	
	{
		if (INTCONbits.TMR0IF == 0)   // Wait for Timer0 to roll over
		{
			T0CONbits.TMR0ON = 1;	// Turn on Timer0
			PORTB = TMR0L;		// Represent the value 
		}
		else					// Roll over occurs
		{
			T0CONbits.TMR0ON = 0;	// Turn off Timer0
			INTCONbits.TMR0IF = 0;	// Reset Timer0 flag
		}
	}
}
