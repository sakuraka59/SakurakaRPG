#pragma once

class GameCamera {

private: double _base_x = -1280 / 2;
private: double _base_y = -720 / 2;
protected: double _x = -1280 / 2;
protected: double _y = -720 / 2;

private: bool _shake_flag = false;
private: int _shake_state = 1;
private: double _shake_x = 0;
private: double _shake_y = 0;
private: double _shake_rate_x = -1;
private: double _shake_rate_y = 1;

private: double _SHAKE_MOVE = 1.0;
private: int _SHAKE_FRAME_SIDE = 5;
private: int _shake_frame = 0;

//-----------------------------------------------
public: void Update();
public: void updateCharaPoint(double chara_x, double chara_y);
private: void updateCameraShake();
public: void setCameraShake();
public: double getCameraX();
public: double getCameraY();
};