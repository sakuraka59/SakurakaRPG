#pragma once
#include <unordered_map>		// ハッシュテーブル
#include <memory>
#include "StateBase.h"
#include "abnormalStateType.h"

class CharaBase;

class StateList {

//	private Dictionary<abnormalStateType, StateBase> _state_list = new Dictionary<abnormalStateType, StateBase>();
//	private List<abnormalStateType> _guard_state_list = new List<abnormalStateType>();

private: std::unordered_map<abnormalStateType, std::shared_ptr<StateBase>> _state_list;
private: std::unordered_map<abnormalStateType, abnormalStateType> _guard_state_list;
// ------------------------------------------------------------------
public: StateList(std::shared_ptr<CharaBase> chara_obj);
public: void Update();
public: void setState(abnormalStateType state_type, int state_level);
public: void endState(abnormalStateType state_type);
public: bool checkToSetState(abnormalStateType state_type, int state_level, int state_rate);
public: bool getStateEndFlag(abnormalStateType state_type);
public: std::unordered_map<abnormalStateType, std::shared_ptr<StateBase>> getStateList();
public: void setEquipItemToState(abnormalStateType state_type, std::shared_ptr<EquipItem> item_obj);
public: void removeEquipItemToState(abnormalStateType state_type, std::shared_ptr<EquipItem> item_obj);
// guard ----------------------------------------------------
public: void setStateGuard(abnormalStateType state_type);
// resist ---------------------------------------------------
public: void setSeedStateResist(abnormalStateType state_type, int state_rate);

};