#include "GameMain.h"
#include "GameUi\PlayUi.h"
#include "GameUi\PlayerCommentUI.h"
#include "GameUi\DefaultStateUI.h"

#include "..\Input\Gamepad.h"

#define COCOS2D_DEBUG 1
USING_NS_CC;

Scene* GameMain::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMain::create();

	// add layer as a child to scene
	scene->addChild(layer);
	
	

	// return the scene
	return scene;
}

bool GameMain::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	/*
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	this->_KEYBORD_EVENT = EventListenerKeyboard::create();
	dispatcher->addEventListenerWithSceneGraphPriority(this->_KEYBORD_EVENT, this);
	// */

	//---------------------------------------------------------------

	/*
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	this->_KEYBORD_EVENT = EventListenerKeyboard::create();
	
	this->_KEYBORD_EVENT->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			auto str = String::createWithFormat("pless up key");
			this->_test_label->setString(str->getCString());
		};
	};
	this->_KEYBORD_EVENT->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		// •ú‚³‚ê‚½‚Æ‚«‚Ìˆ—
		auto str = String::createWithFormat("Push any key");
		this->_test_label->setString(str->getCString());
	};
	
	dispatcher->addEventListenerWithSceneGraphPriority(this->_KEYBORD_EVENT, this);
	
	this->_test_label = LabelTTF::create("Push any key.", "Arial", 40);
	this->_test_label->setPosition(Point(320.0f, 240.0f));
	this->_test_label->setTag(1);
	this->addChild(this->_test_label);
	// */
	//---------------------------------------------------------------

	this->_play_comment_ui_obj = new PlayerCommentUI();


	this->_play_ui_obj = new PlayUi(this->_play_comment_ui_obj);
	this->addChild(this->_play_ui_obj);
	

	CharaPlayer* player_obj = this->_play_ui_obj->getCharaPlayerObj();

	this->_default_state_ui = new DefaultStateUI(player_obj);
//	this->_default_state_ui->setPosition(0, 0);

	this->addChild(this->_default_state_ui);
	
	this->addChild(this->_play_comment_ui_obj);

//	this->_test_ui_obj = new UiBase();
//	this->addChild(this->_test_ui_obj);
	
//	UiBase * test_obj = new UiBase();
//	this->addChild(test_obj);


	this->scheduleUpdate();

	return true;
	
	/*
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(GameMain::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
	origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, nullptr );
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	return true;

	// */
}
void GameMain::update(float delta) {
	
	Gamepad::updateInit();

	this->_play_ui_obj->Update();
	this->_default_state_ui->Update();

	this->_play_comment_ui_obj->Update();


	Gamepad::updateEnd();
}

void GameMain::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

