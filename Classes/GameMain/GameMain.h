#pragma once

#include "cocos2d.h"


class PlayUi;
class PlayerCommentUI;

class GameMain : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// ˆø”ŠÜ‚ß‚Ä‘‚©‚È‚¢‚ÆAƒ‹[ƒvˆ—‚µ‚Ä‚­‚ê‚È‚¢
	virtual void update(float delta);

	
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
		CREATE_FUNC(GameMain);
	//*/

private:
//	UiBase * _test_ui_obj;
	PlayUi* _play_ui_obj;
	PlayerCommentUI* _play_comment_ui_obj;
};