#pragma once

class InputControllerButton {
private: int key_frame = 0;
private: int key_code = 0x00;
private: bool push_flag = false;
public: InputControllerButton(int key);
public: void updateInit();
public: void Update();
public: void updateEnd();

public: bool isPush();	// �������u��
private: void setPushFlag();

/*
public: static bool isPress();	// �����Ă���ԁi�������u�ԁ{���������Ă����
public: static bool isPressFrameStart(int frame); // �w��t���[���ȍ~
public: static bool isPressFrameEnd(int frame); // �w��t���[���܂�
*/

};