#include "Gamepad.h"


//GamepadButton* Gamepad::test_button;

GamepadButton* Gamepad::Up = new GamepadButton(VK_UP);
GamepadButton* Gamepad::Down = new GamepadButton(VK_DOWN);
GamepadButton* Gamepad::Left = new GamepadButton(VK_LEFT);
GamepadButton* Gamepad::Right = new GamepadButton(VK_RIGHT);

GamepadButton* Gamepad::Triangle = new GamepadButton('W');
GamepadButton* Gamepad::Circle = new GamepadButton('D');
GamepadButton* Gamepad::Cross = new GamepadButton('S');
GamepadButton* Gamepad::Square = new GamepadButton('A');

GamepadButton* Gamepad::L1 = new GamepadButton('Q');
GamepadButton* Gamepad::L2 = new GamepadButton('F');
GamepadButton* Gamepad::R1 = new GamepadButton('E');
GamepadButton* Gamepad::R2 = new GamepadButton('G');
GamepadButton* Gamepad::L3 = new GamepadButton('R');
GamepadButton* Gamepad::R3 = new GamepadButton('T');

GamepadButton* Gamepad::Start = new GamepadButton('Z');
GamepadButton* Gamepad::Select = new GamepadButton('X');
//GamePadControllType Gamepad::_controll_type = GamePadControllType::chara;
GamepadControll* Gamepad::GameControll = new GamepadControll();
//*/
Gamepad::Gamepad() {

}
void Gamepad::updateInit() {

	Gamepad::Up->updateInit();
	Gamepad::Down->updateInit();
	Gamepad::Left->updateInit();
	Gamepad::Right->updateInit();

	Gamepad::Triangle->updateInit();
	Gamepad::Circle->updateInit();
	Gamepad::Cross->updateInit();
	Gamepad::Square->updateInit();

	Gamepad::L1->updateInit();
	Gamepad::L2->updateInit();
	Gamepad::R1->updateInit();
	Gamepad::R2->updateInit();
	Gamepad::L3->updateInit();
	Gamepad::R3->updateInit();

	Gamepad::Start->updateInit();
	Gamepad::Select->updateInit();
	
}

void Gamepad::updateEnd() {
	
	Gamepad::Up->updateEnd();
	Gamepad::Down->updateEnd();
	Gamepad::Left->updateEnd();
	Gamepad::Right->updateEnd();

	Gamepad::Triangle->updateEnd();
	Gamepad::Circle->updateEnd();
	Gamepad::Cross->updateEnd();
	Gamepad::Square->updateEnd();

	Gamepad::L1->updateEnd();
	Gamepad::L2->updateEnd();
	Gamepad::R1->updateEnd();
	Gamepad::R2->updateEnd();
	Gamepad::L3->updateEnd();
	Gamepad::R3->updateEnd();

	Gamepad::Start->updateEnd();
	Gamepad::Select->updateEnd();
	
}
/*
GamePadControllType Gamepad::getControllType() {
	return GamePadControllType::chara;
}
void Gamepad::setControllType(GamePadControllType controll_type) {
//	Gamepad::_controll_type = GamePadControllType::chara;

}
*/