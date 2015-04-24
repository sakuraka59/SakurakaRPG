#ifndef __PLAYUI_H__
#define __PLAYUI_H__

#include "UiBase.h"
#include "cocos2d.h"
//#include "../../ResourceManage.h"

class PlayUi : public UiBase
{
public: PlayUi();
public: void Update();

private: cocos2d::Sprite* _test_sprite;

//public: ResourceManage _resource_manage_obj = new ResourceManage();


};
#endif