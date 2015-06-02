#pragma once
#include "cocos2d.h"
#include "miniMapType.h"

using namespace cocos2d;
using namespace std;

class MapObjectList;
class MiniMapBase;

class MiniMapManager : public Ref {
private:
	static MiniMapBase* map_obj;
public: static void loadMiniMap(miniMapType map_type);
public: static unordered_map<int, std::unordered_map<int, int>> getMapData();
public: static unordered_map<int, MapObjectList*> getMapObjData();
};