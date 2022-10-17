/*
 * Task3.c
 *
 * Created: 17/10/2022 10:34:16
 * Author : Mario
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include<stdio.h>
#include<stdlib.h>


int main ()
{
	//Set as outputs pins 5, 6, 7, 8, 9, 10, 11, 12 and 13
	DDRD = (1 << 5)|(1 << 6)|(1 << 7);
	DDRB = (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3)|(1 << 4)|(1 << 5); //PB0, PB1, PB2, PB3 and PB4 as an output
	EIMSK = (1 << INT0); //enable external interrupt 0
	EICRA = 0x03; //make INTO rising edge triggered
	sei (); //enable interrupts
	while (1){
			}; //wait here
}
ISR (INT0_vect) //ISR for external interrupt 0
{	
	//Tun on and off all the leds in PORTD that are enabled (5, 6, and 7)
	for(int i = 5; i < 8; i++){
		PORTD |= (1 << i);
		delay_ms_short();
		PORTD &= ~(1 << i);
	}
	//Tun on and off all the leds in PORTB that are enabled (8, 9, 10, 11, 12 and 13)
	for(int i = 0; i < 6; i++){
			PORTB |= (1 << i);
			delay_ms_short();
			PORTB &= ~(1 << i);
	}
	// Flash all the leds that are enabled on and off 3 times (pins 5 to 13)
	for(int i = 0; i < 3; i++){
		PORTD |= (1 << 5)|(1 << 6)|(1 << 7);
		PORTB |= (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3)|(1 << 4)|(1 << 5); //toggle PORTB.2
		delay_ms_short(); //wait 1 sec
		PORTB &= ~((1 << 0)|(1 << 1)|(1 << 2)|(1 << 3)|(1 << 4)|(1 << 5)); //untoggle PORTB.2
		PORTD &= ~((1 << 5)|(1 << 6)|(1 << 7));
		delay_ms_short();
	}
	//Generate a random number from 1 to 6 
	int randNumber = 1 + ( rand() % 6 );
	//Set in the 9x9 led matrix the number generated simulating a dice
	switch(randNumber){
		case 1: 
			PORTB |= (1 << 1);
			break;
		case 2: 
			PORTB |= (1 << 0)|(1 << 2);
			break;
		case 3: 
			PORTD |= (1 << 5); PORTB |= (1 << 1)|(1 << 5);
			break;
		case 4: 
			PORTD |= (1 << 5)|(1 << 7); PORTB |= (1 << 3)|(1 << 5);
			break;
		case 5: 
			PORTD |= (1 << 5)|(1 << 7); PORTB |= (1 << 3)|(1 << 1)|(1 << 5);
			break;
		case 6: 
			PORTD |= (1 << 5)|(1 << 6)|(1 << 7); PORTB |= (1 << 3)|(1 << 4)|(1 << 5);
			break;
	}
	//Wait 4s in total
	delay_ms();
	delay_ms();
	//Turn off all leds
	PORTD = 0x00;
	PORTB = 0x00;
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
	
	OCR1A = 34286; //delay
	TCCR1A = 0x00; //normal mode but operating CTC?0
	TCCR1B = (1<<CS12)|(1<<CS10); //set the prescalar as 1024
	while((TIFR1 &(1<<OCF1A))==0) //wait till the timer overflows flag is SET
	{
	}
	TCCR1B = 0x00; // Turn off clock1
	TCNT1 = 0; //Reset counter
	TIFR1 |= 1<<OCF1A; //Clear time overflow flag
	
	
}

void delay_ms_short()
{	
	OCR1A = 5000; //delay
	TCCR1A = 0x00; //normal mode but operating CTC?0
	TCCR1B = (1<<CS12)|(1<<CS10); //set the prescalar as 1024
	while((TIFR1 &(1<<OCF1A))==0) //wait till the timer overflows flag is SET
	{
	}
	TCCR1B = 0x00; // Turn off clock1
	TCNT1 = 0; //Reset counter
	TIFR1 |= 1<<OCF1A; //Clear time overflow flag
	
	
}

