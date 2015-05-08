#include <windows.h>
#include "InputControllerButton.h"

InputControllerButton::InputControllerButton(int key) {

}
void InputControllerButton::updateInit() {
	this->push_flag = false;

}
void InputControllerButton::Update() {


}
void InputControllerButton::updateEnd() {
	if (this->push_flag == true) {
		this->key_frame++;
	} else {
		this->key_frame = 0;
	}
}
bool InputControllerButton::isPush() {
	if (GetAsyncKeyState(0x42)){
		OutputDebugString((LPCWSTR)("1"));
		return true;
	}
	return false;
}

void InputControllerButton::setPushFlag() {
	this->push_flag = true;
}