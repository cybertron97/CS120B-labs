/*
 * taror002_lab3_part3.c
 *
 * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #3  Exercise #3
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */
#include <avr/io.h>

enum LA_States { LA_SMStart, init, button, wait, button1 } LA_State;

#define X (PINA & 0x01)
#define Y (PINA & 0x02)
#define pound (PINA & 0x04)
#define inside (PINA & 0x80)

void TickFct_LED()
{
	switch(LA_State) {   // Transitions
		case LA_SMStart:  // Initial transition
		LA_State = init;
		break;

		case init:
		if(pound && !X && !Y && !inside){
			LA_State = button;
		}else{
			LA_State = init;
		}
		break;
		
		case button:
		if(pound && !X && !Y && !inside){
			LA_State = button;
		}else if(!pound && !X && !Y && !inside){
			LA_State = wait;
		}else{
			LA_State = init;
		}
		break;
		
		case wait:
		if(!pound && !X && Y && !inside){
			LA_State = button1;
		}else if (!pound && !X && !Y && !inside){
			LA_State = wait;
		}else{
			LA_State = init;
		}
		break;
		
		case button1:
		if(!pound && !X && !Y && inside){
			LA_State = init;
		}else{
			LA_State = button1;
		}
		break;
		
		default:
		LA_State = LA_SMStart;
		break;
	} // Transitions

	switch(LA_State) {   // State actions
		case init:
		PORTB = 0x00;
		break;

		case button:
		break;
		
		case wait:
		break;
		
		case button1:
		PORTB = 0x01;
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