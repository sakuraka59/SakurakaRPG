#pragma once

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class SkillMagicSpell : public Ref {
private: string _spell = "";
private: int _send_frame = -1;

public: SkillMagicSpell(string spell, int frame);
public: int getSendFrame();
public: string getSpell();
};