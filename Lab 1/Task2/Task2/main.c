/*
 * Task2.c
 *
 * Created: 13/10/2022 15:37:36
 * Author : Mario
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
// Debouncing switch circuit has been implemented (Clock pin held low - pulse high)

int main ()
{
	DDRB = (1 << 2)|(1 << 3)|(1 << 4); //PB2, PB3 and PB4 as an output
	EIMSK = (1 << INT0); //enable external interrupt 0
	EICRA = 0x03; //make INTO rising edge triggered
	sei (); //enable interrupts
	while (1){
			}; //wait here
}
ISR (INT0_vect) //ISR for external interrupt 0
{
	PORTB |= (1 << 2); //toggle PORTB.2
	delay_ms(); //wait 1 sec
	PORTB &= ~(1 << 2); //untoggle PORTB.2
	PORTB |= (1 << 3); //toggle PORTB.3
	delay_ms(); //wait 1 sec
	PORTB &= ~(1 << 3); //untoggle PORTB.3
	PORTB |= (1 << 4); //toggle PORTB.4
	delay_ms(); //wait 1 sec
	PORTB &= ~(1 << 4); //untoggle PORTB.4
}

void delay_ms()
{
	// 16MHz (Because we use timer 1, 16 bits) /1024 (Because we are going to use the prescaler of timer 1)
	// 16MHz/1024 = 15625 (Cycles in a s)
	//1/15625=0.000064 (T=1/f)
	//(M+f) => (14+7)*100 = 2s of delay
	//2/0.000064 = 31250 (clock cycles to make 2s)
	//2^16 = 65536 (clock is 16, that means 655396 bites)
	//65536-31250 = 34286 (Start number for the counter)
	
	OCR1A = 34286; //2s delay
	TCCR1A = 0x00; //normal mode but operating CTC?0
	TCCR1B = (1<<CS12)|(1<<CS10); //set the prescaler as 1024
	while((TIFR1 &(1<<OCF1A))==0) //wait till the timer overflows flag is SET
	{
	}
	TCCR1B = 0x00; // Turn off clock1
	TCNT1 = 0; //Reset counter
	TIFR1 |= 1<<OCF1A; //Clear time overflow flag
	
	
}
