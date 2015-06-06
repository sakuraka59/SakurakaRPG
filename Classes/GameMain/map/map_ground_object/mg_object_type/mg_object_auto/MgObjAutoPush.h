#pragma once
#include "../MgObjectAuto.h"

using namespace std;

class MgObjAutoPush : public MgObjectAuto {

private: list<CharaBase*> _active_chara_list;
private: list<CharaBase*> _before_chara_list;

public: MgObjAutoPush(int map_block_x, int map_block_y);
public: void UpdateInit() override;
public: void activeObject(CharaBase* chara_obj) override;

};