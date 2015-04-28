#ifndef __STATE_BASE__
#define __STATE_BASE__

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

protected: CharaBase* _chara_obj;

// resist 10000 to Completely resist or 0 down to no resist 
protected: int _state_resist = 0;				// seed to default resist
protected: int _state_resist_correction = 0;		//
// equip item address to set
protected: std::list<EquipItem> _equip_list;

};
#endif // __STATE_BASE__