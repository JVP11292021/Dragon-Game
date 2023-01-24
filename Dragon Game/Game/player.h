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
		LedControl control;
		bool hit = false;

	public:
		Player(const LedControl&, const pcons&);
		Player(const LedControl&, int16, int16);

		bool isHit(int16, int16);

		void setPos(const pcons& pos) { this->pos = pos; this->control.setDigit(0, pos[0], pos[1], true); }
		void set() { this->control.setDigit(0, pos[0], pos[1], true); }

		void move(const Movements&);
	};
}

#endif 