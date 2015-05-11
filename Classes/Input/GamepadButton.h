#pragma once

class GamepadButton {
protected: int _key_frame = 0;
protected: int _key_code = 0x00;
protected: bool _push_flag = false;
public: GamepadButton(int key);
public: void updateInit();

public: void updateEnd();

public: bool isPush();	// �������u��
public: bool isPress();	// �����Ă���ԁi�������u�ԁ{���������Ă����
private: void setPushFlag();

/*
public: static bool isPress();	// �����Ă���ԁi�������u�ԁ{���������Ă����
public: static bool isPressFrameStart(int frame); // �w��t���[���ȍ~
public: static bool isPressFrameEnd(int frame); // �w��t���[���܂�
*/

};