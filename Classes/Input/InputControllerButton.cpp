#include <windows.h>
#include "InputControllerButton.h"

InputControllerButton::InputControllerButton(int key) {
	this->_key_code = key;
}
void InputControllerButton::updateInit() {
	//int hoge = 0;
	this->_push_flag = false;
//	this->_key_frame++;

}

void InputControllerButton::updateEnd() {
	if (this->_push_flag == true) {
		this->_key_frame++;
	} else if (this->_key_frame > 0){
		this->_key_frame = 0;
	}
}
bool InputControllerButton::isPush() {
	if (GetAsyncKeyState(this->_key_code)){
		
		this->setPushFlag();
		return true;
	}
	return false;
}

void InputControllerButton::setPushFlag() {
	this->_push_flag = true;
}