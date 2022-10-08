;
; Task1.asm
;
; Created: 29/09/2022 16:32:05
; Author : Mario
;

; Pin Constant Values
; PB2 - 10 RED
; PB3 - 11 YELLOW
; PB4 - 12 GREEN

start:
	; Pag 100 from the datasheet. Port B Data Direction Register
	; utilises address 0x24, so r24
	; Set pins 8-13 to high
    ldi		r24,(0<<PB7)|(0<<PB6)|(0<<PD5)|(1<<PB4)|(1<<PB3)|(1<<PB2)|(0<<PB1)|(0<<PB0) ; 1 for HIGH, 0 for LOW
	out		PORTB, r24 ; PORTB = 0x25 (The Port B Data Register) This is used of output, for input we use PINB in this case

	; Set pins 8-13 to output mode
	ldi		r19, (0<<PB7)|(0<<PB6)|(0<<PB5)|(1<<PB4)|(1<<PB3)|(1<<PB2)|(0<<PB1)|(0<<PB0) ; 1 for HIGH, 0 for LOW
	out		DDRB, r24 ; DDRB = 0x24 (The port B Data Direction Register)


loop:
rjmp loop