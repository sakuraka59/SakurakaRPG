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
// �ʏ��UPDATE�������ƈړ�������s��Ȃ��֌W�ŁA
// �I�u�W�F�N�g�������ɔj������Ă��܂�
// ���̂��߂Ɉړ��I���t���O����I�u�W�F�N�g��j�󂵂Ȃ��悤�ɃI�[�o�[���C�h����
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
	// �r�������ǂ���
	if (this->_spell_frame_time < this->_starting_magic_frame) {
		//this->_starting_magic_frame -= 1;

		// �r���󋵐i�߂�

		if (this->_spell_list_itr != this->_spell_list.end()) {
			// ����̈�ԍŏ��̃f�[�^���擾����
			
			SkillMagicSpell* spell_obj = *this->_spell_list_itr;
			if (this->_spell_frame_time >= spell_obj->getSendFrame()) {
				this->_use_chara_obj->sendDirectComment(spell_obj->getSpell());
				
				this->_spell_list_itr++;
			}
		}
		/*
		if (this->_spell_list.size() > 0 ) {
			// ����̈�ԍŏ��̃f�[�^���擾����
			SkillMagicSpell* spell_obj = this->_spell_list.front();
			
			if (this->_spell_frame_time >= spell_obj->getSendFrame()) {
				this->_use_chara_obj->sendDirectComment(spell_obj->getSpell());
				
				this->_spell_list.pop_front();
			}
		}
		// */
		this->_spell_frame_time++;
		// �r���i�߂Ă��I���Ȃ��ꍇ�A�����I��
		if (this->_spell_frame_time < this->_starting_magic_frame) {
			return false;
		}
	}

	if (this->_spell_frame_time >= this->_starting_magic_frame) {
		// ���@����
		this->skillActiveEffect(this->_use_chara_obj);
		// ���@�𔭓������̂ŃX�L������j������
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