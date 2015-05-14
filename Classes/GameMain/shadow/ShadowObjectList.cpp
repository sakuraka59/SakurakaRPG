#include "ShadowObjectList.h"
#include "ShadowObjectBase.h"

ShadowObjectList::ShadowObjectList(GameCamera* camera_obj)
{
	this->_camera_obj = camera_obj;
//	this._texture_info = Director.Instance.GL.WhiteTextureInfo;


//	this._object_sprite_list = new SpriteList(this._texture_info);

//	this._object_sprite_list.Color = new Vector4(0.0f, 0.0f, 0.0f, 0.3f);
//	this.AddChild(this._object_sprite_list);

}
void ShadowObjectList::setRenderObject(RenderObject* render_obj){

	/*
	ShadowObjectBase shadow_obj = new ShadowObjectBase(
		this->_camera_obj,
		render_obj,
		this->_texture_info
		);
	//this._shadow_obj_list.Add(shadow_obj);
	this._shadow_obj_list[render_obj] = shadow_obj;

	this._object_sprite_list.AddChild(shadow_obj.getObjectSprite());
	*/
}
void ShadowObjectList::removeRenderObject(RenderObject* render_obj) {

	if (this->_shadow_obj_list[render_obj] == nullptr) {
		//this._object_sprite_list.RemoveChild(this._shadow_obj_list[render_obj].getObjectSprite(), true);
		//this._shadow_obj_list.Remove(render_obj);

		this->_shadow_obj_list[render_obj] = nullptr;
	}
}
void ShadowObjectList::Update() {
	/*
	foreach(KeyValuePair<RenderObject, ShadowObjectBase> shadow_obj in this._shadow_obj_list) {

		shadow_obj.Value.Update();

	}
	*/
}