#include "cocos2d.h"
#include "ShadowObjectBase.h"

ShadowObjectBase::ShadowObjectBase(RenderObject* render_obj)
{
	this->_render_obj = render_obj;
//	this->_object_sprite = new SpriteTile(){ TextureInfo = texture_info };
//	this->_object_sprite.Scale = new cocos2d::Vec2(this->_SHADOW_WIDTH, 10);

//	this._object_sprite.Color = new Vector4(0.0f, 0.0f, 0.0f, 0.3f);

	cocos2d::Rect rect = cocos2d::Rect(0, 0, this->_SHADOW_WIDTH, 10);
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create();
	sprite_data->setTextureRect(rect);
	sprite_data->setPosition(this->_SHADOW_WIDTH / 2, 0);

	sprite_data->setColor(cocos2d::Color3B(0, 0, 0));
	sprite_data->setOpacity(128);

	this->addChild(sprite_data);
}
/*
ShadowObjectBase::SpriteTile getObjectSprite() {

	return this->_object_sprite;
}
*/
void ShadowObjectBase::Update() {
	//this->_object_sprite->Position = new cocos2d::Vec2(this->_render_obj->getDrawPositionX() - (this->_SHADOW_WIDTH / 2), this->_render_obj->getDrawPositionY() - 3);
	if (this != nullptr) {
		this->setPosition(this->_render_obj->getDrawPositionX() - (this->_SHADOW_WIDTH / 2), this->_render_obj->getDrawPositionY() - 3);
	}
	else {
		delete this;
	}
};