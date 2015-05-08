#pragma once
#include "InputControllerButton.h"

class InputController {
public: static InputControllerButton* test_button;
public: InputController(){ this->test_button = new InputControllerButton(0x41); };
public: void Update();
public: static void testUpdate();
};