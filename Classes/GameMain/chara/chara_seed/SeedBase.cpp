#include "SeedBase.h"
// #include PartSetBase.h
// #include EquipSprite.h
// #include StateList.h
#include "../CharaBase.h"

#include "../abnormal_state/StateList.h"


/*
class PartSetBase;
class EquipSprite;
class StateList;
class CharaBase;
*/
SeedBase::SeedBase() {

	/*
	this._test_point = i;
	this._draw_x = (int)(this._test_point /20) * 40;
	this._draw_y = 70;// 544/2;
	this._draw_y += (this._test_point % 20) * 50;
	//this.Order = this._draw_y;
	// 画像スプライト宣言
	Bounds2 bounds = base_scene.Camera2D.CalcBounds();

	// 画像表示サイズ
	Vector2i numcells = new Vector2i(10,0);
	Vector2 cellsize = bounds.Size / numcells.Vector2();
	*/
	// 画像表示 -------------------
	/*
	// 読み込み
	this._sprite_data = ResourceManage.getSpriteTile("/Application/res/Objects.png",7,3);

	// スプライト内での表示内容設定
	this._sprite_data.TileIndex2D = new Vector2i(4,2);

	// 表示基準点を中央へ
	this._sprite_data.CenterSprite();
	*/
	// 表示位置の調整
	// Vita 解像度 960,544

//	this->_seed_state_list = std::make_unique<StateList>();
}

void SeedBase::Update() {

}
// 画像
void SeedBase::setSpriteData(std::string file_name, int x, int y) {

	this->_file_name = file_name;
	this->_file_x = x;
	this->_file_y = y;
	// 読み込み
	//this._base_sprite_data = ResourceManage.getSpriteTile(fine_name,x,y);
}
double SeedBase::getHeight() {
	return this->_height;
}
double SeedBase::getWidthHalf() {
	return this->_width;
}
int SeedBase::getCorrectX(){
	return this->_draw_correct_x;
}
int SeedBase::getCorrectY(){
	return this->_draw_correct_y;
}
float SeedBase::getScalePer() {
	return this->_scale_per;
}
double SeedBase::getRunSpeed() {
	return this->_run_speed;
}
double SeedBase::getWalkSpeed() {
	return this->_walk_speed;
}

int SeedBase::getBaseHp() {
	return this->_base_hp;
}
int SeedBase::getBaseSp() {
	return this->_base_sp;
}
int SeedBase::getBaseCc() {
	return this->_base_cc;
}

std::unique_ptr<StateList>& SeedBase::getStateList(std::unique_ptr<CharaBase>& chara_obj) {
	this->_seed_state_list = std::make_unique<StateList>(chara_obj);
	this->setStateList(chara_obj);
	return this->_seed_state_list;
}

void SeedBase::setStateList(std::unique_ptr<CharaBase>& chara_obj) {

}
// vision data ----------------------------------------------
double SeedBase::getVisionRange() {
	return this->_vision_range;
}
double SeedBase::getVisionAngle() {
	return this->_vision_angle;
}
double SeedBase::getUnvisionRange() {
	return this->_unvision_range;
}
// search list ----------------------------------------------
std::list<charaGroupList> SeedBase::getMyGroupList() {
	return this->_my_group_list;
}
std::list<charaGroupList> SeedBase::getFellowGroupList() {
	return this->_fellow_group_list;
}

std::list<charaGroupList> SeedBase::getTargetGroupList() {
	return this->_target_group_list;
}
