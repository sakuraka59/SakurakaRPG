#pragma once

#include "cocos2d.h"


class PlayUi;
class PlayerCommentUI;
class DefaultStateUI;
class ItemUi;
class AbnormalStateUI;

class GameMain : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// 引数含めて書かないと、ループ処理してくれない
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
	DefaultStateUI* _default_state_ui;



	cocos2d::EventListenerKeyboard* _KEYBORD_EVENT;
	// キー入力テスト
	cocos2d::LabelTTF* _test_label;

	// single
public: 
	static ItemUi* _item_ui_obj;
	static AbnormalStateUI* _abnormal_state_ui_obj;
};