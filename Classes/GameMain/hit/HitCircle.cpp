#include "HitCircle.h"
#include "../../RenderObject.h"

HitCircle::HitCircle(RenderObject* render_obj, double radius) {
	this->_render_obj = render_obj;
	this->_radius = radius;
}
double HitCircle::getCneterX() {
	return this->_render_obj->getDrawX();
}
double HitCircle::getCneterY() {
	return this->_render_obj->getDrawY();
}
double HitCircle::getRadius() {
	return this->_radius;
}