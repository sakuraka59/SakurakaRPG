#include "SkillMagic.h"
#include "../../chara/CharaBase.h"
#include "../SkillMagicSpell.h"

SkillMagic::SkillMagic(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillBase(use_chara_obj, all_chara_list)
{

}
void SkillMagic::skillInit() {
	this->_use_chara_obj->setAttackFrame(this->_starting_magic_frame + 1);
	this->_spell_frame_time = 0;
	this->_delete_flag = false;
	this->_spell_list_itr = this->_spell_list.begin();
}
//-----------------------------------------------------------
// 通常のUPDATE処理だと移動動作を行わない関係で、
// オブジェクトがすぐに破棄されてしまう
// そのために移動終了フラグからオブジェクトを破壊しないようにオーバーライドする
//-----------------------------------------------------------
void SkillMagic::Update() {

	if (this->_delete_flag == true) {

		return;
	}
	bool check_attack_flag = this->updateSkillEffect();

	if (check_attack_flag == true) {

		this->setDeleteFlag();
	}


}
bool SkillMagic::updateSkillEffect() {

//	Debug.WriteLine("[SkillMagic]check spell frame:" + this->_spell_frame_time + "/" + this->_starting_magic_frame);
	// 詠唱中かどうか
	if (this->_spell_frame_time < this->_starting_magic_frame) {
		//this->_starting_magic_frame -= 1;

		// 詠唱状況進める

		if (this->_spell_list_itr != this->_spell_list.end()) {
			// 現状の一番最初のデータを取得する
			
			SkillMagicSpell* spell_obj = *this->_spell_list_itr;
			if (this->_spell_frame_time >= spell_obj->getSendFrame()) {
				this->_use_chara_obj->sendDirectComment(spell_obj->getSpell());
				
				this->_spell_list_itr++;
			}
		}
		/*
		if (this->_spell_list.size() > 0 ) {
			// 現状の一番最初のデータを取得する
			SkillMagicSpell* spell_obj = this->_spell_list.front();
			
			if (this->_spell_frame_time >= spell_obj->getSendFrame()) {
				this->_use_chara_obj->sendDirectComment(spell_obj->getSpell());
				
				this->_spell_list.pop_front();
			}
		}
		// */
		this->_spell_frame_time++;
		// 詠唱進めても終わらない場合、処理終了
		if (this->_spell_frame_time < this->_starting_magic_frame) {
			return false;
		}
	}

	if (this->_spell_frame_time >= this->_starting_magic_frame) {
		// 魔法発動
		this->skillActiveEffect(this->_use_chara_obj);
		// 魔法を発動したのでスキル情報を破棄する
		this->setDeleteFlag();
		return true;
	}
	return false;
	/*
	this->setMagicEffect();
	this->setDeleteFlag();
	return true;
	*/
}
void SkillMagic::skillActiveEffect(CharaBase* check_chara_obj) {

}