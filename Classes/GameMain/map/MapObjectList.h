#pragma once
#include <unordered_map>
#include "../../RenderObject.h"

class MapObjectBase;
class GameCamera;
class CharaPlayer;

class MapObjectList : public RenderObject  {


protected: std::unordered_map<int, MapObjectBase*> _map_obj_line_list;
//	protected SpriteList _object_sprite_list;
private: RenderObject* _object_draw_list;
private: GameCamera* _camera_obj;
//	private TextureInfo _texture_info;

protected: std::unordered_map<int, bool> _map_obj_draw_list;

private: int _draw_correction_x = 0;
private: int _draw_correction_y = 0;
private: int _OBJECT_WIDTH = 96;
private: int _OBJECT_HEIGHT = 192;
private: int _map_block_y = 0;

private: int _before_x = 0;
private: int _before_y = 0;
private: bool _draw_flag = true;
private: CharaPlayer* _player_obj;

public: MapObjectList(int map_block_y, GameCamera* camera_obj, CharaPlayer* player_obj);
public: void setObject(int map_block_x);
public: bool checkMapObject(int map_block_x);
public: MapObjectBase* getMapObject(int map_block_x);
public: void Update();

private: void removeLineObjectDraw();
private: void resetLineObjectDraw(int player_map_x, int width_side);
};