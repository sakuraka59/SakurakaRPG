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

	
	ShadowObjectBase* shadow_obj = new ShadowObjectBase(render_obj);
	//this._shadow_obj_list.Add(shadow_obj);
	this->_shadow_obj_list[render_obj] = shadow_obj;

	this->addChild(shadow_obj);
}
void ShadowObjectList::removeRenderObject(RenderObject* render_obj) {

	if (this->_shadow_obj_list[render_obj] == nullptr) {
		//this._object_sprite_list.RemoveChild(this._shadow_obj_list[render_obj].getObjectSprite(), true);
		//this._shadow_obj_list.Remove(render_obj);
		this->removeChild(this->_shadow_obj_list[render_obj]);
		delete this->_shadow_obj_list[render_obj];
		//this->_shadow_obj_list[render_obj] = nullptr;
	}
}
void ShadowObjectList::Update() {
	/*
	foreach(KeyValuePair<RenderObject, ShadowObjectBase> shadow_obj in this._shadow_obj_list) {

		shadow_obj.Value.Update();

	}
	*/
	for (std::unordered_map<RenderObject*, ShadowObjectBase*>::iterator shadow_itr = this->_shadow_obj_list.begin(); shadow_itr != this->_shadow_obj_list.end(); shadow_itr++) {
		this->_shadow_obj_list[shadow_itr->first]->Update();

		//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
		//		this->_map_obj_line_list[map_obj_iterator->first]->Update();
		//		map_obj_line;
		//this->_shadow_obj_list->addChild(this->_shadow_obj_list[map_obj_iterator->first], this->_shadow_obj_list[map_obj_iterator->first]->getDrawY() * (-1));

	}
}