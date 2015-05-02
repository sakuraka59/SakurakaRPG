#include "cocos2d.h"
#include "ShadowObjectBase.h"
#include "../../RenderObject.h"
ShadowObjectBase::ShadowObjectBase(GameCamera* camera_obj, RenderObject* render_obj, TextureInfo* texture_info)
{
	this->_render_obj = render_obj;
//	this->_object_sprite = new SpriteTile(){ TextureInfo = texture_info };
//	this->_object_sprite.Scale = new cocos2d::Vec2(this->_SHADOW_WIDTH, 10);

//	this._object_sprite.Color = new Vector4(0.0f, 0.0f, 0.0f, 0.3f);

}
/*
ShadowObjectBase::SpriteTile getObjectSprite() {

	return this->_object_sprite;
}
*/
void ShadowObjectBase::Update() {
	//this->_object_sprite->Position = new cocos2d::Vec2(this->_render_obj->getDrawPositionX() - (this->_SHADOW_WIDTH / 2), this->_render_obj->getDrawPositionY() - 3);
	
	

};