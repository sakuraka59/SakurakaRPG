#pragma once
#include <memory>

class HitCircle;
class HitSquare;

class HitCheck {
public: static bool checkRectAndCircle(HitCircle* circle_obj, HitSquare* square_obj);
public: static bool checkCircleAndCircle(HitCircle* circle_obj1, HitCircle* circle_obj2);
};