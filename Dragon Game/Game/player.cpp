#include "player.h"

namespace arduino {
	Player::Player(const pcons& pos) {
		this->pos = pos;
	}

	Player::Player(int16 x, int16 y) {
		this->pos = { x, y };
	}

	bool Player::isHit(int16 x, int16 y) {
		if (x == this->pos[0] && y == this->pos[1])
			return true;
		return false;
	}
}