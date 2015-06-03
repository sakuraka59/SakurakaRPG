#include "MiniMapManager.h"
#include "MiniMapBase.h"
#include "test_map/TestMap.h"

MiniMapBase* MiniMapManager::map_obj = new MiniMapBase();

void MiniMapManager::loadMiniMap(miniMapType map_type) {

	switch (map_type) {
	case miniMapType::no_type:
		break;
	case miniMapType::test_map:
		MiniMapManager::map_obj = new TestMap();
//		TestMap* load_map_obj = new TestMap();
//		MiniMapManager::map_obj = load_map_obj;
		//MiniMapManager::map_obj = new MiniMapBase();
		break;
	}
//	MiniMapManager::map_obj->loadMapData();
}

unordered_map<int, std::unordered_map<int, int>> MiniMapManager::getMapData() {

	return MiniMapManager::map_obj->getMapData();
}

unordered_map<int, MapObjectList*> MiniMapManager::getMapObjData() {
	return MiniMapManager::map_obj->getMapObjData();
}