#ifndef __ARDUINO_PINS__
#define __ARDUINO_PINS__

#include "Arduino.h"
#include "types.h"

namespace arduino {

	void pin_i(uint8 pin);
	void pin_o(uint8 pin);
	void pin_ip(uint8 pin);

	void write_h(uint8 pin);
	void write_l(uint8 pin);

}

#endif