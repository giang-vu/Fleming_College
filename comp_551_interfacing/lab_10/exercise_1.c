/*
I choose clock frequency XTAL = 20MHz.
Each tick will consume: TCY = 4/20MHz = 0.2us

The number of ticks in 1ms delay will be: 1ms/0.2us = 5000 ticks =0x1388 ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x1388= 0XEC78
I use 16-bit timer, internal clock, increment on L-to-H transition, no prescaler, so the value of T0CON will be:
T0CON = 0b00000000 = 0

The number of ticks in 0.75s delay will be: 0.75s/0.2us = 3,750,000 ticks
Using the prescaler 1/256, so the ticks will be: 3,750,000/256 = 14648 ticks = 0x3938 ticks
The register value for TMR0H:TMR0L will be: 0xFFFF + 1 - 0x3938= 0XC6C8
I use 16-bit timer, internal clock, increment on L-to-H transition, prescaler 1/256, so the value of T0CON will be:
T0CON = 0b00000111 = 0x07
*/

#include<P18F458.h>				//include PIC458 library
#pragma config OSC=HS,OSCS=OFF		//configuring functions
#pragma PWRT=OFF,BOR=ON,BORV=45
#pragma config WDT=OFF				//setting Watchdog Timer 'OFF'
#pragma config DEBUG=OFF,LVP=OFF,STVR=OFF
#define RS PORTBbits.RB0		//defining bit RB0 as LCD's register Select bit 
#define RW PORTBbits.RB1		//defining bit RB1 as LCD's Read/Write bit
#define EN PORTBbits.RB2		//defininf bit RB2 as LCD's Enable bit

void delay1()
{
	T0CON=0b00000000;			//setting Timer0
	TMR0H=0xEC;					//setting Timer0 high bits
	TMR0L=0x78;					//setting Timer0 low bit
	
	T0CONbits.TMR0ON=1;		//setting timer0 'ON'
wait:
	{
		if(INTCONbits.TMR0IF==0)	//checking condition
		{
			goto wait;
		}
		else
		{
			T0CONbits.TMR0ON=0;		//setting timer0 'OFF'
			INTCONbits.TMR0IF=0;	//setting timer0 interrrupt flag '0'
		}
	}
}

void delay2()
{
	T0CON=0b00000111;			//setting Timer0
	TMR0H=0xC6;					//setting Timer0 high bits
	TMR0L=0xC8;					//setting Timer0 low bit
	
	T0CONbits.TMR0ON=1;		//setting timer0 'ON'
wait1:
	{
		if(INTCONbits.TMR0IF==0)	//checking condition
		{
			goto wait1;
		}
		else
		{
			T0CONbits.TMR0ON=0;		//setting timer0 'OFF'
			INTCONbits.TMR0IF=0;	//setting timer0 interrrupt flag '0'
		}
	}
}

void lcdcmd(unsigned char a)		//lcd command function
{
	PORTD=a;					//assigning command to PORTD
	RS=0;						//data is treated as command
	RW=0;						//data is being written in LCD
	EN=1;						//setting enable bit high
	delay1();					//delay of 1ms
	EN=0;						//setting enable bit low to run the command
}

void lcddata(unsigned char a)		//lcd function for showing data 
{
	PORTD=a;					//putting data to PORTD
	RS=1;						//data is displayed on screen
	RW=0;						//data is being written in LCD
	EN=1;						//setting enable bit high
	delay1();					//delay of 1ms
	EN=0;						//setting enable bit low to run the command
}

void lcdinit()				//initializing LCD
{
	lcdcmd(0x38);		//configure LCD for 2 line display, 8 bit mode
	lcdcmd(0x0C);		//display ON and cursor OFF
	lcdcmd(0x01);		//clear display screen
	lcdcmd(0x06);		//increment cursor
	lcdcmd(0x80);		//set cursor to first block of first line of LCD
}

void main()
{
	unsigned char a[]="COMP551";	//string for first line
	unsigned char b[]="Interfacing 2017";	//string for second line
	int i;			//interger variable
	ADCON1=0x06;		//setting ADCON1 register
	CMCON=0xFF;			//turning off all comparators
	TRISB=0;			//initializing PORTB as output port
	TRISD=0;			//initializing PORTD as output port
	TRISEbits.TRISE2=1;	//initializing RE2 bit as input bit

	while(1)		//infinite loop
	{
		lcdinit();		//initialize the LCD
		lcdcmd(0x14);		//shifting cursor to right to centered the first string
		lcdcmd(0x14);		//shifting cursor to right to centered the first string
		lcdcmd(0x14);		//shifting cursor to right to centered the first string
		lcdcmd(0x14);		//shifting cursor to right to centered the first string
		for(i=0;i<7;i++)		//for loop for first string
		{
			lcddata(a[i]);		//sending one character at a time
			lcdcmd(0x06);		//incrementing cursor
		}
		lcdcmd(0xC0);			//moving to next line
		for(i=0;i<17;i++)		//for loop for second string
		{
			if(PORTEbits.RE2==0)	//if button is pressed
			{
				lcddata(b[i]);		//send one character at a time
				lcdcmd(0x06);		//incrementing cursor
				delay2();			//.75 second delay
			}
			else				//if button is not pressed
			{
here:
				if(PORTEbits.RE2==1)	
				goto here;		//hold the loop here
				i--;			//return to previous character
			}
		}
	}
}
