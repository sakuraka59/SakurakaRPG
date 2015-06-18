#pragma once

enum class GamePadControllType;
class GamepadControll {
private: GamePadControllType _controll_type;

public: GamepadControll();
public: GamePadControllType getControllType();
public: void setControllType(GamePadControllType controll_type);
};

