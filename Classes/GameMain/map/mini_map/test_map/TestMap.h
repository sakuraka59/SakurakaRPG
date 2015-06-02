#pragma once
#include "../MiniMapBase.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class MapObjectList;


class TestMap : public MiniMapBase {
public: TestMap() {

	list<list<int>>map_data{
		{ 1, 5, 5, 3, 5, 3, 5, 3, 5, 5, 3, 3 },
		{ 5, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 5, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 5, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 5, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 5, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3 },
		{ 5, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3 },
	};
	this->_map_data_base = map_data;

}

};