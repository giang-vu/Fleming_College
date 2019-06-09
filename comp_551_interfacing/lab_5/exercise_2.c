/*
I use 16-bit timer, no prescaler, disable oscillator, enable synchronization, external clock, so the value of T0CON will be:
T0CON = 10000110 = 0x86
*/

#include <P18F458.h>
#pragma config WDT = OFF

void main (void)
{
	TRISCbits.TRISC0 = 1;                     // Set RC0 pin as input
	TRISB = 0;                                // Set PORTB pins as output
	TRISD = 0;                                // Set PORTD pins as output
	T1CON = 0x86;                             // Set Timer1
	TMR1H = 0x00;                             // Load value 0x00 to TMR1H 
	TMR1L = 0x00;                             // Load value 0x00 to TMR1L
	PORTB = 0;                                // Reset all PORTB pins
	PORTD = 0;                                // Reset all PORTD pins
	CMCON = 0xFF;                             // Set Comparator Module
	T1CONbits.TMR1ON = 1;				// Turn on Timer1
  while (1)
	{
		if (PIR1bits.TMR1IF == 0)		// Wait for Timer1 roll over
		{
			if (PORTCbits.RC0 == 1)		// Count the clock 
			{
				TMR1L += 1;			// Increase TMR1L by 1
				PORTB = TMR1L;		// Represent TMR1L's value 
				if (PORTB == 0xFF)
				{	
					TMR1H += 1;		// Increase TMR1H by 1
					TMR1L = 0;		// Reset TMR1L
					PORTD = TMR1H;	// Represent TMR1H's value
				}
			}
		}
		else					      // Roll over occurs
		{
			T1CONbits.TMR1ON = 0;		// Turn off Timer1
			PIR1bits.TMR1IF = 0;		// Reset Timer1 Flag
		}
	} 
}
