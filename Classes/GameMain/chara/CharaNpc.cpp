#include "CharaNpc.h"

#include "chara_seed/test_puppet/SeedTestPuppet.h"
#include "chara_seed/human/SeedHuman.h"
#include "chara_seed/SeedBase.h"
#include "../GameCamera.h"

#include "../skill/SkillBase.h"
#include "../skill/weapon_skill/no_weapon/NoWeaponDefault.h"
#include "abnormal_state\StateList.h"
#include "../magic/MagicBase.h"
#include "../shadow/ShadowObjectList.h"

CharaNpc::CharaNpc(int set_x, int set_y, GameCamera* camera_obj, std::list<CharaBase*> *all_chara_list, std::list<MagicBase*> magic_list, ShadowObjectList* shadow_list)
{
//	this->_skill_list = skill_list;
	this->_all_chara_list = all_chara_list;
	this->_magic_list = magic_list;
	this->_shadow_list = shadow_list;

	//this->_state_list = new StateList(this);
	this->_play_camera = camera_obj;

	this->_draw_x = set_x;
	this->_draw_y = set_y;

	this->_restart_x = set_x;
	this->_restart_y = set_y;

//	this->_chara_seed = new SeedHuman();
	this->_chara_seed = new SeedTestPuppet();
	//this->_chara_seed = new SeedTentacle();


	this->addChild(this->_chara_seed);

	this->setState();// set seed after

	this->_state_list = this->_chara_seed->getStateList(this);
	// add group data
	this->_fellow_group_list = this->_chara_seed->getFellowGroupList();
	this->_fellow_group_list.push_back(charaGroupList::game_master);


	int seed_correct_x = this->_chara_seed->getCorrectX();
	this->_draw_correct_x = (int)((float)seed_correct_x * this->_chara_seed->getScalePer());

	// 初期表示
	this->setPosition((int)(this->_draw_x), (int)(this->_draw_y + this->_draw_z));
//	this->setPosition((int)(this->_draw_x - this->_play_camera->getCameraX()), (int)(this->_draw_y - this->_play_camera->getCameraY() + this->_draw_z));


	this->SetCharaHitData();
	this->updateDraw();
/*
	var texture_info = Director.Instance.GL.WhiteTextureInfo;

	var sprite = new SpriteUV(){ TextureInfo = texture_info };

	
	sprite.Position = new Vector2(0, 0);

	sprite.Scale = new Vector2(2, 2);
	sprite.Color = new Vector4(0.0f, 0.2f, 1.0f, 1.0f);
	sprite.BlendMode = BlendMode.Normal;
	this->AddChild(sprite);


	this->SetCharaHitData();

	// test vision view 
	var vision_texture_info = Director.Instance.GL.WhiteTextureInfo;
	this->_test_vision_angle_0 = new SpriteUV(){ TextureInfo = vision_texture_info };
	this->_test_vision_angle_1 = new SpriteUV(){ TextureInfo = vision_texture_info };
	this->_test_vision_angle_2 = new SpriteUV(){ TextureInfo = vision_texture_info };
	var range = new Vector2((float)this->_chara_seed.getVisionRange(), 1);
	this->_test_vision_angle_0.Scale = range;
	this->_test_vision_angle_1.Scale = range;
	this->_test_vision_angle_2.Scale = range;

	this->_test_vision_angle_0.Angle = 3.14f * (float)((this->_move_angle_direction) / 180.0f);
	this->_test_vision_angle_1.Angle = 3.14f * (float)((this->_move_angle_direction - this->_chara_seed.getVisionAngle()) / 180.0f);
	this->_test_vision_angle_2.Angle = 3.14f * (float)((this->_move_angle_direction + this->_chara_seed.getVisionAngle()) / 180.0f);
	this->_test_vision_angle_0.Color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	this->_test_vision_angle_1.Color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	this->_test_vision_angle_2.Color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	this->AddChild(this->_test_vision_angle_0);
	this->AddChild(this->_test_vision_angle_1);
	this->AddChild(this->_test_vision_angle_2);
	//*/
}
// group data -----------------------------------------------
void CharaNpc::setGroupList() {
	this->_my_group_list = this->_chara_seed->getMyGroupList();
	this->_fellow_group_list = this->_chara_seed->getFellowGroupList();
	this->_target_group_list = this->_chara_seed->getTargetGroupList();
}
// update ---------------------------------------------------
void CharaNpc::mainUpdate() {

	this->npcAi();


	// test vision view
	/*
	this->_test_vision_angle_0.Angle = 3.14f * (float)((this->_move_angle_direction) / 180.0f);
	this->_test_vision_angle_1.Angle = 3.14f * (float)((this->_move_angle_direction - this->_chara_seed.getVisionAngle()) / 180.0f);//(float)(this->_move_angle_direction - this->_chara_seed.getVisionAngle());
	this->_test_vision_angle_2.Angle = 3.14f * (float)((this->_move_angle_direction + this->_chara_seed.getVisionAngle()) / 180.0f);//(float)(this->_move_angle_direction + this->_chara_seed.getVisionAngle());
	*/

}
void CharaNpc::charaDownMomentDetail() {
	this->removeChild(this->_chara_seed, false);
}
void CharaNpc::charaRevival() {
	this->_draw_x = this->_restart_x;
	this->_draw_y = this->_restart_y;

	this->_ai_base_count = this->_AI_SET_COUNT;
	this->_ai_set_action = aiAction::stand;

	this->_now_state[mainStateType::hp] = this->_max_state[mainStateType::hp];
	this->_down_flag = false;
	this->now_hot_to_oestrus_flag = false;

	this->_target_enemy_chara = nullptr;
	this->_set_attack_skill = nullptr;
	this->addChild(this->_chara_seed);
}
void CharaNpc::setCharaMapPoint(double point_x, double point_y) {

	CharaBase::setCharaMapPoint(point_x, point_y);
	this->_restart_x = point_x;
	this->_restart_y = point_y;
}
// npc ai base ----------------------------------------------
void CharaNpc::npcAi() {
	if (this->_down_flag == true || this->_no_control_frame > 0) {
		return;
	}

	// 戦闘状態
	if (this->_ai_set_action == aiAction::battle) {
		this->battleAi();
	}
	// 移動可能状態
	if (this->_attack_frame <= 0 && this->_skill_frame <= 0) {
		this->searchEnemyChara();
	}

	// 戦闘状態ではない場合
	if (this->_ai_set_action != aiAction::battle) {
		this->_move_speed_per = 0;
		if (this->_ai_base_count <= 0 && this->_ai_set_action != aiAction::battle) {
			// 行動変更
			// 立ちだった場合、歩きへ

			int random_num = 1;
			switch (this->_ai_set_action) {
			case aiAction::stand:
				this->_ai_set_action = aiAction::move;

				
				this->updateMoveAngle(random_num);

				break;
			case aiAction::move:
				this->_ai_set_action = aiAction::stand;
				break;
			}

			this->_ai_base_count += this->_AI_SET_COUNT;
		}

		switch (this->_ai_set_action) {
		case aiAction::stand:
			this->searchEnemyChara();
			break;
		case aiAction::move:
			this->_move_speed_per = 1;
			this->searchEnemyChara();
			this->updateMove(this->getWalkSpeed());
			break;

		}

		this->_ai_base_count--;
	}
	/*
	if (this->_no_control_frame > 0 || this->_attack_frame > 0 //|| this->_skill_frame > 0 ||
	) {
	return;
	}


	/*
	this->_move_speed_per = 0;
	if (this->_ai_base_count <= 0 && this->_ai_set_action != (int)aiAction.battle) {
	// 行動変更

	// 立ちだった場合、歩きへ
	switch (this->_ai_set_action) {
	case (int)aiAction.stand:
	this->_ai_set_action = (int)aiAction.move;
	Random rnd = new Random();
	int random_num = rnd.Next(360);
	this->updateMoveAngle(random_num);
	break;
	case (int)aiAction.move:
	this->_ai_set_action = (int)aiAction.stand;
	break;
	}

	this->_ai_base_count += this->_AI_SET_COUNT;
	}

	switch (this->_ai_set_action) {
	case (int)aiAction.stand:
	this->searchEnemyChara();
	break;
	case (int)aiAction.move:
	this->_move_speed_per = 1;
	this->searchEnemyChara();
	this->updateMove(this->getWalkSpeed());
	break;
	case (int)aiAction.battle:
	this->battleAi();
	break;
	}

	this->_ai_base_count--;
	*/
}
void CharaNpc::searchEnemyChara() {

	if (this->_target_enemy_chara == nullptr) {

		for (CharaBase* search_chara : *this->_all_chara_list) {


			if (search_chara == this) {
				continue;
			}
			std::list<charaGroupList> search_chara_group = search_chara->getMyGroupList();

			/*
			//bool target_flag = false;
			foreach(charaGroupList group_name in search_chara_group) {
				if (this->_target_group_list.Contains(group_name)) {
					double range = this->getTargetRange(
						this->_draw_x,
						this->_draw_y,
						search_chara.getDrawX(),
						search_chara.getDrawY()
						);
					double target_angle = this->getTargetAngle(
						this->_draw_x,
						this->_draw_y,
						search_chara.getDrawX(),
						search_chara.getDrawY()
						);
					double chara_angle = this->_move_angle_direction;
					//(this->_move_angle_direction - this->_chara_seed.getVisionAngle())
					double target_angle_min = chara_angle - this->_chara_seed.getVisionAngle();
					double target_angle_max = chara_angle + this->_chara_seed.getVisionAngle();

					// check angle 
					bool angle_check_flag = false;
					double max_angle = 360;

					if (target_angle >= target_angle_min &&
						target_angle <= target_angle_max) {
						angle_check_flag = true;
					}
					if (angle_check_flag == false && target_angle_min < 0) {
						if (target_angle >= target_angle_min + max_angle) {
							angle_check_flag = true;
						}
					}

					if (angle_check_flag == false && target_angle_max >= max_angle) {
						if (target_angle <= target_angle_max - max_angle) {
							angle_check_flag = true;
						}
					}

					if (
						(float)range >= 0 &&
						(float)range <= this->_chara_seed.getVisionRange() &&
						angle_check_flag == true) {

						this->_target_enemy_chara = search_chara;
						this->_ai_set_action = aiAction.battle;
						return;

					}
				}
			}
			*/


		}
	}
}
double CharaNpc::getTargetRange(double x1, double y1, double x2, double y2){

	double dx = pow(x1 - x2, 2);
	double dy = pow(y1 - y2, 2);
	double distance = sqrt(dx + dy);

	return distance;
}
void CharaNpc::battleAi() {
	int ai_count_max = 220;

	// 攻撃終了直後の場合、スキルを破棄
	if (this->_set_attack_skill != nullptr &&
		this->checkAttackFlag() == true && this->_before_skill_flag == false) {
		this->_set_attack_skill = nullptr;
	}

	// 何もスキルをセットしていない場合、スキルを準備する
	if (this->_set_attack_skill == nullptr) {
		this->_set_attack_skill = new NoWeaponDefault(this, this->_all_chara_list);
	}

	this->_move_speed_per = 1;

	// ターゲットとの角度と距離を取得
	double target_angle = this->getTargetAngle(
		this->_draw_x,
		this->_draw_y,
		this->_target_enemy_chara->getDrawX(),
		this->_target_enemy_chara->getDrawY()
		);
	double target_range = this->getTargetRange(
		this->_draw_x,
		this->_draw_y,
		this->_target_enemy_chara->getDrawX(),
		this->_target_enemy_chara->getDrawY()
		);
	// 指定範囲外の場合、行動を通常時へ移行
	if (target_range >= this->_chara_seed->getUnvisionRange()) {
		this->_target_enemy_chara = nullptr;
		this->_ai_set_action = aiAction::stand;
		this->_ai_base_count = ai_count_max;
		return;
	}
	else {

		double skill_use_range = -1;

		// スキルセット中 + 攻撃可能の場合
		if (this->_set_attack_skill != nullptr && this->checkAttackFlag() == true) {
			skill_use_range = this->_set_attack_skill->getNpcUseRange();

			// ターゲットとの距離がNPCのスキル発動範囲内の場合
			if (target_range <= skill_use_range) {
				// 攻撃をセット

				// test to comment
				//						bool attack_flag = this->setSkill(this->_set_attack_skill);
			}
		}
	}

	this->updateMoveAngle(target_angle);
	this->updateMove(this->getRunSpeed());

	// 次フレームにて、スキル再使用可能直後を判定するために、現在フレームのアタックチェックを保持
	this->_before_skill_flag = this->checkAttackFlag();

	// old AI -----------------------------------------------
	/*
	if (this->_set_attack_skill == null && this->_down_flag == false && this->checkAttackFlag() == true) {
	//this->_set_attack_skill = new TentacleDefault(this, this->_all_chara_list);
	this->_set_attack_skill = new NoWeaponDefault(this, this->_all_chara_list);
	//				Debug.WriteLine("new skill insert");
	}

	this->_move_speed_per = 1;
	double target_angle = this->getTargetAngle(
	this->_draw_x,
	this->_draw_y,
	this->_target_enemy_chara._draw_x,
	this->_target_enemy_chara._draw_y
	);
	double target_range = this->getTargetRange(
	this->_draw_x,
	this->_draw_y,
	this->_target_enemy_chara._draw_x,
	this->_target_enemy_chara._draw_y
	);
	if (target_range >= this->_chara_seed.getUnvisionRange()) {
	this->_target_enemy_chara = null;
	this->_ai_set_action = (int)aiAction.stand;
	this->_ai_base_count = ai_count_max;
	return;
	}


	double skill_use_range = -1;
	if (this->_set_attack_skill != null && this->checkAttackFlag() == true) {
	skill_use_range = this->_set_attack_skill.getNpcUseRange();

	if (target_range <= skill_use_range) {

	bool attack_flag = this->setSkill(this->_set_attack_skill);

	if (attack_flag == true) {
	//						Debug.WriteLine("next skill");
	this->_set_attack_skill = null;
	}

	}
	}




	this->updateMoveAngle(target_angle);

	this->updateMove(this->getRunSpeed());
	*/


}