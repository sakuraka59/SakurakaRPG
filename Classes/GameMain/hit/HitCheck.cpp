#include "HitCheck.h"
#include "HitCircle.h"
#include "HitSquare.h"
#include <math.h>

bool HitCheck::checkRectAndRect(HitSquare* square_obj1, HitSquare* square_obj2) {
	double hoge1 = square_obj1->getX();
	double hoge2 = square_obj2->getX() + square_obj2->getWidth();

	double hoge3 = square_obj1->getY();
	double hoge4 = square_obj2->getY() + square_obj2->getHeight();

	double hoge5 = square_obj1->getX() + square_obj1->getWidth();
	double hoge6 = square_obj2->getX();

	double hoge7 = square_obj1->getY() + square_obj1->getHeight();
	double hoge8 = square_obj2->getY();
	
	if (square_obj1->getX() <= square_obj2->getX() + square_obj2->getWidth() &&
		square_obj1->getY() <= square_obj2->getY() + square_obj2->getHeight() &&
		square_obj1->getX() + square_obj1->getWidth() >= square_obj2->getX() &&
		square_obj1->getY() + square_obj1->getHeight() >= square_obj2->getY()
		){

		return true;
	}
	return false;
}
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

	double c1x_c2x_2 = (c1x - c2x) * (c1x - c2x);
	double c1y_c2y_2 = (c1y - c2y) * (c1y - c2y);
	double c1r_c2r_2 = (c1r + c2r) * (c1r + c2r);
//	double c1x_c2x_2 = pow((c1x - c2x), 2) + pow((c1y - c2y), 2);
//	auto hoge2 = pow((c1r - c2r), 2);
	//(xc1-xc2)^2 + (yc1-yc2)^2 ÅÖ (r1+r2)^2
	if (c1x_c2x_2 + c1y_c2y_2 <= c1r_c2r_2) {
		return true;
	}
	return false;
}