#pragma once

class InputControllerButton {
private: int key_frame = 0;
private: int key_code = 0x00;
private: bool push_flag = false;
public: InputControllerButton(int key);
public: void updateInit();
public: void Update();
public: void updateEnd();

public: bool isPush();	// 押した瞬間
private: void setPushFlag();

/*
public: static bool isPress();	// 押している間（押した瞬間＋押し続けている間
public: static bool isPressFrameStart(int frame); // 指定フレーム以降
public: static bool isPressFrameEnd(int frame); // 指定フレームまで
*/

};