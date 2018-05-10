/*
 * taror002_lab3_part5.c
 *
 * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #3  Exercise #5
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */

#include <avr/io.h>

enum LA_States { LA_SMStart, init, pass, wait, wait1} LA_State;

#define X (PINA & 0x01)
#define Y (PINA & 0x02)
#define pound (PINA & 0x04)
#define inside (PINA & 0x80)

unsigned char correct_sq[] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01};
unsigned char tmp = 0;
	
void sq(){
	while(1){
		if(PINA == correct_sq[tmp]){
			tmp++;
			break;
		}else if(tmp != 0 && PINA == correct_sq[tmp - 1]){
			break;
		}else{
			tmp = 0;
		}
		break;
	}
}


void TickFct_LED()
{
	switch(LA_State) {   // Transitions
		case LA_SMStart:  // Initial transition
		LA_State = init;
		break;

		case init:
		LA_State = pass;
		break;
		
		case pass:
		if(tmp == 7){
			LA_State = wait;
			tmp = 0;	
		}else{
			sq();
		}
		break;
		
		case wait:
		LA_State = wait1;
		break;
		
		case wait1:
		if(!pound && !X && !Y && inside){
			LA_State = init;
		}else if(pound && !X && !Y && !inside){
			LA_State = pass;
		}else{
			LA_State = wait1;
		}
		break;
		
		default:
		LA_State = LA_SMStart;
		break;
	} // Transitions

	switch(LA_State) {   // State actions
		case init:
		PORTB = 0x00;
		PORTC = init;
		break;

		case pass:
		PORTC = pass;
		break;		
		
		case wait:
		if(PORTB == 0){
			PORTB = 1;
		}else{
			PORTB = 0;
		}
		PORTC = wait;
		break;
		
		case wait1:
		PORTC = wait1;
		break;
		
		default:
		break;
	} // State actions
}

int main(void) {
	DDRA=0x00; PORTA=0xFF;
	DDRB=0xFF; PORTB=0x00;
	DDRC=0xFF; PORTC=0x00;
	
	PORTB = 0x00;              // Initialize outputs
	
	LA_State = LA_SMStart; // Indicates initial call

	while(1) {
		TickFct_LED();
	}
}