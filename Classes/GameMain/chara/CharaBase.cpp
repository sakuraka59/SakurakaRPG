#include <math.h>
#include "../GAME_SETTING.h"
#include "CharaBase.h"

#include "../item/use_item/HaveUseItemList.h"
#include "../item/equip_item/HaveEquipItemList.h"
#include "abnormal_state\StateList.h"
#include "equipType.h"

#include "chara_seed/SeedBase.h"
#include "../hit/HitCircle.h"

#include "../item/equip_item/EquipItem.h"
#include "../item/equip_item/weapon/WeaponBase.h"

#include "../skill/SkillBase.h"

#include "../shadow/ShadowObjectList.h"

#include "../GameCamera.h"

using namespace cocos2d;

CharaBase::CharaBase()
{
	this->_use_item_list = new HaveUseItemList(this);
	this->_use_item_list->autorelease();
	this->_equip_item_list = new HaveEquipItemList(this);
	this->_state_list = new StateList(this);
	this->_set_now_skill = nullptr;

	//this->CenterSprite();
	
	for (int equip_type = static_cast<int>(equipType::no_type) + 1; equip_type < static_cast<int>(equipType::enum_end); equip_type++) {
		this->_equip_list[static_cast<equipType>(equip_type)] = 0;
	}
	/*
	foreach(equipType equip_type in Enum.GetValues(typeof(equipType))) {
		this->_equip_list[equip_type] = nullptr ;
	}
	*/
	this->_skill_chain_num = 0;
	/*
	this->_test_label = new Label();
	this->_test_label.Position = new Vector2(-20, -20);
	this->_test_label.Text = "angle: " + this->_move_angle + "\n x :" + this->_draw_x + "\n y :" + this->_draw_y;
	this->_test_label.Color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	this->AddChild(this->_test_label);
	*/


//	TTFConfig conf_test("fonts/arial.ttf", 16);
	this->_test_label = "angle: ";
	
	this->_label_obj = LabelTTF::create(this->_test_label, "fonts/arial.ttf", 16);
	//label_obj->setColor(Color3B::WHITE);
	this->_label_obj->setPosition(-20, -70);
	this->addChild(this->_label_obj);

}
void CharaBase::SetCharaHitData() {
	this->_hit_circle_obj = new HitCircle(this, this->_chara_seed->getWidthHalf());

}
void CharaBase::Update() {

	if (this->_set_now_skill != nullptr) {
		this->_set_now_skill->Update();
	}
	this->commonUpdate();
	this->mainUpdate();

	// last update
	this->updateBlockPoint();

	if (this->_set_now_skill != nullptr) {
		if (this->_set_now_skill->getDeleteFlag() == true) {
			/*
			SkillBase* delete_skill_obj = this->_set_now_skill;
			this->_set_now_skill = nullptr;
			this->_set_now_skill = nullptr;
			*/
		}
	}
}
void CharaBase::mainUpdate() {

}
void CharaBase::updateBlockPoint() {
	this->_map_block_x = (int)floor(this->_draw_x / MAP_BLOCK_WIDTH);
	this->_map_block_y = (int)floor(this->_draw_y / MAP_BLOCK_HEIGHT);
}
//-----------------------------------------------------------
//	プレイヤー、NPC共通の更新処理
//-----------------------------------------------------------
void CharaBase::commonUpdate() {

	// 性的ステータスを自動回復させる
	this->autoHealSexual();
	//if 
	if (this->_now_state[mainStateType::hp] <= 0 && this->_down_flag == false) {
		this->charaDownMoment();
	}

	if (this->_down_flag == true) {
		this->charaDownUpdate();
	}
	this->updateDamagePush();
	this->updateJump();
	this->_state_list->Update();
	this->countActionFrame();
	this->_chara_seed->Update();

	// 行動可能時、スキル情報やターゲット情報を破棄
	if (this->_attack_frame <= 0) {
		this->resetTargetChara();
		this->removeSkill();
		if (this->_skill_chain_num > 0) {
			this->_skill_chain_num = 0;
		}
	}
}
//-----------------------------------------------------------
// HP0によるダウンした瞬間の処理
//-----------------------------------------------------------
void CharaBase::charaDownMoment() {
	this->_down_flag = true;
	this->_now_state[mainStateType::hp] = 0;
	this->_revival_frame = this->_REVIVAL_TIME + 1;	// 現在フレームから処理開始するので+1フレーム分追加する
	this->allActionCancel();
	this->charaDownMomentDetail();

	// ダウンなので、スキル強制解除
	this->removeSkill();
	//this->_
	//setDeleteFlag

}
bool CharaBase::getDownFlag() {
	return this->_down_flag;
}
void CharaBase::charaDownMomentDetail() {

}
void CharaBase::charaDownUpdate() {

	if (this->_state_list->getStateEndFlag(abnormalStateType::extasy)) {
		this->_revival_frame--;
	}
	if (this->_revival_frame <= 0 && this->_state_list->getStateEndFlag(abnormalStateType::absent_mindedness)) {

		this->charaRevival();
	}
}
//-----------------------------------------------------------
// キャラクターが復活した際の処理
//-----------------------------------------------------------
void CharaBase::charaRevival() {

}
void CharaBase::allActionCancel() {

}
//-----------------------------------------------------------
// キャラクターの移動の更新処理を行う
//-----------------------------------------------------------
void CharaBase::updateMove(double move_speed) {

	if (this->_no_control_frame > 0 || this->_down_flag == true ||
		this->_attack_frame > 0 || this->_skill_frame > 0) {
		return;
	}
	if (this->checkSpellFlag() == true) {
		return;
	}

	/*
	if (this->_attack_frame <= 0) {
	this->resetTargetChara();
	}
	*/
	//this->_move_angle = angle();

	//double move_speed = this->_chara_seed.getRunSpeed();

	this->_move_x = (double)(cos(this->_move_angle * M_PI / 180) * move_speed);
	this->_move_y = (double)(sin(this->_move_angle * M_PI / 180) * move_speed);

	if (this->_move_x < 0.00001f && this->_move_x > -0.00001f) {
		this->_move_x = 0;
	}
	if (this->_move_y < 0.00001f && this->_move_y > -0.00001f) {
		this->_move_y = 0;
	}
	
	this->_draw_x += this->_move_x;
	this->_draw_y += this->_move_y;

//	this->setPosition((float)this->_draw_x, (float)this->_draw_y);
	//this->Position = new Vector2((int)this->_draw_x, (int)this->_draw_y);

}
void CharaBase::updateMagicPoint() {
	if (this->_no_control_frame > 0 || this->_down_flag == true ||
		this->_attack_frame > 0 || this->_skill_frame > 0) {
		return;
	}
}
// jump
bool CharaBase::setJumpNormal(double jump_speed) {
	// if chara of ground
	if (this->checkActionFlag() != true) {
		return false;
	}
	if (this->_draw_z <= 0) {
		this->_draw_z = jump_speed;
		this->_jump_speed = jump_speed;

		return true;
	}
	return false;
}
bool CharaBase::setJumpForcing(double jump_speed) {
	if (this->_draw_z <= 0 && jump_speed >= 0) {
		this->_draw_z = jump_speed;
	}

	if (this->_draw_z <= 0 && jump_speed <= 0) {

	}
	else {
		this->_jump_speed = jump_speed;
	}

	return true;

}
void CharaBase::updateJump() {
	//jump to update			
	bool update_draw_flag = false;
	if (this->_draw_z > 0) {
		this->_jump_speed -= this->_fall_speed;
		this->_draw_z += this->_jump_speed;
		update_draw_flag = true;
	}

	if (this->_draw_z < 0 && this->_jump_speed < 0) {
		this->_jump_speed = 0;
		this->_draw_z = 0;
		update_draw_flag = true;
	}
	else if (this->_draw_z > 0 && this->_no_control_frame > 0 && this->_no_control_frame <= 30) {
		this->_no_control_frame = 30 + 1;
	}

	if (update_draw_flag == true) {
		this->updateDraw();
	}
}
bool CharaBase::checkGroundFlag() {
	if (this->_draw_z > 0) {
		return false;
	}
	return true;
}
// skill to move
void CharaBase::updateSkillMove(double add_angle, double move_speed_1frame, double jump_power) {


	if (this->_no_control_frame > 0 || this->_attack_frame <= 0) {
		return;
	}

	//Debug.WriteLine("move angle:"+move_speed_1frame);
	this->_move_x = (double)(cos((this->_move_angle + add_angle) * M_PI / 180) * move_speed_1frame);
	this->_move_y = (double)(sin((this->_move_angle + add_angle) * M_PI / 180) * move_speed_1frame);

	if (this->_move_x < 0.00001f && this->_move_x > -0.00001f) {
		this->_move_x = 0;
	}
	if (this->_move_y < 0.00001f && this->_move_y > -0.00001f) {
		this->_move_y = 0;
	}
	this->_draw_x += this->_move_x;
	this->_draw_y += this->_move_y;

	if (jump_power > 0) {
		this->setJumpForcing(jump_power);
	}
	///			this->updateCameraMove();

}
void CharaBase::updateDraw() {
	//this->Position = this->getDrawPosition();
	// test
	Vec2* set_position = this->getDrawPosition();
	this->setPosition(*set_position);
	delete set_position;
	//------------------------------
	//this->Position = new Vector2((int)(this->_draw_x - this->_play_camera.getCameraX() - (this->_move_x * this->_move_speed_per)), (int)(this->_draw_y - this->_play_camera.getCameraY() + this->_draw_z - (this->_move_y * this->_move_speed_per)));
	//this->Position = new Vector2((int)(this->_draw_x), (int)(this->_draw_y));

	this->_test_label =
		"x :" + std::to_string(this->_draw_x) +
		"\n y :" + std::to_string(this->_draw_y) +
		"\n z :" + std::to_string(this->_draw_z) +
		"\n hp :" + std::to_string(this->_now_state[mainStateType::hp] / 100) +
		"\n map x :" + std::to_string(this->_map_block_x) +
		"\n map y :" + std::to_string(this->_map_block_y) +
		"\n ほげぴよー huga";

	this->_label_obj->setString(this->_test_label);

	/*
	this->_test_label.Text = " angle: " + this->_move_angle +
		"\n angle_direction " + this->_move_angle_direction +
		"\n x :" + this->_draw_x +
		"\n y :" + this->_draw_y +
		"\n z :" + this->_draw_z +
		"\n before_x :" + this->_before_x +
		"\n before_y :" + this->_before_y +
		"\n map x :" + this->_map_block_x +
		"\n map y :" + this->_map_block_y +
		"\n move speed per :" + this->_move_speed_per +
		"\n hp :" + (this->_now_state[mainStateType.hp] / 100) + "." + (this->_now_state[mainStateType.hp] % 100).ToString("00") +
		"/ " + (this->getMaxState(mainStateType.hp) / 100) + "." + (this->getMaxState(mainStateType.hp) % 100).ToString("00") +
		"\n atk:" + this->_correction_state[mainStateType.atk] +
		"\n _spell_point_x:" + this->_spell_point_x +
		"\n _spell_point_y:" + this->_spell_point_y +
		"\n main weapon :" + this->getMainWeaponType() +
		"\n  sub weapon :" + this->getSubWeaponType() +
		"\n weapon state:" + this->getWeaponState() +
		"\n _no_control_frame:" + this->_no_control_frame +
		"\n _attack_frame:" + this->_attack_frame +
		"\n _skill_frame:" + this->_skill_frame +
		"\n _push_speed:" + this->_push_speed +
		"\n _skill_chain_num:" + this->_skill_chain_num +
		"\n checkSpellFlag:" + this->checkSpellFlag()


		;


	*/
	//------------------------------
	this->_before_x = this->_draw_x;
	this->_before_y = this->_draw_y;
}
cocos2d::Vec2* CharaBase::getDrawPosition() {
	return new cocos2d::Vec2((float)this->getDrawPositionX(), (float)(this->getDrawPositionY() + this->_draw_z));
}
float CharaBase::getDrawPositionX() {
	return (float)(this->_draw_x);

//	return (float)(this->_draw_x - this->_play_camera->getCameraX());


	//return new Vector2((float)(this->_draw_x - this->_play_camera.getCameraX()), (float)(this->_draw_y - this->_play_camera.getCameraY() + this->_draw_z));	
}
float CharaBase::getDrawPositionY() {
	return (float)(this->_draw_y);

//	return (float)(this->_draw_y - this->_play_camera->getCameraY());


	//return new Vector2((float)(this->_draw_x - this->_play_camera.getCameraX()), (float)(this->_draw_y - this->_play_camera.getCameraY() + this->_draw_z));	
}
void CharaBase::updateMoveAngle(double angle) {
	// 詠唱中は別動作を行う
	if (this->checkSpellFlag() == true) {
		this->updateSpellAim(angle);
	}
	else {
		this->_move_angle = angle;
		this->updateMoveAngleDirection();
	}
}
void CharaBase::updateMoveAngleDirection() {

	if (this->_move_angle <= 22.5) {
		this->_move_angle_direction = 0;
	}
	else if (this->_move_angle <= 67.5) {
		this->_move_angle_direction = 45;
	}
	else if (this->_move_angle <= 112.5) {
		this->_move_angle_direction = 90;
	}
	else if (this->_move_angle <= 157.5) {
		this->_move_angle_direction = 135;
	}
	else if (this->_move_angle <= 202.5) {
		this->_move_angle_direction = 180;
	}
	else if (this->_move_angle <= 247.5) {
		this->_move_angle_direction = 225;
	}
	else if (this->_move_angle <= 292.5) {
		this->_move_angle_direction = 270;
	}
	else if (this->_move_angle <= 337.5) {
		this->_move_angle_direction = 315;
	}
	else if (this->_move_angle <= 360) {
		this->_move_angle_direction = 00;
	}
}
int CharaBase::getMoveAnagleDirection() {
	this->updateMoveAngleDirection();
	return this->_move_angle_direction;
}
//-----------------------------------------------------------
//	詠唱中の方向変更や
void CharaBase::updateSpellAim(double angle) {
	switch (this->_spell_status) {
	case 1:
		// 方向指定の魔法の場合
		this->_move_angle = angle;
		this->updateMoveAngleDirection();
		break;
	case 2:
		// 座標指定の魔法の場合
		double move_speed = this->_spell_point_speed;
		double target_move_x = (double)(cos(angle * M_PI / 180) * move_speed);
		double target_move_y = (double)(sin(angle * M_PI / 180) * move_speed);

		if (target_move_x < 0.00001f && target_move_x > -0.00001f) {
			target_move_x = 0;
		}
		if (target_move_y < 0.00001f && target_move_y > -0.00001f) {
			target_move_y = 0;
		}
		//				double target_move_x = (double)(cos(angle * M_PI / 180 ) * this->_spell_point_speed);	
		//double target_move_y = (double)(sin(angle * M_PI / 180 ) * this->_spell_point_speed);

		this->_spell_point_x += target_move_x;
		this->_spell_point_y += target_move_y;
		//this->_spell_point_x += 1;
		break;

	}

}
SeedBase* CharaBase::getCharaSeed(){
	return this->_chara_seed;
}
HitCircle* CharaBase::getHitCircle() {
	return this->_hit_circle_obj;
}
void CharaBase::setRunSpeedBase(double speed) {
	this->_run_speed_base = speed;
}
void CharaBase::setRunSpeed() {
	this->_run_speed = this->_run_speed_base;
}
double CharaBase::getRunSpeed() {
	return this->_run_speed;
}
void CharaBase::setWalkSpeed(double speed) {
	this->_walk_speed = speed;
}
double CharaBase::getWalkSpeed() {
	return this->_walk_speed;
}
double CharaBase::getMoveAngle() {
	return this->_move_angle;
}
//-----------------------------------------------------------
// 行動に冠する要素の関数
//-----------------------------------------------------------
void CharaBase::setNoControlFrame(int frame_num) {
	this->_no_control_frame = frame_num;
}
// 攻撃後のスキル以外の行動が可能になるまでの時間をセット
void CharaBase::setAttackFrame(int frame_num) {
	this->_attack_frame = frame_num;

}
// 次のスキルが使えるようになるまでの時間を取得
void CharaBase::setSkillFrame(int frame_num) {
	this->_skill_frame = frame_num;
}
// 詠唱状態をセットする
void CharaBase::setSpellStatus(int spell_state) {
	if (spell_state == 1 || spell_state == 2) {
		this->_spell_status = spell_state;
		this->_spell_point_x = 0;
		this->_spell_point_y = 0;
	}
}
// 詠唱状態から復帰する
void CharaBase::resetSpellStatus() {
	this->_spell_status = 0;
	// スキル破棄
}

void CharaBase::setSuperAromurFrame(int frame_num) {
	this->_super_armour_frame = frame_num;
}

int CharaBase::getNoControlFrame() {
	return this->_no_control_frame;
}
int CharaBase::getAttackFrame() {
	return this->_attack_frame;
}
int CharaBase::getSkillFrame() {
	return this->_skill_frame;
}
int CharaBase::getSuperAromurFrame() {
	return this->_super_armour_frame;
}

// state ----------------------------------------------------
void CharaBase::setState() {

	this->_hit_height = this->_chara_seed->getHeight();
	this->_hit_width_half = this->_chara_seed->getWidthHalf();

	for (int state_type = static_cast<int>(mainStateType::no_type) + 1; state_type < static_cast<int>(mainStateType::enum_end); state_type++) {
		//this->_equip_list[static_cast<equipType>(equip_type)] = 0;
		this->_now_state[static_cast<mainStateType>(state_type)] = 0;
		this->_base_state[static_cast<mainStateType>(state_type)] = 0;
		this->_correction_state[static_cast<mainStateType>(state_type)] = 0;
		this->_max_state[static_cast<mainStateType>(state_type)] = 0;
	}

	this->setStateInit(mainStateType::hp, this->_chara_seed->getBaseHp());

	this->setStateInit(mainStateType::sp, this->_chara_seed->getBaseSp());
	this->setStateInit(mainStateType::cc, this->_chara_seed->getBaseCc());

	this->setStateInit(mainStateType::str, 0);
	this->setStateInit(mainStateType::dex, 0);
	this->setStateInit(mainStateType::atk, 0);
	this->setStateInit(mainStateType::def, 0);

	this->_now_state[mainStateType::honey] = 0;
	this->_base_state[mainStateType::honey] = 10000;
	this->_correction_state[mainStateType::honey] = 0;
	this->reColStatus(mainStateType::honey);

	this->_now_state[mainStateType::excitation] = 0;
	this->_base_state[mainStateType::excitation] = 10000;
	this->_correction_state[mainStateType::excitation] = 0;
	this->reColStatus(mainStateType::excitation);

	this->setGroupList();
	this->setRunSpeedBase(this->_chara_seed->getRunSpeed());
	this->setRunSpeed();
	this->setWalkSpeed(this->_chara_seed->getWalkSpeed());
}
void CharaBase::setStateInit(mainStateType state_type, int num) {
	this->_now_state[state_type] = num;
	this->_base_state[state_type] = num;
	this->_correction_state[state_type] = 0;
	this->_max_state[state_type] = num;
}
int CharaBase::getNowState(mainStateType state_type) {
	return this->_now_state[state_type];
}
int CharaBase::getBaseState(mainStateType state_type) {
	return this->_base_state[state_type];
}
int CharaBase::getCorrectionState(mainStateType state_type) {
	return this->_correction_state[state_type];
}
int CharaBase::getMaxState(mainStateType state_type) {
	return this->_max_state[state_type];
}

void CharaBase::addCorrectionState(mainStateType state_type, int num) {
	this->_correction_state[state_type] += num;
	this->calNowState(state_type);

}
void CharaBase::calNowState(mainStateType state_type) {
	this->_now_state[state_type] = this->_base_state[state_type] + this->_correction_state[state_type];
}
double CharaBase::getHitHeight() {
	return this->_hit_height;
}

int CharaBase::getNowHp() {
	return this->_now_state[mainStateType::hp];
}

void CharaBase::setBeforeInsertDraw() {
	this->setDrawXToBeforeX();
	this->setDrawYToBeforeY();
}
void CharaBase::setDrawXToBeforeX() {
	this->_draw_x = this->_before_x;
}
void CharaBase::setDrawYToBeforeY() {
	this->_draw_y = this->_before_y;
}
void CharaBase::setDrawX(double set_x) {
	this->_draw_x = set_x;
}
void CharaBase::setDrawY(double set_y) {
	this->_draw_y = set_y;
}
double CharaBase::getBeforeX() {
	return this->_before_x;
}
double CharaBase::getBeforeY() {
	return this->_before_y;
}
int CharaBase::getMapBlockX() {
	return this->_map_block_x;
}
int CharaBase::getMapBlockY() {
	return this->_map_block_y;
}

// group data -----------------------------------------------
void CharaBase::setGroupList() {

}
std::list<charaGroupList> CharaBase::getMyGroupList() {
	return this->_my_group_list;
}
//-----------------------------------------------------------
// equip item
//-----------------------------------------------------------
void CharaBase::setEquipItem(equipType equip_type, EquipItem* item_obj, std::unordered_map<abnormalStateType, int> abnormal_state_list) {

	if (this->_equip_list[equip_type] == item_obj) {
		this->removeEquipItem(equip_type, item_obj, abnormal_state_list);
		return;
	}
	else if (this->_equip_list[equip_type] != nullptr) {
		
		this->removeEquipItem(equip_type, this->_equip_list[equip_type], this->_equip_list[equip_type]->getStateDefaultList());

	}
	// check sub weapon
	if (equip_type == equipType::weapon && this->_equip_list[equipType::sub_weapon] != nullptr) {
		if (this->_equip_list[equipType::sub_weapon]->checkEquipRelease() == true) {
			this->removeEquipItem(equipType::sub_weapon, this->_equip_list[equipType::sub_weapon], this->_equip_list[equipType::sub_weapon]->getStateDefaultList());
		}
	}

	this->_equip_list[equip_type] = item_obj;
	//Dictionary<mainStateType, int> item_state = item_obj.getItemState();
	std::unordered_map<mainStateType, int> item_state = item_obj->getItemState();

	for (int state_type = static_cast<int>(mainStateType::no_type) + 1; state_type < static_cast<int>(mainStateType::enum_end); state_type++) {
		this->_correction_state[static_cast<mainStateType>(state_type)] += item_state[static_cast<mainStateType>(state_type)];
		this->reColStatus(static_cast<mainStateType>(state_type));
	}
	/*
	foreach(mainStateType state_type in Enum.GetValues(typeof(mainStateType))) {
		this->_correction_state[state_type] += item_state[state_type];
		this->reColStatus(state_type);
	}
	// */
	// abnormal default check

	for (int state_type = static_cast<int>(abnormalStateType::no_type) + 1; state_type < static_cast<int>(abnormalStateType::enum_end); state_type++) {
		if (abnormal_state_list[static_cast<abnormalStateType>(state_type)] >= 1) {
			this->setEquipToAbnormalState(static_cast<abnormalStateType>(state_type), item_obj);
		}
	}
	/*
	foreach(abnormalStateType state_type in Enum.GetValues(typeof(abnormalStateType))) {
		if (abnormal_state_list[state_type] >= 1) {
			this->setEquipToAbnormalState(state_type, item_obj);
		}
	}
	// */

	return;
}
void CharaBase::removeEquipItem(equipType equip_type, EquipItem* item_obj, std::unordered_map<abnormalStateType, int> abnormal_state_list) {
	this->_equip_list[equip_type] = nullptr;

	std::unordered_map<mainStateType, int> item_state = item_obj->getItemState();

	for (int state_type = static_cast<int>(mainStateType::no_type) + 1; state_type < static_cast<int>(mainStateType::enum_end); state_type++) {
		this->_correction_state[static_cast<mainStateType>(state_type)] -= item_state[static_cast<mainStateType>(state_type)];
		this->reColStatus(static_cast<mainStateType>(state_type));
	}
	/*
	foreach(mainStateType state_type in Enum.GetValues(typeof(mainStateType))) {
		this->_correction_state[state_type] -= item_state[state_type];
		this->reColStatus(state_type);
	}
	//*/
	// abnormal default check
	for (int state_type = static_cast<int>(abnormalStateType::no_type) + 1; state_type < static_cast<int>(abnormalStateType::enum_end); state_type++) {
		if (abnormal_state_list[static_cast<abnormalStateType>(state_type)] >= 1) {
			this->removeEquipToAbnormalState(static_cast<abnormalStateType>(state_type), item_obj);
		}
	}
	/*
	foreach(abnormalStateType state_type in Enum.GetValues(typeof(abnormalStateType))) {
		if (abnormal_state_list[state_type] >= 1) {
			this->removeEquipToAbnormalState(state_type, item_obj);
		}
	}
	// */
}
void CharaBase::reColStatus(mainStateType state_type) {
	switch (state_type) {
	case mainStateType::hp:
	case mainStateType::sp:
	case mainStateType::honey:
	case mainStateType::excitation:
		this->_max_state[state_type] = this->_base_state[state_type] + this->_correction_state[state_type];
		break;
	default:
		this->_now_state[state_type] = this->_base_state[state_type] + this->_correction_state[state_type];
		break;
	}
	/*(state_type == mainStateType.hp) {
	this->_max_state[state_type] = this->_base_state[state_type] + this->_correction_state[state_type];
	} else {
	this->_now_state[state_type] = this->_base_state[state_type] + this->_correction_state[state_type];
	}
	*/
}

void CharaBase::setEquipToAbnormalState(abnormalStateType state_type, EquipItem* item_obj) {
	
	this->_state_list->setEquipItemToState(state_type, item_obj);
	this->_state_list->setState(state_type, 1);
}
void CharaBase::removeEquipToAbnormalState(abnormalStateType state_type, EquipItem* item_obj) {
	this->_state_list->removeEquipItemToState(state_type, item_obj);
}
// get set data etc -----------------------------------------
std::list<CharaBase*>* CharaBase::getAllCharaList() {
	return this->_all_chara_list;
}
StateList* CharaBase::getStateList() {
	return this->_state_list;
}
// set skill(use item to skill set ok)
bool CharaBase::setSkill(SkillBase* skill_obj) {

	if (this->checkSetSkill(skill_obj) != true) {
		return false;
	}
	//	Debug.WriteLine("[charaBase]set skill 0");
	/*
	if (this->checkSpellFlag() == true) {
	return false;
	}
	*/

	if (skill_obj->checkExtendSkillUse() != true) {
		return false;
	}
	int use_sp = skill_obj->getUseSp();
	//	Debug.WriteLine("[charaBase]set skill 1");
	//sp check
	if (use_sp > 0) {
		if (this->checkSp(use_sp) != true) {
			return false;
		}
		this->useSp(use_sp);
	}

	if (skill_obj->getChainCountFlag() == true) {
		this->_skill_chain_num++;
	}


	this->removeSkill();
	skill_obj->skillInit();

	this->_set_now_skill = skill_obj;

	// @TODO
//	bool skill_set_flag = this->_skill_list->setSkillData(skill_obj, this->checkGroundFlag());
	bool skill_set_flag = true;
	// スキルが発動できる場合
	if (skill_set_flag == true) {

		// ターゲットの方向を向く
		double get_move_angle = this->getTargetAngleSkill();

		if (get_move_angle > -360 && get_move_angle < 720) {
			this->_move_angle = get_move_angle;
		}
	}
	return skill_set_flag;
}
bool CharaBase::checkSetSkill(SkillBase* skill_obj) {

	//	Debug.WriteLine("[charaBase]check set skill 0");
	//	スキル発動可能状態かチェック

	if (this->checkAttackFlag() != true) {
		return false;
	}
	//	Debug.WriteLine("[charaBase]check set skill 1");
	// 武器装備タイプチェック
	if (skill_obj->checkWeaponType() != true) {
		return false;
	}
	//	Debug.WriteLine("[charaBase]check set skill 2");
	// 詠唱状態かどうかチェック
	if (this->checkSpellFlag() == true) {
		return false;
	}
	//	Debug.WriteLine("[charaBase]check set skill 3");
	// 空中発動不可能、なおかつキャラクターが地上判定じゃない場合
	if (skill_obj->getInAirFlag() != true && this->checkGroundFlag() != true) {
		return false;
	}
	//	Debug.WriteLine("[charaBase]check set skill 4");
	//			if (this->_in_air_flag == true || use_chara_obj.checkGroundFlag() == true) {

	// 消費SPチェック
	int use_sp = skill_obj->getUseSp();
	//sp check
	if (use_sp > 0) {
		if (this->checkSp(use_sp) != true) {
			return false;
		}
	}
	//	Debug.WriteLine("[charaBase]check set skill 5");
	return true;
}
// action function ------------------------------------------
void CharaBase::countActionFrame() {

	if (this->_no_control_frame > 0) {
		this->_no_control_frame--;
	}
	if (this->_attack_frame > 0) {
		this->_attack_frame--;
	}
	if (this->_skill_frame > 0) {
		this->_skill_frame--;
	}
	if (this->_super_armour_frame > 0) {
		this->_super_armour_frame--;
	}

}
//-----------------------------------------------------------
// skill check
// trueでスキルのキャンセル可能タイミングになる（移動等の行動は不可能
//-----------------------------------------------------------
bool CharaBase::checkAttackFlag() {


	if (this->_skill_frame > 0 || this->_no_control_frame > 0) {
		return false;
	}


	return true;
}
//-----------------------------------------------------------
// Action　check
// trueですべての行動が可能になる
//-----------------------------------------------------------
bool CharaBase::checkActionFlag() {
	if (this->_attack_frame > 0 || this->_no_control_frame > 0) {
		return false;
	}
	return true;
}
//-----------------------------------------------------------
// 詠唱中かどうかのフラグ
// 上記のチェックとは違い、trueで詠唱中判定
//-----------------------------------------------------------
bool CharaBase::checkSpellFlag() {
	if (this->_spell_status != 0) {
		return true;
	}
	return false;
}
// sp -------------------------------------------------------
void CharaBase::useSp(int use_sp) {
	this->_now_state[mainStateType::sp] -= use_sp;
}
bool CharaBase::checkSp(int check_sp) {
	//	Debug.WriteLine("[charaBase]check sp:"+check_sp+"/"+this->_now_state[mainStateType.sp]);

	if (this->_now_state[mainStateType::sp] >= check_sp) {
		return true;
	}
	return false;
}
// damage ---------------------------------------------------
void CharaBase::slipDamageHp(int damage) {
	this->_now_state[mainStateType::hp] -= damage;

	if (this->_now_state[mainStateType::hp] < 0) {
		this->_now_state[mainStateType::hp] = 0;
	}
}
void CharaBase::directDamageHp(int damage) {

	this->_now_state[mainStateType::hp] -= damage;

	this->resetRevivalFrame();
	this->damageAction();

	this->checkRemoveSkill();
	if (this->_now_state[mainStateType::hp] < 0) {
		this->_now_state[mainStateType::hp] = 0;
	}
}
void CharaBase::normalDamageHp(int attack_damage) {

	int damage = attack_damage - 10;
	if (damage < 100) {
		damage = 100;
	}

	this->_now_state[mainStateType::hp] -= damage;

	this->resetRevivalFrame();
	this->damageAction();

	if (this->_now_state[mainStateType::hp] < 0) {
		this->_now_state[mainStateType::hp] = 0;
	}
}
void CharaBase::checkToSetState(abnormalStateType state_type, int state_level, int state_rate) {
	bool state_flag = this->_state_list->checkToSetState(abnormalStateType::poison, state_level, state_rate);

	if (state_flag == true) {
		//this->sendComment("毒なう");
	}
}

void CharaBase::damageAction() {
	this->_no_control_frame = 60;
}
//-----------------------------------------------------------
//	ダメージ等によるスキル行動キャンセルチェック
//-----------------------------------------------------------
void CharaBase::checkRemoveSkill(){
	this->removeSkill();
}
//-----------------------------------------------------------
//	スキル行動キャンセル
//-----------------------------------------------------------
void CharaBase::removeSkill(){

	/*
	if (this->_set_attack_skill != nullptr ) {
		this->_skill_list->removeSkillList(this->_set_attack_skill);
		this->_set_attack_skill->setDeleteFlag();
	}
	if (this->_set_now_skill != nullptr ) {
		this->_skill_list->removeSkillList(this->_set_now_skill);
		this->_set_now_skill->setDeleteFlag();
	}

	this->setAttackFrame(0);
	this->setSkillFrame(0);
	*/
}
// sexual damage ----------------------------------
void CharaBase::normalDamageSexual(int damage, double direct_rate, bool action_flag, charaCommentType comment_type) {

	// 絶頂中はダメージ受けない
	if (this->_state_list->getStateEndFlag(abnormalStateType::extasy) == false) {
		return;
	}

	this->honeyOnlyDamage(damage, action_flag);

	//		int excitation_damage = 0;

	if (this->_now_state[mainStateType::honey] >= this->_max_state[mainStateType::honey]) {

		this->_now_state[mainStateType::excitation] += damage;
	}
	else {
		// 興奮MAXじゃない場合は快楽に下方補正をかける
		double rate = ((double)this->_now_state[mainStateType::honey] / (double)this->_max_state[mainStateType::honey]);
		this->_now_state[mainStateType::excitation] += (int)((double)damage * rate * direct_rate);
	}

	if (this->_now_state[mainStateType::excitation] > this->_max_state[mainStateType::excitation]) {
		this->_now_state[mainStateType::excitation] = (int)((double)this->_max_state[mainStateType::excitation]);

		// 絶頂ステータスを付与する
		if (this->_state_list->getStateEndFlag(abnormalStateType::extasy)) {
			this->_state_list->setState(abnormalStateType::extasy, 1);
			this->_sexual_state = charaSexualState::extasy;
			this->sendSexualComment();
		}


		// HPを0にする
		this->_now_state[mainStateType::hp] = 0;
	}
}
void CharaBase::honeyOnlyDamage(int damage, bool action_flag) {

	// 絶頂中はダメージ受けない
	if (this->_state_list->getStateEndFlag(abnormalStateType::extasy) == false) {
		return;
	}
	this->sendTypeComment(charaCommentType::pleasure, charaSexualType::normal);
	this->_now_state[mainStateType::honey] += damage;
	this->resetRevivalFrame();
	if (action_flag == true) {
		this->damageAction();
	}

	if (this->_now_state[mainStateType::honey] >= this->_max_state[mainStateType::honey]) {
		this->_now_state[mainStateType::honey] = this->_max_state[mainStateType::honey];


		// 興奮MAX+発情じゃない＝発情した瞬間
		if (this->_state_list->getStateEndFlag(abnormalStateType::oestrus)) {
			//this->sendComment(this->_comment_list.getComment(charaCommentType.honey_start, charaSexualType.normal));
			if (this->now_hot_to_oestrus_flag == false) {
				this->sendTypeCommentDirect(charaCommentType::oestrus_start, charaSexualType::normal);
				this->now_hot_to_oestrus_flag = true;
			}
			this->_sexual_state = charaSexualState::oestrus;

			//this->sendTypeComment(charaCommentType.honey_start, charaSexualType.normal);
			this->_state_list->setState(abnormalStateType::oestrus, 1);
		}
	}
}
void CharaBase::setExtasy() {
	this->_now_state[mainStateType::honey] = 0;
	this->_now_state[mainStateType::excitation] = 0;
}
void CharaBase::resetRevivalFrame() {
	this->_revival_frame = this->_REVIVAL_TIME + 1;

	this->_sexual_repair_frame = this->_SEXUAL_SET_FRAME;
}
// sexual etc -----------------------------------------------
charaSexualType CharaBase::getSexualType() {
	return this->_sexual_type;
}
// heal -----------------------------------------------------
void CharaBase::healHp(int heal_num) {
	this->_now_state[mainStateType::hp] += heal_num;
	if (this->_now_state[mainStateType::hp] >= this->_max_state[mainStateType::hp]) {
		this->_now_state[mainStateType::hp] = this->_max_state[mainStateType::hp];
	}
}

void CharaBase::autoHealSexual() {

	if (this->_sexual_repair_frame > 0) {
		this->_sexual_repair_frame--;
		return;
	}
	

	if (this->_now_state[mainStateType::honey] > 0) {
		this->_now_state[mainStateType::honey] -= this->_AUTO_HEAL_HONEY;
		if (this->_now_state[mainStateType::honey] < 0) {
			this->_now_state[mainStateType::honey] = 0;
		}
	}

	if (this->_now_state[mainStateType::excitation] > 0) {
		this->_now_state[mainStateType::excitation] -= this->_AUTO_HEAL_EXCITATION;
		if (this->_now_state[mainStateType::excitation] < 0) {
			this->_now_state[mainStateType::excitation] = 0;
		}
	}

}
// test only ------------------------------------------------
void CharaBase::setWeaponTestIndex(int index) {
	this->_test_weapon_index = index;
}

// send comment (use to player only -------------------------
void CharaBase::sendComment(std::string comment) {
}
void CharaBase::sendTypeComment(charaCommentType comment_type, charaSexualType chara_type) {
}
void CharaBase::sendTypeCommentDirect(charaCommentType comment_type, charaSexualType chara_type) {
}
void CharaBase::sendSexualComment() {
}

// set magic list
void CharaBase::setMagicList(MagicBase* magic_obj) {
	//this->_magic_list.Add(magic_obj);
	this->_magic_list->push_back(magic_obj);
}
// set magic list
void CharaBase::setShadowList(MagicBase* magic_obj) {

	this->_shadow_list->setRenderObject((RenderObject*)magic_obj);
}
GameCamera* CharaBase::getGameCamera() {
	return this->_play_camera;
}

// equip data -----------------------------------------------
weaponType CharaBase::getMainWeaponType() {
	if (this->_equip_list[equipType::weapon] == nullptr) {
		return weaponType::no_weapon;
	}

	WeaponBase* weapon_obj = (WeaponBase*)this->_equip_list[equipType::weapon];
	return weapon_obj->getWeaponType();
}
weaponType CharaBase::getSubWeaponType() {
	//Debug.WriteLine("[CharaBase]getSubWeaponType check");
	if (this->_equip_list[equipType::sub_weapon] == nullptr) {
		return weaponType::no_weapon;
	}

	WeaponBase* weapon_obj = (WeaponBase*)this->_equip_list[equipType::sub_weapon];

	return weapon_obj->getWeaponType();
}
//-----------------------------------------------------------
// 剣+鞘などで使う武器状態を取得
//-----------------------------------------------------------
int CharaBase::getWeaponState() {
	return this->_weapon_state;
}
void CharaBase::setWeaponState(int weapon_state) {
	this->_weapon_state = weapon_state;
}

EquipItem* CharaBase::getEquipItemObj(equipType equip_type) {
	return this->_equip_list[equip_type];
}
// magic ----------------------------------------------------
double CharaBase::getSpellPointX() {
	return this->_spell_point_x;
}
double CharaBase::getSpellPointY() {
	return this->_spell_point_y;
}
// push -----------------------------------------------------
void CharaBase::setDamagePush(double push_speed, double push_angle, int push_frame) {
	this->_push_speed = push_speed;
	this->_push_angle = push_angle;
	this->_push_frame = push_frame;
	this->_no_control_frame = push_frame;
	/*
	protected int _push_frame = 0;			// 吹き飛ばし時間
	protected double _push_angle = 0;		// 吹き飛ばし方向
	protected double _push_speed = 0;		// 吹き飛ばし速度
	*/

}
void CharaBase::updateDamagePush() {
	if (this->_push_frame <= 0 && this->_draw_z <= 0) {
		this->_push_speed = 0;
		this->_push_angle = 0;
		return;
	}

	this->_move_x = (double)(cos(this->_push_angle * M_PI / 180) * this->_push_speed);
	this->_move_y = (double)(sin(this->_push_angle * M_PI / 180) * this->_push_speed);

	if (this->_move_x < 0.00001f && this->_move_x > -0.00001f) {
		this->_move_x = 0;
	}
	if (this->_move_y < 0.00001f && this->_move_y > -0.00001f) {
		this->_move_y = 0;
	}
	this->_draw_x += this->_move_x;
	this->_draw_y += this->_move_y;

	this->_push_frame--;

}

// battle target --------------------------------------------
void CharaBase::setTargetChara(CharaBase* set_target_chara_obj) {
	if (this->_skill_target_obj == nullptr) {
		this->_skill_target_obj = set_target_chara_obj;
	}
}
//-----------------------------------------------------------
//	ターゲットの方向を取得する
//-----------------------------------------------------------
double CharaBase::getTargetAngleSkill() {
	if (this->_skill_target_obj == nullptr) {
		return -1000;
	}
	double target_angle = this->getTargetAngle(
		this->_draw_x,
		this->_draw_y,
		this->_skill_target_obj->getDrawX(),
		this->_skill_target_obj->getDrawY()
		);
	//		this->getMoveAnagleDirection();
	return target_angle;

}
void CharaBase::resetTargetChara() {
	if (this->_skill_target_obj != nullptr) {
		this->_skill_target_obj = nullptr;
	}
}
//-----------------------------------------------------------
//	2点の方向を取得する
//-----------------------------------------------------------
double CharaBase::getTargetAngle(double x1, double y1, double x2, double y2) {

	double mx = x1 - x2;
	double my = y1 - y2;

	double degree;

	if (mx == 0 && my == 0) {
		degree = 0;
	}
	else {
		//degree = System.Math.Atan2(my, mx) * (180 / System.Math.PI);
		degree = atan2(my, mx) * (180 / M_PI);
	}
	return degree + 180;
}
void CharaBase::setCharaMapPoint(double point_x, double point_y) {

	this->setDrawX(point_x);
	this->setDrawY(point_y);
	this->updateBlockPoint();
	
}