#include <windows.h>
#include "GamepadButton.h"

GamepadButton::GamepadButton(int key) {
	this->_key_code = key;
	
}
void GamepadButton::updateInit() {
	this->_push_flag = false;
	// 毎回判定をとって初期化を行う
	// でないと、各種判定が通る前に入力された際に判定を抜けてしまうため
	GetAsyncKeyState(this->_key_code);
}

void GamepadButton::updateEnd() {
	if (this->_push_flag == true) {
		this->_key_frame++;
	} else if (this->_key_frame > 0){
		this->_key_frame = 0;
	}
}
bool GamepadButton::isPush() {
	if (GetAsyncKeyState(this->_key_code)) {
		
		this->setPushFlag();
		if (this->_key_frame == 0){
			return true;
		}
		return false;
	}
	return false;
}

bool GamepadButton::isPress() {
	if (GetAsyncKeyState(this->_key_code)){

		this->setPushFlag();
		return true;
	}
	return false;
}
void GamepadButton::setPushFlag() {
	this->_push_flag = true;
}