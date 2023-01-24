#include "player.h"

namespace arduino {
	Player::Player(const LedControl& control, const pcons& pos) {
		this->pos = pos;
		this->control = control;
		this->control.setIntensity(0, 15);
		this->control.setLed(0, pos[0], pos[1], true);
	}

	Player::Player(const LedControl& control, int16 x, int16 y) {
		this->pos = { x, y };
		this->control = control;
		this->control.setIntensity(0, 15);
		this->control.setLed(1, x, y, true);
	}

	bool Player::isHit(int16 x, int16 y) {
		if (x == this->pos[0] && y == this->pos[1])
			return true;
		return false;
	}

	void Player::move(const Movements& direction) {
		switch (direction) {
			case Movements::UP:
				this->pos.x++;
				break;
			case Movements::DOWN:
				this->pos.x--;
				break;
		}

		this->control.setLed(0, 0, this->pos[1], true);
	}
}