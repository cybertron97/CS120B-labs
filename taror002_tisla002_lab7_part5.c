/*
 * taror002_tisla002_lab7_part5.c
 * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #7  Exercise #5
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)

enum States{start, init, increment, decrement, reset, wait} state;
unsigned char cnt;

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks


//given
void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void tick(){
	switch(state){		//transitions
		case start:
		state = init;
		break;
		
		case init:
		if(A0){
			state = increment;
		}else if(A1){
			state = decrement;
		}else if (A0 && A1){
			state = reset;
		}else{
			state = init;
		}
		break;
		
		case wait:
		if(A0){
			state = increment;
		}else if(A1){
			state = decrement;
		}else if (A0 && A1){
			state = reset;
		}else{
			state = wait;
		}
		break;
		
		case increment:
		if (A0 && A1){
			state = reset;
		}else if (A0){
			state = increment;
		}else{
			state = wait;
		}
		break;
		
		case decrement:
		if (A0 && A1){
			state = reset;
		}else if(A1){
			state = decrement;
		}else{
			state = wait;
		}
		break;
		
		case reset:
		if (A0 && A1){
			state = reset;
		}else{
			state = init;
		}
		break;
		
		default:
		state = start;
		break;
	}
	
	switch(state){		//actions
		case start:
		break;
		
		case init:
		cnt = 0x00;
		PORTB = 0x00;
		break;
		
		case wait:
		cnt = 0x00;
		break;
		
		case increment:
		if( cnt > 0 && cnt < 15){
			if(PORTB < 9 && !(cnt % 5)){
				PORTB = PORTB + 1;
			}
		}else if (cnt >= 15){
			if(PORTB < 9 && !(cnt & 2)){
				PORTB = PORTB + 1;
			}
		}else{
			if(PORTB < 9){
				PORTB = PORTB + 1;
			}
		}
				
		cnt++;
		break;
		
		case decrement:
		if( cnt > 0 && cnt < 15){
			if(PORTB > 0 && !(cnt % 5)){
				PORTB = PORTB - 1;
			}
		}else if (cnt >= 15){
			if(PORTB > 0 && !(cnt & 2)){
				PORTB = PORTB - 1;
			}
		}else{
			if(PORTB > 0){
				PORTB = PORTB - 1;
			}
		}

		cnt++;
		break;
		
		case reset:
		cnt = 0x00;
		PORTB = 0x00;
		break;
		
		default:
		break;
		
	}
	
}


int main(void)
{
	/* Replace with your application code */
	
	DDRA = 0x00; PORTA = 0xFF;	//input
	DDRB = 0xFF; PORTB = 0x00;	//output
	
	state = start;
	
	TimerSet(200);
	TimerOn();
		
	while(1){
		tick();		
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
	
	
}