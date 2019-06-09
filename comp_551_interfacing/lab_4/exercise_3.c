/*
In order to get a frequency of 500Hz, the time period will be: T = 1/f = 1/500 = 2ms
The time period is equal to double delay time, so the delay time will be: delay = 2/2 = 1ms
Now I write a program using Timer0 to have the delay time 1ms.
I choose clock frequency XTAL = 4MHz.
Each tick will consume: TCY = 4/4MHz = 1us
The number of ticks in 1ms delay will be: 1m/1us = 1000 ticks = 0x03E8 ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x03E8 = 0xFC18
I use 16-bit timer, internal clock, increment on L-to-H transition, no prescale, so the value of T0CON will be:
T0CON = 00001000 = 0x08
*/

#include <P18F458.h>
#pragma config WDT = OFF
#define myBit PORTBbits.RB0         // Define PORTB RB0 as myBit

void Timer0_delay()                 // Timer0 delay function
{	                                      
	T0CON = 0x08;                 // Set Timer0
	TMR0H = 0xFC;                 // Load value 0xFC18 to <TMR0H:TMR0L>
	TMR0L = 0x18;
	T0CONbits.TMR0ON = 1;	      // Turn on Timer0

wait:
	if (INTCONbits.TMR0IF == 0) // Wait for Timer0 to roll over
	{
		goto wait;
	}
	else  // Roll over occurs
	{
		T0CONbits.TMR0ON = 0; // Turn off Timer0
		INTCONbits.TMR0IF = 0;  // Reset Timer0 flag
	}
}

void main (void)                    
{   
	TRISB = 0;  // Set all PORTB pins as output	
	while (1)
	{
		myBit = 0; 
		Timer0_delay();
		myBit = 1;
		Timer0_delay();
    /* Call the delay twice to measure the time period */
		myBit = 0;
	}
}
