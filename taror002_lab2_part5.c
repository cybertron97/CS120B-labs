/*	Partner(s) Name & E-mail: Takbir Islam tisla002@ucr.edu
 *	Lab Section: 026 
 *	Assignment: Lab #2  Exercise # 5
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
	DDRB = 0xFE; PORTB = 0x01; // Configure port B's 7 pins as outputs and B0 as input
	DDRD = 0x00; PORTD = 0xFF; // Configure port D's 8 pins as inputs
								// initialize to 0s
	 
	unsigned short button = 0x00;	// intermediate variable used for port updates
	
	unsigned char tmpB = 0x00;	//store value passed into output
		
    /* Replace with your application code */
    while (1) 
    {
		// 1) Read Inputs and assign to variables
		button = (PIND << 1) | (PINB & 0x01);
				
		// 2) Perform Computation
		
		if( button >= 70){
			tmpB = 0x02;
		}else if ( button > 5 && button < 70){
			tmpB = 0x04;
		}else{
			tmpB = 0x00;
		}
			
		// 3) write results to port
		PORTB = tmpB;
		
		
    }
	
	return 0;
}

