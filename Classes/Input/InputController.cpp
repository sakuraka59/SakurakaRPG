#include "InputController.h"


//InputControllerButton* InputController::test_button;

InputControllerButton* InputController::Up;
InputControllerButton* InputController::Down;
InputControllerButton* InputController::Left;
InputControllerButton* InputController::Right;

InputControllerButton* InputController::Triangle;
InputControllerButton* InputController::Circle;
InputControllerButton* InputController::Cross;
InputControllerButton* InputController::Square;

InputControllerButton* InputController::L1;
InputControllerButton* InputController::L2;
InputControllerButton* InputController::R1;
InputControllerButton* InputController::R2;
InputControllerButton* InputController::L3;
InputControllerButton* InputController::R3;

InputControllerButton* InputController::Start;
InputControllerButton* InputController::Select;
//*/
InputController::InputController() {
	//	this->test_button = new InputControllerButton(0x41);

	this->Up = new InputControllerButton(VK_UP);
	this->Down = new InputControllerButton(VK_DOWN);
	this->Left = new InputControllerButton(VK_LEFT);
	this->Right = new InputControllerButton(VK_RIGHT);

	this->Triangle = new InputControllerButton('W');
	this->Circle = new InputControllerButton('D');
	this->Cross = new InputControllerButton('S');
	this->Square = new InputControllerButton('A');

	this->L1 = new InputControllerButton('Q');
	this->L2 = new InputControllerButton('F');
	this->R1 = new InputControllerButton('E');
	this->R2 = new InputControllerButton('G');
	this->L3 = new InputControllerButton('R');
	this->R3 = new InputControllerButton('T');

	this->Start = new InputControllerButton('Z');
	this->Select = new InputControllerButton('X');

}
void InputController::updateInit() {

	//InputController::hoge();

	/*
	InputController::Up->updateInit();
	InputController::Down->updateInit();
	InputController::Left->updateInit();
	InputController::Right->updateInit();

	InputController::Triangle->updateInit();
	InputController::Circle->updateInit();
	InputController::Cross->updateInit();
	InputController::Square->updateInit();

	InputController::L1->updateInit();
	InputController::L2->updateInit();
	InputController::R1->updateInit();
	InputController::R2->updateInit();
	InputController::L3->updateInit();
	InputController::R3->updateInit();

	InputController::Start->updateInit();
	InputController::Select->updateInit();
	*/
}

void InputController::updateEnd() {
	/*
	InputController::Up->updateEnd();
	InputController::Down->updateEnd();
	InputController::Left->updateEnd();
	InputController::Right->updateEnd();

	InputController::Triangle->updateEnd();
	InputController::Circle->updateEnd();
	InputController::Cross->updateEnd();
	InputController::Square->updateEnd();

	InputController::L1->updateEnd();
	InputController::L2->updateEnd();
	InputController::R1->updateEnd();
	InputController::R2->updateEnd();
	InputController::L3->updateEnd();
	InputController::R3->updateEnd();

	InputController::Start->updateEnd();
	InputController::Select->updateEnd();
	*/
}