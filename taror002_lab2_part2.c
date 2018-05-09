/*	Partner(s) Name & E-mail: Takbir Islam tisla002@ucr.edu
 *	Lab Section: 026 
 *	Assignment: Lab #2  Exercise # 2
 *	Author: Tanish Arora and Takbir Islam
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	//DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as outputs,
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s
	unsigned char tmpC=0x00;
	//while loop
	while (1)
	{
		tmpC= PINA; 
		if (tmpC == 1 || tmpC == 2)
		{
			PORTC = 0x20; 
		}
		if (tmpC == 3 || tmpC==4)
		{
			PORTC = 0x30; 
		}
		if (tmpC == 5 || tmpC == 6)
		{
			PORTC = 0x38; 
		}
		if (tmpC >=7 && tmpC <=9)
		{
			PORTC = 0x1C; 
		}
		if ( tmpC>=10 && tmpC<=12)
		{
			PORTC = 0x3E; 
		}
		if (tmpC>=13 && tmpC<=15)
		{
			PORTC=0x3F; 
		}
		//for less than 4 we will need to light up another LED as well 
		
		unsigned char tmpB = PORTC ; 
		if (tmpC < 4) 
		{
			PORTC= (tmpB | 0x40); //bitwise or 
		}
		
	}
	return 0;
}