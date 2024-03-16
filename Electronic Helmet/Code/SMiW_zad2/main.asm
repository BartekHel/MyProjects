//////////////////////////////////////////////////////////////////////////////
// Laboratory AVR Microcontrollers Part1
// Program template for ASM lab 7
// Please fill in this information before starting coding
// Authors:
//1.Bartosz Heliñski
// Group: 1
// Section: 1
// Task number: 2
//
// Version: 2020v3.0
//////////////////////////////////////////////////////////////////////////////

.nolist ;quartz assumption 4Mhz
.include "m2560def.inc"
 
//////////////////////////////////////////////////////////////////////////////
// Change this variable to test different values from 0 to 100
.equ xlength =  100
;//////////////////////////////////////////////////////////////////////////////
; EEPROM - data non-volatile memory segment Please don't use
.ESEG 
 
;//////////////////////////////////////////////////////////////////////////////
; StaticRAM - data memory.segment
.DSEG 
.ORG 0x200; may be omitted this is the default value
; Destination table (xlengthx bytes). 
TAB_RAM: .BYTE xlength
 
;//////////////////////////////////////////////////////////////////////////////
; CODE - Program memory segment
; Please Remember that it is "word" address space
;
.CSEG  
.org 0x0000 ; may be omitted this is default value 
jmp RESET   ; Reset Handler
   
 
;//////////////////////////////////////////////////////////////////////////////
; Program start
RESET:
 
    cli         ; disable all interrupts
//  Set stack pointer to the top of RAM
    ldi R16, HIGH(RAMEND)
    out SPH, R16
    ldi R16, LOW(RAMEND)
    out SPL, R16

	ldi r17, high(xlength) ;sprawdzanie dlugosci TAB_RAM
	ldi r18, low(xlength)
 
// 1. Place here code related to initialization of all ports 
// for instance:   port A as input and no pullups 
// DDRA=0x00
// PORTA=0x00
//    port B as output and initial value FF
// DDRB=0xFF
// PORTB=0xFF
    // 
    // Writing a logic one to PINxn toggles the value of PORTxn, regardless of the value of DDRxn
    // Note that the SBI instruction can be used to toggle one single bit in a port.
 
    // for instance: sbi DDRB, 0
 
 


// 2. Enable interrupts if needed
//  sei
    
 


//------------------------------------------------------------------------------
// 3. Load initial values of index registers 
//  Z, X, Y 
 
 
 ldi YH, high(TAB_RAM)
 ldi YL, low(TAB_RAM)

 // Sprawdzenie czy rozmiar TAB_RAM jest miedzy 3 a 300
 ldi r19, high(xlength)
 cpi r19, 0x02
 brsh End ; wiekszy lub rowny 512
 ldi r20, low(xlength)
 cpi r19, 0
 breq CheckLower
 cpi r20, 0x2d
 brsh End ; wiekszy lub rowny 301
 rjmp LoadStartOfTabRom

 CheckLower:
	cpi r20, 0x03
	brlo End ; mniejszy niz 3


 LoadStartOfTabRom: ;jesli TAB_RAM jest wieksze od TAB_ROM, trzeba wrocic na poczatek i zresetowac test parzystosci
	ldi r21, 0xFF ;sprawdzanie parzystosci
	ldi ZH, high(TAB_ROM<<1)
	ldi ZL, low(TAB_ROM<<1)

 MainLoop:
	lpm r19, Z+
	lpm r20, Z ;w tych rejestrach sa dwa kolejne bajty z TAB_ROM, drugiego jeszcze nie kopiujemy
	cpi r19, 0x00 ;sprawdzenie, czy koniec TAB_ROM
	brne Copy
	cpi r20, 0x00
	breq CheckEmpty ;to jest koniec TAB_ROM, trzeba sprawdzic, czy nie jest puste

 Copy:
	com r21
	cpi r21, 0 ;rejestr jest negowany, wiec co drugie wykonanie bedzie sie skladac z samych zer, wtedy pomijane jest kopiowanie
	breq MainLoop
	st Y+, r19
	dec r18
	cpi r18, 0
	brne MainLoop

 // W dolnym bajcie moze byc 0, ale trzeba sprawdzic, czy w gornym nie jest 1
 // Jezeli jest, to trzeba zmniejszyc gorny bajt (ustawic 0, bo moze on miec tylko wartosci 0 lub 1 dla zadanego przedzialu)
 // W kolejnej iteracji MainLoop na dolnym bajcie zostanie wykonany rozkaz dec, ktory zmieni wartosc rejestru z 0x00 na 0xFF
 cpi r17, 0
 breq End
 ldi r17, 0
 rjmp MainLoop
 
 
//------------------------------------------------------------------------------
// Program end - Ending loop
//------------------------------------------------------------------------------
End:
    rjmp END

// Sprawdzenie polega na porownaniu oryginalnej wartosci xlength z ta w rejestrach r17 i r18
// Jezeli sa takie same, to znaczy ze nie zostalo wykonane zadne kopiowanie, mimo ze wskaznik jest na koncu tablicy - jest ona pusta lub ma dlugosc 1 (nie ma bajtow nieparzystych)
// Jezeli sa rozne, to mozna kontynuowac kopiowanie od poczatku tablicy. Zapobiega to nieskonczonej petli
CheckEmpty:
ldi r19, high(xlength)
ldi r20, low(xlength)
cp r17, r19
brne LoadStartOfTabRom
cp r18, r20
brne LoadStartOfTabRom
rjmp End
 
//------------------------------------------------------------------------------
// Table Declaration -  place here test values
// Test with other table values and different begin addresses of a table (also above 0x8000)
//
//.org 0x8000
TAB_ROM: 	.db 	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x1F
		.db	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F, 0x1F
		.db	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F
		.db	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
		.db	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
		.db	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F
		.db	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F
		.db	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
		.db	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F
		.db	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F
		.db	0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaA, 0xaB, 0xaC, 0xaD, 0xAE, 0xAF
		.db	0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF
		.db	0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF
		.db	0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF
		.db	0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0 
			// please correct end of this table according to the guidelines given by the teacher 
		.db 	0x00,0x00
.EXIT
//------------------------------------------------------------------------------