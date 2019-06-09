/*
I choose default clock frequency XTAL = 20MHz.
Each tick will consume: TCY = 4/20MHz = 0.2us

For 1.6 seconds delay in Timer0_delay1 function:
The number of ticks in 1.6s delay will be: 1.6s/0.2us = 8,000,000 ticks
I use prescaler 1/128, so the ticks will be: 8,000,000/128 = 62500 ticks = 0xF424 ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0xF424 = 0x0BDC

For 0.6 seconds delay in Timer0_delay2 function:
The number of ticks in 0.6s delay will be: 0.6s/0.2us = 3,000,000 ticks
I use prescaler 1/128, so the ticks will be: 3,000,000/128 = 23438 ticks = 0x5B8E ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x5B8D = 0xA472

I use 16-bit timer, internal clock, increment on L-to-H transition, prescaler 1:128, so the value of T0CON will be:
T0CON = 0b00000110
*/

#include <P18F458.h>
#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF
#pragma config DEBUG=OFF, LVP=OFF, STVR=OFF
#define mybit PORTEbits.RE2

void Timer0_delay1()                                
{
	T0CON=0b00000110; 					//setting Timer0
	TMR0H=0x0B; 						//setting Timer0 high bits
	TMR0L=0xDC; 						//setting Timer0 low bit
	T0CONbits.TMR0ON=1; 				//setting Timer0 'ON'
	wait:
	if(INTCONbits.TMR0IF==0) 				//checking condition
	{
		goto wait;
	}
	else
	{
		T0CONbits.TMR0ON=0; 			//setting Timer0 'OFF'
		INTCONbits.TMR0IF=0; 			//reset Timer0 Flag
	}
}

void Timer0_delay2()
{
	T0CON=0b00000110; 					//setting Timer0
	TMR0H=0xA4; 						//setting Timer0 high bits
	TMR0L=0x72; 						//setting Timer0 low bits
	T0CONbits.TMR0ON=1; 				//setting Timer0 'ON'
	wait:
	if(INTCONbits.TMR0IF==0) 				//checking condition
	{
		goto wait;
	}
	else
	{
		T0CONbits.TMR0ON=0; 			//setting Timer0 'OFF'
		INTCONbits.TMR0IF=0; 			//reset Timer0 flag
	}
}

void main()
{
	ADCON1=0x06; 						//setting ADCON1 register
	CMCON=0x07; 						//turning off from RD0 to RD3
	TRISEbits.TRISE2=1; 				//turning RE2 as input
	TRISA=0; 						//clearing PORTA
	PORTA=0; 						//setting PORTA=0
	while(1)
	{
		if(mybit==0)
		{
			PORTAbits.RA0=~PORTAbits.RA0; 	//toggling RA0
			Timer0_delay2(); 			//calling delay of 0.6 sec
		}
		else
		{
			PORTAbits.RA0=~PORTAbits.RA0;	//toggling RA0
			Timer0_delay1(); 			//calling delay of 1.6 sec
		}
	}
}
