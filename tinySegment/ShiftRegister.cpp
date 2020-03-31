/*
 * ShiftRegister.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: muman
 */

#define F_CPU 8000000

//#include "ArduinoPins.h"
#include "ShiftRegister.h"
#include <avr/io.h>
#include <util/delay.h>

enum {
	OUTPUT_LOW,
	OUTPUT_HIGH,
};

enum  {
	PIN_INPUT,
	PIN_OUTPUT,
};

void digitalWrite(int pin, int value) {
	if (value == OUTPUT_LOW) {
		PORTB &= ~(1 << pin);
	} else if (value == OUTPUT_HIGH) {
		PORTB |= (1 << pin);
	}
}

/**
 * Constructor
 */
//ShiftRegister::ShiftRegister() {
//
//}

/**
 * Constructor
 */
ShiftRegister::ShiftRegister(int dataPin, int clockPin, int latchPin,
		SHIFT_ORDER order) :
		_dp(dataPin), _cp(clockPin), _lp(latchPin), _order(order)
{

}

/**
 * Destructor
 */
ShiftRegister::~ShiftRegister() {

}

bool ShiftRegister::begin(int dataPin, int clockPin, int latchPin, int order) {
	if (dataPin != -1) {
		_dp = dataPin;
	}
	if (clockPin != -1) {
		_cp = clockPin;
	}
	if (latchPin != -1) {
		_lp = latchPin;
	}
	if (_order != -1) {
		_order = (SHIFT_ORDER) order;
	}
	_order = LSBFIRST;

	// Set all pins to output	
	DDRB |= (1 << _dp)|(1 << _cp)|(1 << _lp);
	PORTB &= ~((1<<_dp)|(1<<_cp)|(1<<_lp));
	
	return true;
}

/**
 * Shift data out to the shift-register
 *
 */
void ShiftRegister::shiftOut(uint8_t val) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		if (_order == LSBFIRST)
			digitalWrite(_dp, (val & (1 << i)) ? 1 : 0);
//		else
//			digitalWrite(_dp, (val & (1 << (7 - i))) ? 1 : 0);

		digitalWrite(_cp, OUTPUT_HIGH);
		digitalWrite(_cp, OUTPUT_LOW);
//		_delay_ms(10);
	}
	digitalWrite(_dp, 0);

}

/**
 *	Writes the value to the shift-register, ultimately displaying on the LED's
 */
void ShiftRegister::write(uint8_t value) {
	digitalWrite(_lp, OUTPUT_LOW);
	shiftOut(value);
	digitalWrite(_lp, OUTPUT_HIGH);
}
