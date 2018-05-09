
/*	Partner(s) Name & E-mail: Takbir Islam tisla002@ucr.edu
 *	Lab Section: 026 
 *	Assignment: Lab #1  Exercise # 3
 *	Author: Tanish Arora and Takbir Islam
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

int main(void)
{
	DDRA= 0x00; PORTA= 0xFF; //setting inputs
	DDRC= 0xFF; PORTC= 0x00; //setting outputs 
	
	unsigned char cnt =0;
	unsigned char covered = 0;
	unsigned char spaces_available=4;
	
	while(1)
	{
		covered = (PINA & 0x01) + ((PINA>>1) & 0x01)+ ((PINA>>2) & 0x01)+((PINA>>3) & 0x01); //shifting number of digits and then comparing 
		cnt = spaces_available-covered;
		
		if (cnt==0 )
		{
			cnt = cnt | 0x80; 
		}
		
		PORTC=cnt;
	}
	return 0;
}