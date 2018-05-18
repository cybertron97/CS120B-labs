/*
 * taror002_lab4_part2.c
 *
 * Created: 4/18/2018 9:44:08 AM
 * Author : Tanish
 */

#include <avr/io.h>

enum LA_States {start, init, lowfuel, lowfuel1, lowfuel2, lowfuel3, lowfuel4, lowfuel5, lowfuel_wait, lowfuel_wait1, lowfuel_wait2, lowfuel_wait3, lowfuel_wait4, lowfuel_wait5} LA_State;

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)
#define A2 (~PINA & 0x04)
#define A3 (~PINA & 0x08)

#define tmp (A0 | A1 | A2 | A3)

unsigned char tmpA = 0x00;
unsigned char tmp1 = 0x00;
	

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void tick(){
	switch(LA_State){	//transitions 
		case start:
		LA_State = init;
		break;
		
		case init:
		if(tmp >= 0 && tmp <= 2){
			LA_State = lowfuel;
		}else if(tmp >= 3 && tmp <= 4){
			LA_State = lowfuel1;
		}else if(tmp >= 5 && tmp <= 6){
			LA_State = lowfuel2;
		}else if(tmp >= 7 && tmp <= 9){
			LA_State = lowfuel3;
		}else if(tmp >= 10 && tmp <= 12){
			LA_State = lowfuel4;
		}else if(tmp >= 13 && tmp <= 15){
			LA_State = lowfuel5;
		}
		break;
		
		case lowfuel:
			LA_State = lowfuel_wait;
		break;
		
		case lowfuel1:
			LA_State = lowfuel_wait1;
		break;
		
		case lowfuel2:
			LA_State = lowfuel_wait2;
		break;
		
		case lowfuel3:
			LA_State = lowfuel_wait3;
		break;
		
		case lowfuel4:
			LA_State = lowfuel_wait4;
		break;
		
		case lowfuel5:
			LA_State = lowfuel_wait5;
		break;
		
		case lowfuel_wait:
		if(tmpA == tmp){
			LA_State = lowfuel_wait;
		}else{
			LA_State = init;
		}
		break;
		
		case lowfuel_wait1:
		if(tmpA == tmp){
			LA_State = lowfuel_wait1;
		}else{
			LA_State = init;
		}
		break;
		
		case lowfuel_wait2:
		if(tmpA == tmp){
			LA_State = lowfuel_wait2;
		}else{
			LA_State = init;
		}
		break;
		
		case lowfuel_wait3:
		if(tmpA == tmp){
			LA_State = lowfuel_wait3;
		}else{
			LA_State = init;
		}
		break;
		
		case lowfuel_wait4:
		if(tmpA == tmp){
			LA_State = lowfuel_wait4;
		}else{
			LA_State = init;
		}
		break;
		
		case lowfuel_wait5:
		if(tmpA == tmp){
			LA_State = lowfuel_wait5;
		}else{
			LA_State = init;
		}
		break;
		
		default:
			LA_State = start;
		break;
	}
	
	switch(LA_State){	//actions
		
		case start:
		PORTC = 0x00;
		break;
		
		case init:
		tmp1 = 0x00;	
		break;
		
		case lowfuel:
		tmpA = tmp;
			
		tmp1 = SetBit(tmp1,6,1);
		tmp1 = SetBit(tmp1,5,1);
		
		PORTC = tmp1;
		break;
		
		case lowfuel1:
		tmpA = tmp;
			
		tmp1 = SetBit(tmp1,6,1);
		tmp1 = SetBit(tmp1,5,1);
		tmp1 = SetBit(tmp1,4,1);
		
		PORTC = tmp1;		
		break;
		
		case lowfuel2:
		tmpA = tmp;
		
		tmp1 = SetBit(tmp1,5,1);
		tmp1 = SetBit(tmp1,4,1);
		tmp1 = SetBit(tmp1,3,1);
		
		PORTC = tmp1;
		break;
		
		case lowfuel3:
		tmpA = tmp;
		
		tmp1 = SetBit(tmp1,5,1);
		tmp1 = SetBit(tmp1,4,1);
		tmp1 = SetBit(tmp1,3,1);
		tmp1 = SetBit(tmp1,2,1);
			
		PORTC = tmp1;
		break;
		
		case lowfuel4:
		tmpA = tmp;
			
		tmp1 = SetBit(tmp1,5,1);
		tmp1 = SetBit(tmp1,4,1);
		tmp1 = SetBit(tmp1,3,1);
		tmp1 = SetBit(tmp1,2,1);
		tmp1 = SetBit(tmp1,1,1);
			
		PORTC = tmp1;
		break;
		
		case lowfuel5:
		tmpA = tmp;
		
		tmp1 = SetBit(tmp1,5,1);
		tmp1 = SetBit(tmp1,4,1);
		tmp1 = SetBit(tmp1,3,1);
		tmp1 = SetBit(tmp1,2,1);
		tmp1 = SetBit(tmp1,1,1);
		tmp1 = SetBit(tmp1,0,1);
		
		PORTC = tmp1;
		break;
		
		case lowfuel_wait:
		break;
		
		case lowfuel_wait1:
		break;
		
		case lowfuel_wait2:
		break;
		
		case lowfuel_wait3:
		break;
		
		case lowfuel_wait4:
		break;
		
		case lowfuel_wait5:
		break;
		
		default:
		break;
	}
}

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	PORTC = 0x00;
	
	LA_State = start;
	
	while(1){
		tick();
	}
	
}
