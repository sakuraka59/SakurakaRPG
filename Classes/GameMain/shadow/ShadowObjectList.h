#pragma once
#include <unordered_map>
#include "../../RenderObject.h"

class GameCamera;
class ShadowObjectBase;

class ShadowObjectList : public RenderObject{
//private Dictionary<int, RenderObject> _render_obj_list = new Dictionary<int, RenderObject>();
//protected List<ShadowObjectBase> _shadow_obj_list = new List<ShadowObjectBase>();
protected: std::unordered_map<RenderObject*, ShadowObjectBase*> _shadow_obj_list;

//private: SpriteList _object_sprite_list;
//private: TextureInfo _texture_info;

private: GameCamera* _camera_obj;

public: ShadowObjectList(GameCamera* camera_obj);
public: void setRenderObject(RenderObject* render_obj);
public: void removeRenderObject(RenderObject* render_obj);
public: void Update();
};