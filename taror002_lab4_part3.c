/*
 * taror002_lab4_part3'.c
 *
 * Created: 4/19/2018 7:59:21 AM
 * Author : tanish
 */ 

#include <avr/io.h>

enum LA_States { LA_SMStart, init, init_wait, display, wait, display1, wait1} LA_State;

#define A0 (~PINA & 0x01)

unsigned char tmp = 0x00;

void TickFct_LED()
{
	switch(LA_State) {   // Transitions
		case LA_SMStart:  // Initial transition
		LA_State = init;
		break;

		case init:
		if(A0){
			LA_State = init;
		}else{
			LA_State = init_wait;
		}
		break;
		
		case init_wait:
		if(!A0){
			LA_State = init_wait;
		}else{
			LA_State = display;
		}
		break;
		
		case display:
		if(!A0){
			LA_State = wait;
		}else{
			LA_State = display;
		}
		break;
		
		case wait:
		if(!A0){
			LA_State = wait;
		}else{
			LA_State = display1;
		}
		break;
		
		case display1:
		if(!A0){
			LA_State = wait1;
		}else{
			LA_State = display1;
		}
		break;
		
		case wait1:
		if(!A0){
			LA_State = wait1;
		}else{
			LA_State = init;
		}
		break;

		default:
		LA_State = LA_SMStart;
		break;
	} // Transitions

	switch(LA_State) {   // State actions
		case init:
		PORTC = 0x00;
		break;
		
		case init_wait:
		break;

		case display:
		PORTC = 0xAA;
		break;
		
		case display1:
		PORTC = 0x55;
		break;
		
		case wait:
		break;
		
		case wait1:
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