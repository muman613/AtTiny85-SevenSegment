/*
 * tinyShifter.cpp
 *
 * Created: 2/23/2020 2:50:16 PM
 * Author : muman
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
//#include "ArduinoPins.h"
#include "ShiftRegister.h"

//  1     2   3     4   5
// LATCH CLK DATA  GND VCC

// attiny85     74595
//  5 (PB0)  -    3
//  6 (PB1)  -    2
//  7 (PB2)  -    1


#define DATA		0
#define CLOCK		1
#define LATCH		2 

ShiftRegister reg(DATA, CLOCK, LATCH, LSBFIRST);

uint8_t patternBuffer[] = {
	0b11111100,			// 0
	0b01100000,			// 1
	0b11011010,			// 2
	0b11110010,			// 3
	0b01100110,			// 4
	0b10110110,			// 5
	0b10111110,			// 6
	0b11100000,			// 7
	0b11111110,			// 8
	0b11100110,			// 9
	0b01101100,			// 
	0b10010010,
	0b11000110,
	0b00111010,
};

int patternCnt = (sizeof(patternBuffer)/sizeof(uint8_t));
bool bRunning = false;

void updateDisplay();


ISR(TIMER1_COMPA_vect)
{
	if (bRunning) {
		updateDisplay();
	}
}

static inline void initTimer1(void)
{
	cli();
	TCCR1 |= (1 << CTC1);  // clear timer on compare match
	TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11); //clock prescaler 8192
	OCR1C = 100; // compare match value
	TIMSK |= (1 << OCIE1A); // enable compare match interrupt
	sei();
}

void setup() {
	initTimer1();
	reg.begin();
	reg.write(0);
}

void segmentTest() {
	for (int i = 0 ; i < 8 ; i++) {
		reg.write(1 << (7 - i));
		_delay_ms(1000);
	}
}

void updateDisplay() {
	static int index = 0;
	reg.write(patternBuffer[index]);
	index = index+1;
	if (index == 10) {
		index = 0;
	}
}

void loop() {
	
    while (1) {
// 		updateDisplay();
// 		_delay_ms(250);
    }
}

int main(void)
{
	setup();
	segmentTest();
	bRunning = true;
	loop();
}

