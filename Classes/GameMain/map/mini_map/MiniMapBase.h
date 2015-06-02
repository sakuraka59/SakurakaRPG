#pragma once
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class MapObjectList;

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

// 立体オブジェクト
protected: list<list<int>> _map_obj_base;
protected: unordered_map<int, MapObjectList*> _map_obj_line_list;
private: bool _load_map_obj = false;


public: MiniMapBase();
public: virtual void loadMapData();
public: unordered_map<int, unordered_map<int, int>> getMapData();
public: unordered_map<int, MapObjectList*> getMapObjData();

protected: 
};