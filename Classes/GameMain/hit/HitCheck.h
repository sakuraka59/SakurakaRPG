#pragma once
#include <memory>

class HitCircle;
class HitSquare;

class HitCheck {
public: static bool checkRectAndCircle(HitCircle* circle_obj, std::unique_ptr<HitSquare>& square_obj);
public: static bool checkCircleAndCircle(HitCircle* circle_obj1, HitCircle* circle_obj2);
};