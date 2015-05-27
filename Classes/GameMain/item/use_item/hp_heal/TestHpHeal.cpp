#include "TestHpHeal.h"

#include "../../../chara/CharaPlayer.h"
TestHpHeal::TestHpHeal(CharaBase* chara_obj) : UseItem(chara_obj)
{
	this->_num = 3;
}
bool TestHpHeal::useSkill() {
	return true;
	/*
	bool use_flag = this->_chara_obj->setSkill(new TestHeal(this._chara_obj, this._chara_obj.getAllCharaList()));

	return use_flag;
	*/
}