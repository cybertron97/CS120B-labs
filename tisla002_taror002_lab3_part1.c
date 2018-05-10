/*
 * taror002_lab3_part1.c
 *
 * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #3  Exercise #1
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */




#include "avr/io.h"

enum LA_States { LA_SMStart, LA_s0, LA_s1, LA_wait, LA_wait1 } LA_State;
	
#define A0 (PINA & 0x01)	

void TickFct_LED()
{
	switch(LA_State) {   // Transitions
		case LA_SMStart:  // Initial transition
		LA_State = LA_wait;
		break;

		case LA_wait:
		if(A0){
			LA_State = LA_s1;
		}else if (!A0){
			LA_State = LA_wait;
		}
		break;
		
		case LA_s1:
		if(A0){
			LA_State = LA_s1;
		}else if(!A0){
			LA_State = LA_wait1;
		}
		break;
		
		case LA_wait1:
		if(!A0){
			LA_State = LA_wait1;
		}else if(A0){
			LA_State = LA_s0;
		}
		break;
		
		case LA_s0:
		if(A0){
			LA_State = LA_s0;
		}
		if (!A0)
		{
			LA_State=LA_wait;
		}
		break;

		default:
		LA_State = LA_SMStart;
		break;
	} // Transitions

	switch(LA_State) {   // State actions
		case LA_s0:
		PORTB=0x01;
		break;

		case LA_s1:
		PORTB = 0x02;
		break;
		
		case LA_wait:
		PORTB = 0x01;
		break;
		
		case LA_wait1:
		PORTB = 0x02;
		break;

		default:
		break;
	} // State actions
}

int main(void) {
	DDRA=0x00; PORTA=0xFF;
	DDRB=0xFF; PORTB=0x00;
	PORTB = 0x00;              // Initialize outputs
	
	LA_State = LA_SMStart; // Indicates initial call

	while(1) {
		TickFct_LED();
	}
}