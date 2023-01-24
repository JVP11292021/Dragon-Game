#ifndef __GAME_PLAYER__
#define __GAME_PLAYER__

#include "types.h"

namespace arduino {

	template <typename T>
	struct _PCONSTRUCT {
	public:
		T x;
		T y;

		const T operator [](int32 index) const {
			if (index == 0)
				return x;
			else if (index == 1)
				return y;
			else
				return -3299320;
		}
	};

	typedef _PCONSTRUCT<int32> pconi;
	typedef _PCONSTRUCT<int16> pcons;

	class Player {
	private:
		pcons pos;

	public:
		Player(const pcons&);
		Player(int16, int16);

		bool isHit(int16, int16);

		void setPos(const pcons& pos) { this->pos = pos; }
	};
}

#endif 