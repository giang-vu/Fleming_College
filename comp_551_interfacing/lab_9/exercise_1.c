/*
We choose default clock frequency XTAL = 20MHz.
PWM Frequency = 20KHz: PR2=[FOSC/(4*N*FPWM)]-1=[(20*106)/(4*1*20*103)]-1=249

For 100% duty cycle:
CCPR1L=249
DCB1B1:DCB1B0=0:0 (For .0 decimal value)
CCP1CON=0b00001100

For 20% duty cycle:
0.2*249=49.8
CCPR1L=49
CCP1CON=0b000111100
DCB1B1:DCB1B0=1:1 (For 75%)

Since, DC motor has inertia of its own, and it will not work at low values of CCPR1L
For this motor, the PR2 scale of 0-249 has been changed to scale of 183-249
[(249-183)*0.2]+183=196.2
CCPR1L=196
DCB1B1:DCB1B0=0:1 (For 0.25 decimal value)
CCP1CON=0b00011100

I use prescaler value of 1, therefore initial value of Timer2 is:
T2CON=0b00000000
*/

#include<P18F458.h>				//including PIC18 library file
#pragma config OSC=HS, OSCS=OFF		//configuring settings
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF			//setting watchdog timer 'OFF'
#pragma config DEBUG=OFF, LVP=OFF, STVR=OFF
#define mybit PORTEbits.RE2		//defining PORTE2 bit
#define greenled PORTBbits.RB1		//defining bit connected to green led
#define redled PORTBbits.RB0		//defining bit connected to red led

void main()
{
	ADCON1=0x06;				//setting ADCON1 registed
	CMCON=0x07;				//setting comparators 'OFF' from RD0-RD3
	TRISB=0;				//setting PORTB as output port
	PR2=249;				//setting PR2 register for 20KHz freq.
	T2CON=0b00000000;			//setting Timer2
	TRISC=0b11111001;			//clearing PORTC and RC2 as output bit
	TRISEbits.TRISE2=1;			//setting RE2 as input bit
	T2CONbits.TMR2ON=1;			//starting Timer2
	while(1)				//infinite loop
	{
		if(mybit==0)			//when ON-BOARD button is pressed
		{
			greenled=1;		//greenled is 'ON', reverse direction
			redled=0;		//redled is 'OFF'
			CCP1CON=0b00011100; //setting CCP1CON as calculated
			CCPR1L=196;		//setting duty cycle of 20% as calculated
		}
		else				//when ON-BOARD button is not pressed
		{
			greenled=0;		//greenled is 'OFF'
			redled=1;		//redled is 'ON', forward direction
			CCP1CON=0b00001100; //setting CCP1CON as calculated 
			CCPR1L=249;		//setting duty cycle of 100% as calculated
		}
       }
}
