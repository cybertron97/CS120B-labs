/*
 * taror002_lab8_part1.c
 *
 * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #8  Exercise #1
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();
	
	unsigned short my_short = ADC;
	//unsigned char my_char = (char)my_short; // my_char = 0xCD
	//my_char = (char)(my_short >> 4); // my_char = 0xBC
	
    while (1) 
    {
		PORTB = (char) my_short;
		PORTD = (char) (my_short >> 4);
		my_short = ADC;
    }
}

