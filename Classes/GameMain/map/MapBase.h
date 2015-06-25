#pragma once
#include "../../RenderObject.h"
#include <unordered_map>

//class RenderObject;
class MapObjectBase;
class MapObjectList;
class CharaBase;
class CharaPlayer;
class MapGroundList;
class MapGroundObjectList;
class GameCamera;



class MapBase : public RenderObject {

protected: std::unordered_map<int, std::unordered_map<int, MapObjectBase*>> _map_obj_list;
protected: std::unordered_map<int, MapObjectList*> _map_obj_line_list;

private: std::unordered_map<int, std::unordered_map<int, int>> _map_base_data;			// オブジェクト設置等の基本情報（主にランダムマップの壁情報

private: std::unordered_map<int, std::unordered_map<int, int>> _map_ground_data;	// 地面情報
private: std::unordered_map<int, std::unordered_map<int, int>> _map_g_obj_data;		// 地面設置型のオブジェクト

private: CharaPlayer* _player_obj;
//	protected Dictionary<int,Dictionary<int, MapObjectBase>> _map_obj_draw_list = new Dictionary<int, Dictionary<int, MapObjectBase>>();

private: MapGroundList* _map_ground_obj;
private: MapGroundObjectList* _mg_object_list_obj;
private: GameCamera* _camera_obj;

private: int _map_type = 0;


public: MapBase(GameCamera* camera_obj, CharaPlayer* player_obj);
public: void Init();
public: void Update();
//public: std::unordered_map<int, std::unordered_map<int, MapObjectBase*>> getMapObjectList();
public: void initMapObject(std::unordered_map<int, std::unordered_map<int, int>> map_data);
public: std::unordered_map<int, MapObjectList*> getMapObjectLineList();
public: MapGroundObjectList* getMgObjectList();

public: void createRandomMap();
public: void createMiniMap();
public: void setCharaPoint(CharaBase* set_chara_obj, int map_block_type);

// マップ移動更新処理
public: void mapMoveUpdate();
};