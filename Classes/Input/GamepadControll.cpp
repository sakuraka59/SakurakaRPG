#include "GamepadControll.h"
#include "Gamepad.h"

GamepadControll::GamepadControll() {
	this->_controll_type = GamePadControllType::chara;
}
GamePadControllType GamepadControll::getControllType() {
	return this->_controll_type;
}
void GamepadControll::setControllType(GamePadControllType controll_type) {
	this->_controll_type = controll_type;

}