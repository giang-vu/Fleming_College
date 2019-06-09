/*
I choose default clock frequency XTAL = 20MHz.
Each tick will consume: TCY = 4/20MHz = 0.2us
The number of ticks in 0.5s delay will be: 0.5s/0.2us = 2,500,000 ticks
I use prescaler 1/128, so the ticks will be: 2,500,000/128 = 19531 ticks = 0x4C4B ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x4C4B = 0xB3B5
I use 16-bit timer, internal clock, increment on L-to-H transition, prescaler 1:128, so the value of T0CON will be:
T0CON = 0b00000110
*/

#include <p18f458.h> 				//including PIC18F458 library file
#pragma config WDT=OFF 				//setting Watchdog Timer 'OFF'
#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config DEBUG=OFF, LVP=OFF, STVR=OFF

void Timer0_delay()
{
	T0CON=0b00000110; 				//initializing Timer0
	TMR0H=0xB3; 					//Timer0 High bit delay
	TMR0L=0xB5; 					//Timer0 Low bit delay
	T0CONbits.TMR0ON=1; 			//setting Timer0 'ON'
	wait:
	if(INTCONbits.TMR0IF==0)			//checking condition
	{
		goto wait;
	}
	else
	{
		T0CONbits.TMR0ON=0;			//setting timer0 'OFF'
		INTCONbits.TMR0IF=0;		//setting interrupt flag '0'
	}
}

void main()
{
	ADCON1=0x06; 					//setting ADCON1 register
	CMCON=0x07; 					//turning comparator of from RD0-RD3
	TRISA=0; 					//clearing PORTA
	PORTAbits.RA0=0; 				//setting RA0=0
	while(1)
	{
		PORTAbits.RA0=~PORTAbits.RA0;	//toggling bit RA0
		Timer0_delay(); 			//calling delay function
	}
}
