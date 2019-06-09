/*
In order to get a frequency of 3kHz, the time period will be: T = 1/f = 1/3000 s
The time period is equal to double delay time, so the delay time will be:
delay = 1/(3000 x 2) = 1/6000 s = 1000/6 us (~ 168us)
Now I write a program using Timer1 to have the delay time 1000/6 us.
I choose clock frequency XTAL = 4MHz.
Each tick will consume: TCY = 4/4MHz = 1us
The number of ticks in 1ms delay will be: 168us/1us = 168 ticks
The largest prescaler possible is 1/8, so the ticks will be: 168/8 = 21 ticks = 0x0015 ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x0015 = 0xFFEB
I use 16-bit timer, prescaler 1/8, disable oscillator, off synchronization, internal clock, so the value of T0CON will be:
T0CON = 10110000 = 0xB0
*/

#include <P18F458.h>
#pragma config WDT = OFF
#define myBit PORTCbits.RC7          // Define PORTC RC7 as myBit

void Timer1_delay()                  // Timer1 delay function
{	                                      
	T1CON = 0xB0;                  // Set Timer1
	TMR1H = 0xFF;
	TMR1L = 0xEB;                  // Load value 0xFFEB to <TMR1H:TMR1L>
	T1CONbits.TMR1ON = 1;	       // Turn on Timer1

wait:
	if (PIR1bits.TMR1IF == 0)      // Wait for Timer1 to roll over
	{
		goto wait;
	}
	else                           // Roll over occurs
	{
		T1CONbits.TMR1ON = 0;   // Turn off Timer1
		PIR1bits.TMR1IF = 0;    // Reset Timer1 flag
	}
}

void main (void)
{   
	TRISC = 0;				// Set all PORTC pins as output	
	while (1)
	{
		myBit = 0;			 
		Timer1_delay();
		myBit = 1;
		Timer1_delay();
            /* Call the delay twice to measure the time period */
		myBit = 0;
	}
}
