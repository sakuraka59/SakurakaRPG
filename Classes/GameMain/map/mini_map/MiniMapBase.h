#pragma once
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class MapObjectList;
class MapMove;

class MiniMapBase : public Ref {

protected: int hoge = 0;
// 地面
protected: list<list<int>> _map_data_base;
protected: unordered_map<int, unordered_map<int, int>> _map_data;
private: bool _load_map_data = false;

// 地面オブジェクト
protected: list<list<int>> _map_ground_obj_base;
protected: unordered_map<int, unordered_map<int, int>> _map_ground_obj_list;
private: bool _load_map_ground_obj = false;

// マップ移動用地面オブジェクト
protected: list<MapMove*> _map_move_obj_list;

// 立体オブジェクト
protected: list<list<int>> _map_obj_base;
protected: unordered_map<int, MapObjectList*> _map_obj_line_list;
private: bool _load_map_obj = false;


public: MiniMapBase();
//public: virtual void loadMapData();
public: unordered_map<int, unordered_map<int, int>> getMapData();
public: unordered_map<int, unordered_map<int, int>> getMapGoundObjData();
public: unordered_map<int, MapObjectList*> getMapObjData();
public: list<MapMove*> getMapMoveObjData();

};