#include "UiBase.h"

USING_NS_CC;

UiBase :: UiBase() {

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();


	this->_test_label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	this->_test_label->setPosition(Vec2(this->_test_x, 10));

	// add the label as a child to this layer
	this->addChild(this->_test_label, 1);

	
}
void UiBase::Update() {
	this->_test_x++;
	if (this->_test_x >= 1000) {
		this->_test_x = 100;
	}
	this->_test_label->setPosition(Vec2(this->_test_x, 10));
}