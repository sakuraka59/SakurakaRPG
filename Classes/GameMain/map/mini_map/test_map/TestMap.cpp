#include "TestMap.h"

TestMap::TestMap() : MiniMapBase() {
	this->hoge = 1;
	this->_map_data_base = {
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 1, 1 },
	};


}
void TestMap::loadMapData() {


}