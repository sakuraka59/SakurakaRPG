#pragma once

class GamepadButton {
protected: int _key_frame = 0;
protected: int _key_code = 0x00;
protected: bool _push_flag = false;
public: GamepadButton(int key);
public: void updateInit();

public: void updateEnd();

public: bool isPush();	// ‰Ÿ‚µ‚½uŠÔ
public: bool isPress();	// ‰Ÿ‚µ‚Ä‚¢‚éŠÔi‰Ÿ‚µ‚½uŠÔ{‰Ÿ‚µ‘±‚¯‚Ä‚¢‚éŠÔ
private: void setPushFlag();

/*
public: static bool isPress();	// ‰Ÿ‚µ‚Ä‚¢‚éŠÔi‰Ÿ‚µ‚½uŠÔ{‰Ÿ‚µ‘±‚¯‚Ä‚¢‚éŠÔ
public: static bool isPressFrameStart(int frame); // w’èƒtƒŒ[ƒ€ˆÈ~
public: static bool isPressFrameEnd(int frame); // w’èƒtƒŒ[ƒ€‚Ü‚Å
*/

};