#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__5

#include "cocos2d.h"
#include "GameUi\UiBase.h"

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
	UiBase * _test_ui_obj;
};

#endif // __GAMEMAIN_H__