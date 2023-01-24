#include "button.h"
#include "Arduino.h"

namespace arduino {
	Button::Button(int16 pin, int16 counter) {
		this->state = digitalRead(pin);
		this->pin = pin;
		this->counter = counter;
	}

	bool Button::isPressed() {
		if (this->state)
			return true;
		return false;
	}
}