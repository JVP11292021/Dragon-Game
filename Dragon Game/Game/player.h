#ifndef __GAME_PLAYER__
#define __GAME_PLAYER__

#include "types.h"
#include "LedControl.h"

namespace arduino {

	template <typename T>
	struct _PCONSTRUCT {
	public:
		T x;
		T y;

		T operator [](int32 index) const {
			if (index == 0)
				return x;
			else if (index == 1)
				return y;
			else
				return NULL;
		}
	};

	enum class Movements {
		NONE = -1,
		UP, DOWN,
		LEFT, RIGHT
	};

	typedef _PCONSTRUCT<int32> pconi;
	typedef _PCONSTRUCT<int16> pcons;

	class Player {
	private:
		pcons pos;
		bool hit = false;

	public:
		Player(LedControl&, const pcons&);
		Player(LedControl&, int16, int16);

		bool isHit(int16, int16);

		void setPos(LedControl& control, const pcons& pos) { this->pos = pos; control.setLed(0, pos[0], pos[1], true); }
		void set(LedControl& control) { control.setLed(0, pos[0], pos[1], true); }

		void move(LedControl&, const Movements&);
	};
}

#endif 