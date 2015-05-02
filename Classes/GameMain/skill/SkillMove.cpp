#include "SkillMove.h"


SkillMove::SkillMove(double add_angle, double one_frame_speed, double junp_power, int frame_num) {
	this->_add_angle = add_angle;
	this->_one_frame_speed = one_frame_speed;
	this->_junp_power = junp_power;
	this->_frame_num = frame_num;

}
int SkillMove::getFrameNum() {
	return this->_frame_num;
}
double SkillMove::getAddAngle() {
	return this->_add_angle;
}
double SkillMove::getOneFrameSpeed() {
	return this->_one_frame_speed;
}
double SkillMove::getJunpPower() {
	return this->_junp_power;
}