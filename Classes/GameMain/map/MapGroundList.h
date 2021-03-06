#include "../../RenderObject.h"
#include <unordered_map>

class CharaPlayer;
class MapGroundBase;

class MapGroundList : public RenderObject {

private: std::unordered_map<int, std::unordered_map<int, int>> _map_data;
private: std::unordered_map<int, std::unordered_map<int, bool>> _map_draw_list;
private: int _before_block_draw_x = 0;
private: int _before_block_draw_y = 0;

private: int _map_type = 0;

private: const int _map_outer_size_x = -2;
private: const int _map_outer_size_y = -2;

private: CharaPlayer* _player_obj;

private: RenderObject* _ground_sprite_list;

private: std::unordered_map<int, std::unordered_map<int, MapGroundBase*>>_ground_obj_list;

public: MapGroundList(std::unordered_map<int, std::unordered_map<int, int>> map_data, int map_type, CharaPlayer* player_obj);
public: void Init();
public: void Update();
private: void reviewGroundBlockX(int add_block_draw_x, int remove_block_draw_x, int block_draw_y, int map_max_y);
private: void reviewGroundBlockY(int add_block_draw_y, int remove_block_draw_y, int block_draw_x, int map_max_x);
private: void setCharaPoint();
public: std::unordered_map<int, std::unordered_map<int, int>> getMapData();
};