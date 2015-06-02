#pragma once
#include "../MiniMapBase.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class MapObjectList;


class TestMap : public MiniMapBase {
public: TestMap();
public: void loadMapData() override;
};