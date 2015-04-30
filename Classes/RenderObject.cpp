#include "RenderObject.h"
#include "cocos2d.h"


double RenderObject::getDrawX() {
	return this->_draw_x;
}
double RenderObject::getDrawY() {
	return this->_draw_y;
}
double RenderObject::getDrawZ() {
	return this->_draw_z;
}

cocos2d::Vec2* RenderObject::getDrawPosition() {
	return new cocos2d::Vec2(0, 0);
}
float RenderObject::getDrawPositionX() {
	return 0.0f;
}
float RenderObject::getDrawPositionY() {
	return 0.0f;
}