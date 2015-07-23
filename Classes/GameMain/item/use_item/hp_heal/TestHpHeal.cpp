#include "TestHpHeal.h"

#include "../../../skill/hp_heal/TestHeal.h"

#include "../../../chara/CharaPlayer.h"
TestHpHeal::TestHpHeal() : UseItem()
{
//	this->_num = 10;
	this->_item_name = "テスト用HP回復薬";
	this->_have_item_type = haveItemType::portion;
	this->setUseItemId("test_hp_heal");
}
bool TestHpHeal::useSkill() {

	
	bool use_flag = this->_chara_obj->setSkill(new TestHeal(this->_chara_obj, this->_chara_obj->getAllCharaList()));

	return use_flag;
	//*/
}