#pragma once
#include <windows.h>
#include <memory>
#include "GamepadButton.h"
#include "GamepadControll.h"

class Gamepad {

public: static GamepadButton* Up;
public: static GamepadButton* Down;
public: static GamepadButton* Left;
public: static GamepadButton* Right;

public: static GamepadButton* Triangle;
public: static GamepadButton* Circle;
public: static GamepadButton* Cross;
public: static GamepadButton* Square;

public: static GamepadButton* L1;
public: static GamepadButton* L2;
public: static GamepadButton* R1;
public: static GamepadButton* R2;
public: static GamepadButton* L3;
public: static GamepadButton* R3;

public: static GamepadButton* Start;
public: static GamepadButton* Select;


public: static GamepadControll* GameControll;
//

public: Gamepad();
public: static void updateInit();

private: void updateInitDetail();
public: static void updateEnd();



};

enum class gamePadControllType {
	no_type = -1,

	chara,
	item_ui,

	enum_end,
};