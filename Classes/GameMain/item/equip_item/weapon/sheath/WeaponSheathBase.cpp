#include "WeaponSheathBase.h"
#include "../../../../chara/CharaBase.h"

#include "../../../../GameMain.h"
#include "../../../../GameUi/ItemUi.h"

WeaponSheathBase::WeaponSheathBase() : WeaponBase()
{
	this->_weapon_type = weaponType::sheath;
	this->_item_equip_type = equipType::sub_weapon;

}
bool WeaponSheathBase::checkExtendEquipItem() {
	// ���łɏ⑕�����́A�O����K�v������̂ŁA�`�F�b�N��ʂ�
	if (this->_chara_obj->getSubWeaponType() == weaponType::sheath) {
		return true;
	}
	// �Ў蒼���𑕔����̂݁A�����\
	if (this->_chara_obj->getMainWeaponType() == weaponType::sword) {
		return true;
	}
	return false;
}

// ���������ɂ�鑕�������`�F�b�N
bool WeaponSheathBase::checkEquipRelease() {
	weaponType main_weapon_type = this->_chara_obj->getMainWeaponType();
	if (main_weapon_type != weaponType::sword) {
		GameMain::_item_ui_obj->removeEquipItem(this);
		return true;
	}
	return false;
}