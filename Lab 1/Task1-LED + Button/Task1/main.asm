;
; Task1.asm
;
; Created: 29/09/2022 16:32:05
; Author : Mario
;

; Pin Constant Values
; PB1 - 9 Switch
; PB2 - 10 RED
; PB3 - 11 YELLOW
; PB4 - 12 GREEN

declarations:
.def circuit = r16
ldi r18, 78
ldi r19, 29
ldi r20, 13

start:
	call reset;
	call switch;
	call green_led;
	call delay;
	call off_leds
	call delay;
	call yellow_led;
	call delay;
	call off_leds
	call delay;
	call red_led;
	call delay;
	call off_leds
	call delay;
	jmp start;

reset:
	; Set pins 8-13 to output mode and the rest to input
	ldi		r19, (0<<PB7)|(0<<PB6)|(0<<PB5)|(1<<PB4)|(1<<PB3)|(1<<PB2)|(0<<PB1)|(0<<PB0) ; 1 for HIGH, 0 for LOW
	out		DDRB, r19 ; DDRB = 0x24 (The port B Data Direction Register)
	; Set all pins to low
    ldi		r24,(0<<PB7)|(0<<PB6)|(0<<PD5)|(0<<PB4)|(0<<PB3)|(0<<PB2)|(0<<PB1)|(0<<PB0) ; 1 for HIGH, 0 for LOW
	out		PORTB, r24 ; PORTB = 0x25 (The Port B Data Register) This is used of output, for input we use PINB in this case
	ret

switch:
	in circuit, PINB ; get state of pins on Port B
	andi circuit, (1<<PB0) ; mask to get the value for just input pin 9
	cpi circuit, 1 ; if pressed => output high
	brne switch ; if button != 1, loop switch again
	ret

green_led:
	//Green LED
	ldi circuit, (1<<PB4); Tun on LED
	out PINB, circuit ; toggles the state of the pins
	ret

yellow_led:
	//Yellow LED
	ldi circuit, (1<<PB3); Tun on LED
	out PINB, circuit ; toggles the state of the pins
	ret

red_led:
	//Red LED
	ldi circuit, (1<<PB2); Tun on LED
	out PINB, circuit ; toggles the state of the pins
	ret	

off_leds:
	; Set all pins to low
    ldi		r24,(0<<PB7)|(0<<PB6)|(0<<PD5)|(0<<PB4)|(0<<PB3)|(0<<PB2)|(0<<PB1)|(0<<PB0) ; 1 for HIGH, 0 for LOW
	out		PORTB, r24 ; PORTB = 0x25 (The Port B Data Register) This is used of output, for input we use PINB in this case
	ret

delay:
	dec r20
	brne delay
	dec r19
	brne delay
	dec r18
	brne delay
	nop
	ldi r18, 78
	ldi r19, 29
	ldi r20, 13
	ret

