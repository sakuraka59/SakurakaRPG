#include "TestHpHeal.h"

#include "../../../skill/hp_heal/TestHeal.h"

#include "../../../chara/CharaPlayer.h"
TestHpHeal::TestHpHeal(CharaBase* chara_obj) : UseItem(chara_obj)
{
//	this->_num = 10;
	this->_have_item_type = haveItemType::portion;
}
bool TestHpHeal::useSkill() {

	
	bool use_flag = this->_chara_obj->setSkill(new TestHeal(this->_chara_obj, this->_chara_obj->getAllCharaList()));

	return use_flag;
	//*/
}