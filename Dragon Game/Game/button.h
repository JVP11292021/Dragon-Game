#ifndef __BUTTON__
#define __BUTTON__

#include "types.h"

namespace arduino{

	class Button {
	private:
		int16 state = 0;
		int16 pin = 0;
		int16 counter;

	public:
		Button(int16 pin, int16 counter = 3);
		bool isPressed();

		inline void add() { if (counter + 1 < 7) this->counter++; }
		inline void sub() { if (counter - 1 > 0) this->counter--; }

		inline int16 getState() { return state; }
		inline int16 getPin() { return pin; }
		inline int16 getCounter() { return counter; }

		inline void setState(int16 state) { this->state = state; }

	};

}

#endif