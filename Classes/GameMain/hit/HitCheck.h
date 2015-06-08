#pragma once
#include <memory>

class HitCircle;
class HitSquare;

class HitCheck {
public: static bool checkRectAndRect(HitSquare* square_obj1, HitSquare* square_obj2);
public: static bool checkRectAndCircle(HitCircle* circle_obj, HitSquare* square_obj);
public: static bool checkCircleAndCircle(HitCircle* circle_obj1, HitCircle* circle_obj2);
};