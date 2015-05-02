#pragma once


class SkillMove {

private: double _add_angle = 0;
private: double _one_frame_speed = 0;
private: double _junp_power = 0;
private: int _frame_num = 0;
//-------------------------------------------------------------------
public: SkillMove(double add_angle, double one_frame_speed, double junp_power, int frame_num);
public: int getFrameNum();
public: double getAddAngle();
public: double getOneFrameSpeed();
public: double getJunpPower();
};