/*	Partner(s) Name & E-mail: Takbir Islam tisla002@ucr.edu
 *	Lab Section: 026 
 *	Assignment: Lab #2  Exercise # 1
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
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as outputs,
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s
	unsigned char tmpC=0x00; 
	//while loop 
	while (1)
	{
		unsigned char bit_count = 0x00; // to count the number of 1's  
		unsigned char cnt; //iterator 
		//lets do for A first 
		for (cnt=0;cnt < 8; cnt++)
		{
			tmpC=PINA; 
			if (GetBit(tmpC,cnt))
			{
				bit_count++; 
			}
			//for PinB
			tmpC=PINB; 
			if (GetBit(tmpC,cnt))
			{
				bit_count++; 
			}
		}
		PORTC=bit_count; 
	}
	return 0; 
}

