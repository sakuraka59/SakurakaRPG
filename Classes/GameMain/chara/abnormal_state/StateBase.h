#pragma once
#include <unordered_map>		// ハッシュテーブル


class CharaBase;
class EquipItem;

class StateBase {

protected: int _state_type = 0;
protected: enum stateType {
	autoHeal = 0,	// auto heal
	manualHeal,		// manual heal -> heal time
	eventOnly,		// event only heal
	typeMax
};

protected: std::string _state_name = "";

// autoHeal to auto time
// manualHeal to unlock flag on time
protected: int _repair_frame = 0;
protected: int _now_frame = (-1);			// manual heal to release time

protected: int _manual_state = 0;		// manual heal start flag
protected: enum manualState {
	releaseEnd = 1,
	releaseNow,
	releaseOk,
	releaseNg,
	stateMax
};

protected: int _manual_release_frame = 0;	// manual heal to release time
protected: bool _end_flag = true;
protected: int _state_level = 0;
protected: int _effect_count = 0;
protected: int _effect_interval = 1;

protected: std::shared_ptr<CharaBase> _chara_obj;

// resist 10000 to Completely resist or 0 down to no resist 
protected: int _state_resist = 0;				// seed to default resist
protected: int _state_resist_correction = 0;		//
// equip item address to set
protected: std::list<std::shared_ptr<EquipItem>> _equip_list;

//-------------------------------------------------------------------
public: StateBase(std::shared_ptr<CharaBase> chara_obj);
public: virtual bool Update();
protected: virtual void stateUpdate();
protected: void stateEffectCheck();
protected: virtual void EveryFrameEffect();
protected: virtual void stateEffect();
protected: virtual void endStateEffect();
public: void setState(int state_level);
public: void endState();
public: void setEquipItem(std::shared_ptr<EquipItem> equip_item);
public: void removeEquipItem(std::shared_ptr<EquipItem> equip_item);
public: bool getEndFlag();
public: std::string getStateName();
public: int getRepairFrame();
public: int getNowFrame();
// resist ---------------------------------------------------
public: int getStateResist();
public: void setSeedStateResist(int seed_rate);
};
