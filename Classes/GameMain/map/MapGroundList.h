#include "../../RenderObject.h"
#include <unordered_map>

class GameCamera;
class CharaPlayer;

class MapGroundList : public RenderObject {
private: GameCamera* _camera_obj;
private: std::unordered_map<int, int> _map_data;
private: std::unordered_map<int, std::unordered_map<int, bool>> _map_draw_list;
private: int _before_block_draw_x = 0;
private: int _before_block_draw_y = 0;

private: int _map_type = 0;

private: int _map_outer_size_x = -1;
private: int _map_outer_size_y = -1;

private: CharaPlayer* _player_obj;


};