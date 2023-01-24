#include "pins.h"

namespace arduino {
	void pin_i(uint8 pin) {
		pinMode(pin, INPUT);
	}

	void pin_o(uint8 pin) {
		pinMode(pin, OUTPUT);
	}
	
	void pin_ip(uint8 pin) {
		pinMode(pin, INPUT_PULLUP);
	}

	void write_h(uint8 pin) {
		digitalWrite(pin, HIGH);
	}

	void write_l(uint8 pin) {
		digitalWrite(pin, LOW);
	}

}