/*
I choose clock frequency XTAL = 4MHz.
Each tick will consume: TCY = 4/4MHz = 1us

PORTB RB0:
In order to get a frequency of 1kHz, the time period will be: T = 1/f = 1/1000 = 1ms
The time period is equal to double delay time, so the delay time will be:
delay0 = 1/2 = 0.5ms = 500us
Now I write a program using Timer0 to have the delay time 500us.
The number of ticks in 500us delay will be: 500us/1us = 500 ticks = 0x01F4 ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x01F4 = 0xFE0C

PORTB RB4:
In order to get a frequency of 2kHz, the time period will be: T = 1/f = 1/2000 = 0.5ms
The time period is equal to double delay time, so the delay time will be:
delay4 = 0.5/2 = 0.25ms = 250us
Now I write a program using Timer0 to have the delay time 250us.
The number of ticks in 250us delay will be: 250us/1us = 250 ticks = 0x00FA ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x00FA = 0xFF06

For both delay functions, I use 16-bit timer, internal clock, increment on L-to-H transition, no prescale, so the value of T0CON will be:
T0CON = 00001000 = 0x08
*/

#include <P18F458.h>
#pragma config WDT = OFF
#define myBit0 PORTBbits.RB0
#define myBit4 PORTBbits.RB4
#define myBit7 PORTBbits.RB7

void Timer0_delay0()				// Timer0 delay function for RB0
{	                                      	
	T0CON = 0x08;					
	TMR0H = 0xFE; 
	TMR0L = 0x0C;
	T0CONbits.TMR0ON = 1;	        

wait:
	if (INTCONbits.TMR0IF == 0)
	{
		goto wait;
	}
	else
	{
		T0CONbits.TMR0ON = 0;
		INTCONbits.TMR0IF = 0;
	}
}

void Timer0_delay4()				// Timer0 delay function for RB4
{	                                      
	T0CON = 0x08;
	TMR0H = 0xFF;
	TMR0L = 0x06;
	T0CONbits.TMR0ON = 1;	

wait:
	if (INTCONbits.TMR0IF == 0)
	{
		goto wait;
	}
	else
	{
		T0CONbits.TMR0ON = 0;
		INTCONbits.TMR0IF = 0;
	}
}

void main (void)
{
	TRISB = 0x80;
	/* Set RB7 as input to use the Asynchronous Stimulus, the others as output */
	while (1)
	{
		if (myBit7 == 0)	
		{
			myBit0 = ~myBit0;       // Toggle RB0
			myBit4 = 0;			// Deactivate RB4
			Timer0_delay0();
		}
		else
		{
			myBit4 = ~myBit4;	      // Toggle RB4
			myBit0 = 0;			// Deactivate RB0
			Timer0_delay4();
		}	
	}
}
