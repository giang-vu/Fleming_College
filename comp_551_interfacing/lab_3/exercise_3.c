#include <P18F458.h>
#pragma config WDT = OFF

void delay (void)
{
	int i;
	for (i = 0; i < 100; i++);
}

void main(void) 
{
	char arr[] = {+5, +4, +3, +2, +1, 0, -1, -2, -3, -4, -5}; // Declare an array to store characters
	char j;
	TRISC = 0;  // Set all PORTC pins as output
	while (1)
	for (j = 0; j < 11; j++)  
	{
		delay();
		PORTC = arr[j];
	}
}
