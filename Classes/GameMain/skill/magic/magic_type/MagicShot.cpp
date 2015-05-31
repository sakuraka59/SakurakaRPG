#include "MagicShot.h"
#include "../../../chara/CharaBase.h"
MagicShot::MagicShot(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillMagic(use_chara_obj, all_chara_list)
{

}
void MagicShot::skillInit() {
	SkillMagic::skillInit();
	this->_use_chara_obj->setSpellStatus(1);
}
void MagicShot::skillActiveEffect(CharaBase* check_chara_obj) {
	this->_use_chara_obj->setSkillFrame(this->_magic_skill_frame);	// ���̃X�L�����Z�b�g�ł���悤�ɂȂ�܂ł̎���
	this->_use_chara_obj->setAttackFrame(this->_magic_attack_frame);	// ���S�ɍs�����\�ɂȂ�܂ł̎���
	this->_use_chara_obj->sendComment(this->_magic_active_comment);
	this->_use_chara_obj->resetSpellStatus();
	this->_use_chara_obj->setMagicList(this->_magic_active_obj);
	this->_use_chara_obj->setShadowList(this->_magic_active_obj);
	//chara_obj->setShadowList(this);

}