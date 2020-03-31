/*
 * ShiftRegister.h
 *
 *  Created on: Aug 6, 2019
 *      Author: muman
 */

#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

#include <stdint.h>
//#include "ArduinoPins.h"
//#include "main.h"

// Shift order
typedef enum {
	// Shift order
	LSBFIRST,
	MSBFIRST,
} SHIFT_ORDER;


class ShiftRegister {
public:
	//ShiftRegister();
	ShiftRegister(int dataPin, int clockPin, int latchPin, SHIFT_ORDER order);
	~ShiftRegister();

	bool 		begin(int dataPin = -1, int clockPin = -1, int latchPin = -1, int order = -1);
	void 		write(uint8_t value);

private:

//	void	 	digitalWrite(int pin, GPIO_PinState value);
	void		shiftOut(uint8_t val);

	int 		_dp;	// data pin
	int 		_cp;	// clock pin
	int 		_lp;	// latch pin
	SHIFT_ORDER _order;
};

#endif /* SHIFTREGISTER_H_ */
