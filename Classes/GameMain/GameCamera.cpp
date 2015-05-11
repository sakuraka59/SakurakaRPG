#include <random>
#include "GameCamera.h"
#include "GAME_SETTING.h"

void GameCamera::Update() {
	if (this->_shake_flag == true) {

		if (this->_shake_state == 3) {
			this->_shake_frame++;
			if (this->_shake_frame >= 8) {
				this->_shake_frame = 0;
				this->_shake_state = 1;
				this->_shake_flag = false;
			}
		}
		else {
			this->updateCameraShake();
		}
	}
	this->_x = this->_base_x + this->_shake_x;
	this->_y = this->_base_y + this->_shake_y;

}
void GameCamera::updateCharaPoint(double chara_x, double chara_y) {
	this->_base_x = chara_x - (GAME_WIDTH / 2);
	this->_base_y = chara_y - (GAME_HEIGHT / 2);
}
void GameCamera::updateCameraShake() {
	if (this->_shake_state == 1) {

		this->_shake_x += this->_SHAKE_MOVE * this->_shake_rate_x;
		this->_shake_y += this->_SHAKE_MOVE * this->_shake_rate_y;
	}
	else if (this->_shake_state == 2) {
		this->_shake_x -= this->_SHAKE_MOVE * this->_shake_rate_x;
		this->_shake_y -= this->_SHAKE_MOVE * this->_shake_rate_y;
	}

	this->_shake_frame++;
	if (this->_shake_frame >= this->_SHAKE_FRAME_SIDE) {
		this->_shake_frame = 0;

		if (this->_shake_state == 1) {
			this->_shake_state = 2;
		}
		else if (this->_shake_state == 2) {
			this->_shake_state = 3;
			this->_shake_x = 0;
			this->_shake_y = 0;

		}
	}
}
void GameCamera::setCameraShake() {

	if (this->_shake_flag == false) {
		this->_shake_flag = true;

		
		/*
		System.Random rand_obj = new System.Random();
		rand_x = rand_obj.Next(2);
		rand_y = rand_obj.Next(2);
		*/
		std::random_device rnd;     // ”ñŒˆ’è“I‚È—”¶¬Ší‚ğ¶¬
		std::mt19937 mt(rnd());
		std::uniform_int_distribution<int> rand_obj2(0, 1);
		int rand_x = rand_obj2(mt);
		int rand_y = rand_obj2(mt);

		this->_shake_rate_x = 1;
		if (rand_x != 1) {
			this->_shake_rate_x = -1;
		}

		this->_shake_rate_y = 1;
		if (rand_y != 1) {
			this->_shake_rate_y = -1;
		}

	}
}
double GameCamera::getCameraX() {
	return this->_x;
}
double GameCamera::getCameraY() {
	return this->_y;
}