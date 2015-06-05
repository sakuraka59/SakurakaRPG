#pragma once
#include "../../../RenderObject.h"

class CharaPlayer;
class MapGroundObjectBase;

using namespace std;
class MapGroundObjectList : public RenderObject{

private: unordered_map<int, unordered_map<int, int>> _map_ground_obj_data;
private: unordered_map<int, unordered_map<int, bool>> _map_draw_list;

private: int _before_block_draw_x = 0;
private: int _before_block_draw_y = 0;

private: const int _MAP_OUTER_SIZE_X = -2;
private: const int _MAP_OUTER_SIZE_Y = -2;

private: CharaPlayer* _player_obj;

private: RenderObject* _ground_sprite_list;

private: std::unordered_map<int, std::unordered_map<int, MapGroundObjectBase*>>_ground_obj_list;

public: MapGroundObjectList(CharaPlayer* player_obj);
public: void LoadData(unordered_map<int, unordered_map<int, int>> map_ground_data);

public: void Init();
public: void Update();

private: void reviewGroundBlockX(int add_block_draw_x, int remove_block_draw_x, int block_draw_y, int map_max_y);
private: void reviewGroundBlockY(int add_block_draw_y, int remove_block_draw_y, int block_draw_x, int map_max_x);


public: unordered_map<int, std::unordered_map<int, MapGroundObjectBase*>> getGroundObjData();
};