#include "HaveItemListBase.h"

HaveItemListBase::HaveItemListBase()
{
}

void HaveItemListBase::setCharaObj(CharaBase* chara_obj)
{
	this->_chara_obj = chara_obj;
	this->testItemList();
}
void HaveItemListBase::testItemList() {

}