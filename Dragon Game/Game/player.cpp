#include "player.h"

namespace arduino {
	Player::Player(LedControl& control, const pcons& pos) {
		this->pos = pos;
		control.setIntensity(0, 15);
		control.setLed(0, pos[0], pos[1], true);
	}

	Player::Player(LedControl& control, int16 x, int16 y) {
		this->pos = { x, y };
		control.setIntensity(0, 15);
		control.setLed(0, x, y, true);
	}

	Player::Player(const Player& player) {
		this->pos = player.pos;
		this->hit = player.hit;
	}


	bool Player::isHit(int16 x, int16 y) {
		if (x == this->pos[0] && y == this->pos[1]) {
			this->hit = true;
			return true;
		}
		this->hit = false;
		return false;
	}

	void Player::move(LedControl& control, const Movements& direction) {
		if (this->pos[0] < 7 && this->pos[0] > 0) {
			control.setLed(0, this->pos[0], this->pos[1], false);
			switch (direction) {
				case Movements::UP:
					this->pos.x++;
					break;
				case Movements::DOWN:
					this->pos.x--;
					break;
			}
			control.setLed(0, this->pos[0], this->pos[1], true);
		}
		else {
			control.setLed(0, this->pos[0], this->pos[1], false);
			if (this->pos[0] == 7 && direction == Movements::DOWN) 
				this->pos.x--;
			else if (this->pos[0] == 0 && direction == Movements::UP)
				this->pos.x++;
			control.setLed(0, this->pos[0], this->pos[1], true);
		}
	}
}