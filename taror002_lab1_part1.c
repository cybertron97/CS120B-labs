/*	Partner(s) Name & E-mail: Takbir Islam tisla002@ucr.edu
 *	Lab Section: 026 
 *	Assignment: Lab #1  Exercise # 1
 *	Author: Tanish Arora and Takbir Islam
 *	
 *     I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs,
        unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary vsriable to hold the value of A
	unsigned char tmpA1 = 0x00;
while(1)
	{
		// 1) Read input
		tmpA = PINA & 0x01;
		tmpA1 = PINA & 0x02;
                if (tmpA == 0x01 && tmpA1 == 0x00) 
{                     // True if PA0 is 1 and PA1 = 0
			tmpB = (tmpB & 0xFC) | 0x01; // Sets tmpB to bbbbbb0
}
else {
			tmpB = (tmpB & 0xFC) | 0x00;// Sets tmpB to bbbbbb10
	// (clear rightmost 2 bits, then set to 00)
		}	
PORTB = tmpB;	
	}
	return 0;



}
