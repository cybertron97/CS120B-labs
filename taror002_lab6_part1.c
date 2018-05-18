/*
 * taror002_lab6_part1.c
 *
 * Partner(s) Name & E-mail: Takbir Islam - tisla002@ucr.edu
 * Lab Section: 26
 * Assignment: Lab #6  Exercise #1
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */
#include <avr/io.h>
#include "io.c"

#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B 	= 0x0B;	// bit3 = 1: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: prescaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A 	= 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register

	TIMSK1 	= 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1 = 0;

	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	_avr_timer_cntcurr = _avr_timer_M;

	//Enable global interrupts
	SREG |= 0x80;	// 0x80: 1000000
}

void TimerOff() {
	TCCR1B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { 	// results in a more efficient compare
		TimerISR(); 				// Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
enum States { start, initial , wait, increment, decrement } state;      
unsigned char total;                      
unsigned char cnt;       
unsigned char a ;           

void Tick()
{
	a = ~PINA; 
	switch (state)
	{
		case start: 
		state = initial; break; 
		case initial:
		state = wait; break; 
		case wait: 
		if (a == 0x01 )
		{
			if (total<9) 
			total= total+1; 
			else total; 
			LCD_Cursor(1); LCD_WriteData(total+'0'); 		
			state = increment; 	
			cnt++; 
		} 
		else if (a==0x02)
		{
			if (total > 0 )
			total=total-1; 
			else total; 
			LCD_Cursor(1); LCD_WriteData(total+'0'); 	
			state = decrement; cnt++; 
		}
		else if (a == 0x03)
		{
			state = initial; 
		}
		break; 
		case increment: 
		if (a == 0x01 && !(cnt % 8 ))
		{
			if (total<9)
			total= total+1;
			else total;
			LCD_Cursor(1); LCD_WriteData(total+'0');
			
		}
		else if (a == 0x03) state = initial; 
		else if (a ^ 0x01 ) {state =wait; cnt =0 ; } break; 
			
			case decrement: 
			if (a==0x02 && !(cnt % 8))
			{
				if (total > 0 )
				total = total-1;
				else total;
				LCD_Cursor(1); LCD_WriteData(total+'0');
				
			}
			else if (a==0x03) state = initial; 
			else if (a ^ 0x02) {state = wait; cnt=0; } break; 
				default: state = start; break; 
	}
	switch (state)
	{
		case initial: LCD_ClearScreen(); 
		total = 0 , cnt =0 ; 
		LCD_Cursor(1); LCD_WriteData(total+'0'); //dont know why but doesnt run without this statement 
		break; 
		case increment: 
		if (a & 0x01)
		{
			cnt= cnt+1 ; 
		}
		else cnt; break;  
		case decrement: 
		if (a & 0x02) 
		{
			cnt =cnt+1; 
		} 
		else cnt; break;
		default : break; 
	}
	
}
int main(void)
{
	 DDRA = 0x00; PORTA = 0xFF;
	 DDRC = 0xFF; PORTC = 0x00; 
	 DDRD = 0xFF; PORTD = 0x00;
	  
	  LCD_init(); 
	  TimerSet(125);
	 TimerOn();
	 
    /* Replace with your application code */
    while (1) 
    {
		Tick(); 
		while (!TimerFlag);
		TimerFlag=0; 
    }
}

