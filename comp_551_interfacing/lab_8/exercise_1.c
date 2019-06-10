/*
I choose clock frequency XTAL = 20MHz.
Each tick will consume: TCY = 4/20MHz = 0.2us
The number of ticks in 1.2s delay will be: 1.2/0.2us = 6,000,000 ticks
Using the prescaler 1/128, so the ticks will be: 6,000,000/128 = 46875 ticks = 0xB71B ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0xB71B = 0x48E5
I use 16-bit timer, internal clock, increment on L-to-H transition, prescaler 1:128, so the value of T0CON will be:
T0CON = 0b00000110 = 0x06
*/

#include<P18F458.h>					//including PIC18 library file
#pragma config OSC=HS,OSCS=OFF			//configuring settings
#pragma PWRT=OFF,BOR=ON,BORV=45
#pragma config WDT=OFF				//setting Watchdog Timer 'OFF'
#pragma config DEBUG=OFF,LVP=OFF,STVR=OFF
#define mybit PORTEbits.RE2			//defining PORTE2 bit

void timer0_delay()
{
	T0CON=0x06; 		//initializing Timer0
	TMR0H=0x48; 		//Timer0 High bit delay
	TMR0L=0xE5; 		//Timer0 Low bit delay
	T0CONbits.TMR0ON=1; //setting Timer0 'ON'
wait:
	{
		if(INTCONbits.TMR0IF==0) 	       //checking condition
		{
			goto wait;
		}
		else
		{
			T0CONbits.TMR0ON=0; 	//setting Timer0 'OFF'
			INTCONbits.TMR0IF=0;	//setting interrupt flag '0'
		}
	}
}

void main()
{
	int i;
	int a[16]={	0b01100111,  //logically present 9
			0b01111111,	//logically present 8
			0b00000111,	//logically present 7
			0b01111101,	//logically present 6
			0b01101101,	//logically present 5
			0b01100110,	//logically present 4
			0b01001111,	//logically present 3
			0b01011011,	//logically present 2
			0b00000110,	//logically present 1
			0b00111111,	//logically present 0
			0b01110001,	//logically present F
			0b01111001,	//logically present E
			0b01011110,	//logically present d
			0b01011000,  //logically present c
			0b01111100,	//logically present b
			0b01110111	//logically present A
			};
	ADCON1=0x06;
	CMCON=0x07;
	TRISB=0;
	PORTB=0;
	TRISEbits.TRISE2=1;
	if(mybit==0)                     	// if the button is pressed
	{
		while(1)
		{
			for(i = 0; i < 16; i++)	//display these values
			{
hold:
				PORTB = ~a[i]; 
/*Because of using Common Anode, we light a segment by setting it to 0*/
				timer0_delay();     //calling delay function
				if (mybit == 1)	//if button is released
				{
					goto hold;	//display the current value
				}
			}
		}
	}
	else	                                 //initially, if button is not pressed
	{
		PORTB = 0xFF;				//do not light any bar
	}	
}
