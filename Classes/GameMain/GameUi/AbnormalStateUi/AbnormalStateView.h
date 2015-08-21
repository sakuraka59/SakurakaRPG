#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"



class CharaPlayer;
class StateBase;

using namespace std;
using namespace cocos2d;

class AbnormalStateView : public RenderObject {
private: const int _FONT_SIZE = 15;
private: StateBase* _state_obj;
private: cocos2d::LabelTTF* _state_name_label;
private: cocos2d::LabelTTF* _debug_time_label;
		 
public: AbnormalStateView(StateBase* state_obj);

public: void update();
};