/*	Partner(s) Name & E-mail: Takbir Islam tisla002@ucr.edu
 *	Lab Section: 026 
 *	Assignment: Lab #2  Exercise # 4
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
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	DDRC = 0xFF; PORTC = 0x00; 
							   // initialize to 0s
	 
	unsigned char button = 0x00;	// intermediate variable used for port updates
	
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;	//store value passed into output
	
    /* Replace with your application code */
    while (1) 
    {
		// 1) Read Inputs and assign to variables
		button = PINA;
				
		// 2) Perform Computation
		 
		for(unsigned char i = 0; i <= 3; i++){		// GetBit from A0 - A3 and map it to C4 - C7
			tmpC = SetBit(tmpC, i + 4, GetBit(button, i) );                  
		}
		
		for(unsigned char z = 4; z <= 7; z++){		// GetBit from A4 - A7 and map it to B0 - B4
			tmpB = SetBit(tmpB, z - 4, GetBit(button, z) );
		}
		
		// 3) write results to port
		PORTB = tmpB;
		PORTC = tmpC;
		
		
    }
}

