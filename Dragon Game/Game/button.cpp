#include "button.h"
#include "Arduino.h"

namespace arduino {
	Button::Button(int16 pin, const Movements& movements, int16 counter) {
		this->state = digitalRead(pin);
		this->pin = pin;
		this->counter = counter;
		this->movements = movements;
	}

	bool Button::isPressed() {
		if (this->state)
			return true;
		return false;
	}
}