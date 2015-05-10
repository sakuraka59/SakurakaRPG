#pragma once
#include <windows.h>
#include "InputControllerButton.h"

class InputController {
//public: static InputControllerButton* test_button;

public: static InputControllerButton* Up;
public: static InputControllerButton* Down;
public: static InputControllerButton* Left;
public: static InputControllerButton* Right;

public: static InputControllerButton* Triangle;
public: static InputControllerButton* Circle;
public: static InputControllerButton* Cross;
public: static InputControllerButton* Square;

public: static InputControllerButton* L1;
public: static InputControllerButton* L2;
public: static InputControllerButton* R1;
public: static InputControllerButton* R2;
public: static InputControllerButton* L3;
public: static InputControllerButton* R3;

public: static InputControllerButton* Start;
public: static InputControllerButton* Select;

public: InputController();
public: static void updateInit();

private: void updateInitDetail();
public: static void updateEnd();

};