#include "HitCheck.h"
#include "HitCircle.h"
#include "HitSquare.h"
#include <math.h>

bool HitCheck::checkRectAndCircle(HitCircle* circle_obj, HitSquare* square_obj) {

	if (circle_obj->getCneterX() + circle_obj->getRadius() >= square_obj->getX() &&
		circle_obj->getCneterX() - circle_obj->getRadius() <= square_obj->getX() + square_obj->getWidth() &&
		circle_obj->getCneterY() + circle_obj->getRadius() >= square_obj->getY() &&
		circle_obj->getCneterY() - circle_obj->getRadius() <= square_obj->getY() + square_obj->getHeight()
		) {
		return true;
	}

	return false;
}
bool HitCheck::checkCircleAndCircle(HitCircle* circle_obj1, HitCircle* circle_obj2) {
	//circle_obj->getCneterX()
	double c1x = circle_obj1->getCneterX();
	double c1y = circle_obj1->getCneterY();
	double c1r = circle_obj1->getRadius();

	double c2x = circle_obj2->getCneterX();
	double c2y = circle_obj2->getCneterY();
	double c2r = circle_obj2->getRadius();


	//(xc1-xc2)^2 + (yc1-yc2)^2 ÅÖ (r1+r2)^2
	if (pow((c1x - c2x), 2) + pow((c1y - c2y), 2) <= pow((c1r - c2r), 2)) {
		return true;
	}
	return false;
}