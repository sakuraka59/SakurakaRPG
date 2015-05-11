#include "HitSquare.h"


HitSquare::HitSquare(double& x, double& y, double width, double height, double& angle)
{
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;
	this->_angle = angle;
}
double HitSquare::getX() {
	return this->_x;
}
double HitSquare::getY() {
	return this->_y;
}
double HitSquare::getWidth() {
	return this->_width;
}
double HitSquare::getHeight() {
	return this->_height;
}
double HitSquare::getAngle() {
	return this->_angle;
}