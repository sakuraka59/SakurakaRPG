#include "MapMoveManager.h"
#include "MapMoveData.h"

// private‚Å‚àéŒ¾‚Í•K—v

MapMoveData* MapMoveManager::_map_move_obj;

void MapMoveManager::updateInit(){
	MapMoveManager::_map_move_obj = nullptr;
}
bool MapMoveManager::checkMapMove() {
	if (MapMoveManager::_map_move_obj != nullptr) {
		return true;
	}
	return false;
}
void MapMoveManager::setMapMoveData(MapMoveData* map_move_obj) {
	if (MapMoveManager::_map_move_obj != nullptr) {
		return;
	}
	MapMoveManager::_map_move_obj = map_move_obj;
}
MapMoveData* MapMoveManager::getMapMoveData() {
	
	return MapMoveManager::_map_move_obj;
}