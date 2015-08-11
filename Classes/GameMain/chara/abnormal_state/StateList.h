#pragma once
#include <unordered_map>		// ハッシュテーブル
#include "StateBase.h"
#include "abnormalStateType.h"

class CharaBase;

class StateList {

//	private Dictionary<abnormalStateType, StateBase> _state_list = new Dictionary<abnormalStateType, StateBase>();
//	private List<abnormalStateType> _guard_state_list = new List<abnormalStateType>();

private: std::unordered_map<abnormalStateType, StateBase*> _state_list;
private: std::unordered_map<abnormalStateType, abnormalStateType> _guard_state_list;
// ------------------------------------------------------------------
public: StateList(CharaBase* chara_obj);
public: void Update();

// 効果を付与
// effect_num、effect_frameは持続効果で専用に使用する
public: void setState(abnormalStateType state_type, int state_level, int effect_num = 0, int effect_frame = 0);
public: void endState(abnormalStateType state_type);
public: bool checkToSetState(abnormalStateType state_type, int state_level, int state_rate, int effect_num = 0, int effect_frame = 0);
public: bool getStateEndFlag(abnormalStateType state_type);
public: std::unordered_map<abnormalStateType, StateBase*> getStateList();
public: void setEquipItemToState(abnormalStateType state_type, EquipItem* item_obj);
public: void removeEquipItemToState(abnormalStateType state_type, EquipItem* item_obj);
// guard ----------------------------------------------------
public: void setStateGuard(abnormalStateType state_type);
// resist ---------------------------------------------------
public: void setSeedStateResist(abnormalStateType state_type, int state_rate);

};