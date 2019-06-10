/*
FOSC = 20MHz, FPWM = 20KHz
Using PR2 = (FOSC/(FPWM*4*N)) ‐ 1, the value of PR2 register will be:
(20*106/(20*103*4*1)) ‐ 1 = 250 ‐ 1 = 249

For 95% duty cycle: 249 * 0.95 = 236.55
Therefore, CCPR1L=236 and CCP1CON=0b00101100 (0.55 is rounded to 0.5)

For 5% duty cycle: 249 * 0.05 = 12.45
Therefore, CCPR1L=12 and CCP1CON=0b00101100 (0.45 is rounded to 0.5)

We use Timer2, no postscale, prescaler=1, so the value of T2CON will be: T2CON = 0b00000000
*/

#include<P18F458.h> 			     //including PIC18 library file
#pragma config OSC=HS, OSCS=OFF	            //configuring settings
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF			     //setting watchdog timer 'OFF'
#pragma config DEBUG=OFF, LVP=OFF, STVR=OFF
#define mybit PORTEbits.RE2 	            //defining PORTE2 bit

void main()
{
	ADCON1=0x06; 				//setting ADCON1 register
	CMCON=0x07;				//turning 'OFF' comparator on bit D0-D3
	PR2=249; 				//setting PR2 register for 20KHz frequency
	T2CON=0b00000000; 			//setting Timer2
	TRISCbits.TRISC2=0; 		//setting RC2 as output bit
	TRISEbits.TRISE2=1; 		//setting RE2 as input bit
	T2CONbits.TMR2ON=1; 		//starting Timer2
	while(1)                         //infinite loop
	{
		if(mybit==0) 			//condition for RE2 bit
		{
			CCP1CON=0b00101100;	//setting CCP1CON as calculated
			CCPR1L=236; 		//setting duty cycle of 95% as calculated
		}
		else
		{
			CCP1CON=0b00101100; //setting CCP1CON as calculated
			CCPR1L=12; 		//setting duty cycle of 5% as calculated
		}
	}
}
