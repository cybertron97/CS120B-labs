/*
 * taror002_tisla002_lab7_part2.c
  * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #7  Exercise #2
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


enum CM_states {start, output} CM_state;
enum TL_states {TL_SMStart, TL_T0, TL_T1, TL_T2} TL_state;
enum BL_states {BL_SMStart, BL_LedOff, BL_LedOn} BL_state;
	
volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

unsigned char threeLEDs = 0;
unsigned char blinkingLED = 0;

unsigned char count = 0;

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
	
	switch(CM_state){	//transitions
		case start:
		CM_state = output;
		break;
		
		case output:
		CM_state = output;
		break;		
		
		default:
		CM_state = start;
		break;	
	}
	
	switch(CM_state){ //actions
		case start:
		break;
		
		case output:
		PORTB = threeLEDs | blinkingLED;
		break;

		default:
		break;
		
		
	}
	
}

void tick_ThreeLEDs(){
	
	switch(TL_state){	//transitions
		case TL_SMStart:
		TL_state = TL_T0;
		break;
		
		case TL_T0:
		TL_state = TL_T1;
		break;
		
		case TL_T1:
		TL_state = TL_T2;
		break;
		
		case TL_T2:
		TL_state = TL_T0;
		break;
		
		default:
		TL_state = TL_SMStart;
		break;
		
	}
	
	switch(TL_state){	//actions
		case TL_SMStart:
		threeLEDs = 0x00;
		break;
		
		case TL_T0:
		threeLEDs = 0x01;
		break;
		
		case TL_T1:
		threeLEDs = 0x02;
		break;
		
		case TL_T2:
		threeLEDs = 0x04;
		break;
		
		default:
		break;
		
	}
	
}

void tick_BlinkLED(){

	switch(BL_state){	//transitions
		case BL_SMStart:
		BL_state = BL_LedOff;
		break;
		
		case BL_LedOff:
		BL_state = BL_LedOn;
		break;
		
		case BL_LedOn:
		BL_state = BL_LedOff;
		break;
		
		default:
		BL_state = BL_SMStart;
		break;
		
	}
	
	switch(BL_state){	//actions
		case BL_SMStart:
		blinkingLED = 0x00;
		break;
		
		case BL_LedOff:
		blinkingLED = 0x08;
		break;
		
		case BL_LedOn:
		blinkingLED = 0x00;
		break;
		
		default:
		break;
	}
	
}


int main(void)
{
    /* Replace with your application code */
   
	//DDRA = 0x00; PORTA = 0xFF;	//input
	DDRB = 0xFF; PORTB = 0x00;		//output
	
	TimerSet(100);
	TimerOn();
	
	TL_state = TL_SMStart;
	BL_state = BL_SMStart;
	CM_state = start;
		
	while(1){
		count++;
		
		if (count == 3 || count == 6 || count == 9)		
		{
			tick_ThreeLEDs();
		}
		
		if (count == 10){
			tick_BlinkLED();
			count = 0;
		}
		
		tick();
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
		
    
}

