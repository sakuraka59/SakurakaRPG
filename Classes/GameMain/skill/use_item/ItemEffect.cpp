#include "ItemEffect.h"
#include "../../chara/CharaBase.h"
ItemEffect::ItemEffect(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list,
	unordered_map<mainStateType, int> default_state, unordered_map<mainStateType, int> correct_state, int effect_frame_num)
	: SkillMyself(use_chara_obj, all_chara_list) {

	// 装備種制限 なし
	this->_main_weapon_list[weaponType::all_weapon] = weaponType::all_weapon;

	// 回復などのステータスをセット
	this->_default_state = default_state;

	// 能力補正用のステータスをセット
	this->_correct_state = correct_state;
	
	// 効果時間をセット
	this->_effect_frame_num = effect_frame_num;
}
void ItemEffect::skillInit() {
	this->_use_chara_obj->setAttackFrame(40);
	this->_use_chara_obj->setSkillFrame(30);
	//			Debug.WriteLine("[TestHeal]set skill init");
}

void ItemEffect::attackHitEffect(CharaBase* check_chara_obj) {
	
	int state_frame = 0;
	// 回復系
	for (auto state_data : this->_default_state) {
		if (state_data.second == 0)  {
			continue;
		}

		switch (state_data.first) {
		case mainStateType::hp:
//			check_chara_obj->healHp(state_data.second);
			check_chara_obj->checkToSetState(abnormalStateType::hp_effect, 1, 10000, state_data.second, this->_effect_frame_num);
			break;
		case mainStateType::sp:
			check_chara_obj->checkToSetState(abnormalStateType::sp_effect, 1, 10000, state_data.second, this->_effect_frame_num);
//			check_chara_obj->healSp(state_data.second);
			break;
		case mainStateType::honey:
			check_chara_obj->checkToSetState(abnormalStateType::honey_effect, 1, 10000, state_data.second, this->_effect_frame_num);
			//check_chara_obj->healHoney(state_data.second);
			break;
		case mainStateType::excitation:
			check_chara_obj->healExcitation(100);
			break;
		case mainStateType::satiety:
			check_chara_obj->checkToSetState(abnormalStateType::satiety_effect , 1, 10000, state_data.second, this->_effect_frame_num);
			break;
		}
	}

	// 攻撃補助系
	for (auto correct_data : this->_correct_state) {
		if (correct_data.second == 0)  {
			continue;
		}
		abnormalStateType correction_state_type = abnormalStateType::_no_type;
		switch (correct_data.first) {
		case mainStateType::hp:
			correction_state_type = abnormalStateType::hp_correct;
			break;
		case mainStateType::sp:
			correction_state_type = abnormalStateType::sp_correct;
			break;
		case mainStateType::atk:
			correction_state_type = abnormalStateType::atk_correct;
			break;
		case mainStateType::def:
			correction_state_type = abnormalStateType::def_correct;
			break;
		case mainStateType::magic:
			correction_state_type = abnormalStateType::magic_correct;
			break;
		case mainStateType::mdef:
			correction_state_type = abnormalStateType::mdef_correct;
			break;
		}
		if (correction_state_type == abnormalStateType::_no_type) {
			continue;
		}
		check_chara_obj->checkToSetState(correction_state_type, 1, 10000, correct_data.second, this->_effect_frame_num);
	}
//	check_chara_obj->healHp(1000);
	//			Debug.WriteLine("[TestHeal]attackHitEffect");
}