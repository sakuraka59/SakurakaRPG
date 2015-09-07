#pragma once

enum class gamePadControllType;

class GamepadControll {
private: gamePadControllType _controll_type;
private: gamePadControllType _before_controll_type;

public: GamepadControll();
public: gamePadControllType getControllType();
public: void setControllType(gamePadControllType controll_type, int controll_detail = -1);
};

