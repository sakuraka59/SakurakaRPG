#pragma once
#include "../../RenderObject.h"

class GameCamera;
class TextureInfo;
class SpriteTile;

class ShadowObjectBase : public RenderObject {

private: SpriteTile* _object_sprite;
private: RenderObject* _render_obj;

private: int _SHADOW_WIDTH = 20;
public: ShadowObjectBase(RenderObject* render_obj);
//public: SpriteTile getObjectSprite();
public: void Update();
};