#pragma once

class RenderObject;

class GameCamera;
class TextureInfo;
class SpriteTile;

class ShadowObjectBase {

private: SpriteTile* _object_sprite;
private: RenderObject* _render_obj;

private: int _SHADOW_WIDTH = 20;
public: ShadowObjectBase(GameCamera* camera_obj, RenderObject* render_obj, TextureInfo* texture_info);
//public: SpriteTile getObjectSprite();
public: void Update();
};