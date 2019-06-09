#include <P18F458.h>
#pragma config WDT = OFF

void delay (void)
{
	int i;
	for (i = 0; i < 100; i++);
}

void main(void) 
{
	char arr[] = "012345ABCD";      // Declare an array to store characters
	char j;
	TRISB = 0;                      // Set all PORTB pins as output
	while(1)
	{
		for (j = 0; j < 10; j++)  // Run each character in the array
		{
			delay();
			PORTB = arr[j];     // Represent hex value of the character
		}
	}
}
