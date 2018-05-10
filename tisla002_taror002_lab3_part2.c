 /*
 * taror002_lab3_part2.c
 *
 * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #3  Exercise #2
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */

#include <avr/io.h>

enum LA_States { LA_SMStart, init, check, increment, decrement, wait, wait1, reset } LA_State;

#define A0 (PINA & 0x01)
#define A1 (PINA & 0x02)

void TickFct_LED()
{
	switch(LA_State) {   // Transitions
		case LA_SMStart:  // Initial transition
		LA_State = init;
		break;

		case init:
		LA_State = check;
		break;
		
		case check:
		if(!A0 && !A1){
			LA_State = check; 
		}else if(A0 && !A1){
			LA_State = increment;
		}else if(!A0 && A1){
			LA_State = decrement;
		}else if(A0 && A1){
			LA_State = reset;
		}
		break;
		
		case increment:
		LA_State = wait;
		break;
		
		case decrement:
		LA_State = wait1;
		break;
		
		case wait:
		if(A0 && A1){
			LA_State = reset;
		}else if(!A0 ){ //&& !A1
			LA_State = check;
		}else if (A0 ){//&& !A1
			LA_State = wait;
		}
		break;
		
		case wait1:
		if(A0 && A1){
			LA_State = reset;
		}else if(!A1){
			LA_State = check;
		}else if(A1){
			LA_State = wait1;
		}
		break;
		
		case reset:
		LA_State = check;
		break;

		default:
		LA_State = LA_SMStart;
		break;
	} // Transitions

	switch(LA_State) {   // State actions
		case init:
		PORTC = 0x07;
		break;

		case check:
		break;
		
		case increment:
		if( PORTC < 9 ){
			PORTC = PORTC + 1;
		}
		break;
		
		case decrement:
		if( PORTC > 0 ){
			PORTC = PORTC - 1;
		}
		break;
		
		case wait:
		break;
		
		case wait1:
		break;
		
		case reset:
		PORTC = 0x00;
		break;

		default:
		break;
	} // State actions
}

int main(void) {
	DDRA=0x00; PORTA=0xFF;
	DDRC=0xFF; PORTC=0x00;
	PORTC = 0x00;              // Initialize outputs
	
	LA_State = LA_SMStart; // Indicates initial call

	while(1) {
		TickFct_LED();
	}
}