#pragma once

enum class gamePadControllType;
class GamepadControll {
private: gamePadControllType _controll_type;

public: GamepadControll();
public: gamePadControllType getControllType();
public: void setControllType(gamePadControllType controll_type);
};

