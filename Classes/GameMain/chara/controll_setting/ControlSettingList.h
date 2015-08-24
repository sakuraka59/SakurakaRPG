#pragma once
#include <unordered_map>
#include "../../item/equip_item/weapon/weaponType.h"

using namespace std;

class ControllSetting;
class CharaPlayer;

class ControllSettingList {
private: CharaPlayer* _chara_obj;
private: unordered_map<weaponType, unordered_map<weaponType, ControllSetting*>>_controll_setting_list;

public: ControllSettingList(CharaPlayer* chara_obj);

public: ControllSetting* getControllSetting();

public: ControllSetting* testControllSetting(weaponType main_weapon, weaponType sub_weapon);


};