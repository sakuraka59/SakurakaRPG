#include "CharaPlayer.h"
#include "..\..\RenderObject.h"

#include "..\GameCamera.h"

#include "abnormal_state\StateList.h"
#include "charaGroupList.h"
#include "chara_seed\human\SeedHuman.h"

#include "../../Input/Gamepad.h"

CharaPlayer::CharaPlayer(GameCamera* camera, PlayerCommentUI* comment_ui_obj, std::list<CharaBase*> all_chara_list, SkillList* skill_list, std::list<MagicBase*> magic_list, ShadowObjectList* shadow_list)
{
	//this->_skill_list = skill_list;
	this->_all_chara_list = all_chara_list;
	this->_magic_list = magic_list;
	this->_shadow_list = shadow_list;
	this->_state_list = new StateList(this);
	this->_play_camera = camera;

	
	// グループリストに操作キャラクターを追加する
	this->_my_group_list.push_back(charaGroupList::player);

	this->_chara_seed = new SeedHuman();

	this->addChild(this->_chara_seed);

	this->_comment_ui_obj = comment_ui_obj;
	this->setState();// set seed after

//	
	
	int seed_correct_x = this->_chara_seed->getCorrectX();
	this->_draw_correct_x = (int)((float)seed_correct_x * this->_chara_seed->getScalePer());

	this->_now_state[mainStateType::hp] = 1000;

	// 初期座標。オブジェクトとかぶると0,0へ強制移動するので注意
	this->_draw_x = -64;//1280 / 2;
	this->_draw_y = -64 * 10;// -1280 / 2;//300;
	this->updateBlockPoint();
	this->SetCharaHitData();

	// test 
	this->updateDraw();

	// */


	// 初期表示
	//this->Position = new Vector2((int)(this->_draw_x), (int)(this->_draw_y - this->_play_camera._y));
	//	this->Position = new Vector2((int)(this->_draw_x - this->_play_camera.getCameraX()), (int)(this->_draw_y - this->_play_camera.getCameraY() + this->_draw_z));

	//*


	// 描画範囲のテスト表示
	// base point

	/*
	var texture_info = Director.Instance.GL.WhiteTextureInfo;

	var sprite = new SpriteUV(){ TextureInfo = texture_info };


	sprite.Position = new Vector2((float)this->_draw_x / 2, 0);
	*/
	/*
	sprite.Scale = new Vector2(3,3);
	sprite.Color = new Vector4(1.0f, 0.2f, 1.0f, 1.0f);
	sprite.BlendMode = BlendMode.Normal;
	this->AddChild(sprite);
	*/
	/*
	this->_now_state[mainStateType::hp] = 1000;

	// 初期座標。オブジェクトとかぶると0,0へ強制移動するので注意
	this->_draw_x = 500;
	this->_draw_y = -544 / 2;//300;
	this->updateBlockPoint();
	this->SetCharaHitData();
	//this->directDamageHp(11);
	*/
	//this->RemoveChild(this->_test_label, true);

}
// update ---------------------------------------------------
void CharaPlayer::mainUpdate() {

	//this->_game_pad_data = GamePad.GetData(0);
	// 操作によるキャラクター移動
	// 操作によるキャラクター移動
	if (this->_down_flag == false) {
		this->moveCharaPlusKey();
	}


	// テスト用コメント投稿
	this->testComment();

	this->testState();
	this->testAction();



	if (this->_comment_delay_count > 0) {
		this->_comment_delay_count--;
	}


}
void CharaPlayer::updateCamera() {
	// カメラ処理はキャラクターが動き終わった後にやること！
	this->_play_camera->updateCharaPoint(this->getDrawX(), this->getDrawY());

}
void CharaPlayer::charaDownMomentDetail() {
	//TODO
//	this->sendComment(this->_comment_list->getComment(charaCommentType.down, charaSexualType.normal));
}
void CharaPlayer::charaRevival() {

	this->_now_state[mainStateType::hp] = 100;//(int)(this->_max_state[mainStateType.hp]/2);
	this->_down_flag = false;

	//TODO
//	this->sendComment(this->_comment_list.getComment(charaCommentType.normal_revival, charaSexualType.normal));
	this->now_hot_to_oestrus_flag = false;
}
void CharaPlayer::damageAction() {
	this->_play_camera->setCameraShake();
	this->damageAction();

	if (this->_down_flag == false) {

	}
	else {

	}
}
// controll -------------------------------------------------

//-------------------------------------------------
// 十字キーによるキャラクター移動
//-------------------------------------------------
void CharaPlayer::moveCharaPlusKey() {
	this->_move_speed_per = 0;
	if ((this->_no_control_frame <= 0 && this->_attack_frame <= 0 && this->_skill_frame <= 0) || this->checkSpellFlag() == true) {

		// 移動方向、移動距離を取得
		this->_move_speed_per = 1;

		if (this->_control_flag == true && Gamepad::Right->isPress() == true && Gamepad::Up->isPress() == true) {
			this->updateMoveAngle(45);
		}
		else if (this->_control_flag == true && Gamepad::Right->isPress() == true && Gamepad::Down->isPress() == true) {
			this->updateMoveAngle(315);
		}
		else if (this->_control_flag == true && Gamepad::Left->isPress() == true && Gamepad::Down->isPress() == true) {
			this->updateMoveAngle(225);
		}
		else if (this->_control_flag == true && Gamepad::Left->isPress() == true && Gamepad::Up->isPress() == true) {
			this->updateMoveAngle(135);
		}
		else if (this->_control_flag == true && Gamepad::Left->isPress() == true) {
			//			if((this->_game_pad_data.Buttons & GamePadButtons.Left) != 0) {
			this->updateMoveAngle(180);
		}
		else if (this->_control_flag == true && Gamepad::Right->isPress() == true) {
			//if ((this->_game_pad_data.Buttons & GamePadButtons.Right) != 0) {
			this->updateMoveAngle(0);
		}
		else if (this->_control_flag == true && Gamepad::Up->isPress() == true) {
			//if ((this->_game_pad_data.Buttons & GamePadButtons.Up) != 0) {
			this->updateMoveAngle(90);
		}
		else if (this->_control_flag == true && Gamepad::Down->isPress() == true) {
			//if ((this->_game_pad_data.Buttons & GamePadButtons.Down) != 0) {
			this->updateMoveAngle(270);

		}
		else {

			this->_move_speed_per = 0;
		}
		/*
		if (this->_control_flag == true && Input2.GamePad0.Right.Down == true && Input2.GamePad0.Up.Down == true) {
			this->updateMoveAngle(45);
		}
		else if (this->_control_flag == true && Input2.GamePad0.Right.Down == true && Input2.GamePad0.Down.Down == true) {
			this->updateMoveAngle(315);
		}
		else if (this->_control_flag == true && Input2.GamePad0.Left.Down == true && Input2.GamePad0.Down.Down == true) {
			this->updateMoveAngle(225);
		}
		else if (this->_control_flag == true && Input2.GamePad0.Left.Down == true && Input2.GamePad0.Up.Down == true) {
			this->updateMoveAngle(135);
		}
		else if (this->_control_flag == true && Input2.GamePad0.Left.Down == true) {
			//			if((this->_game_pad_data.Buttons & GamePadButtons.Left) != 0) {
			this->updateMoveAngle(180);
		}
		else if (this->_control_flag == true && Input2.GamePad0.Right.Down == true) {
			//if ((this->_game_pad_data.Buttons & GamePadButtons.Right) != 0) {
			this->updateMoveAngle(0);
		}
		else if (this->_control_flag == true && Input2.GamePad0.Up.Down == true) {
			//if ((this->_game_pad_data.Buttons & GamePadButtons.Up) != 0) {
			this->updateMoveAngle(90);
		}
		else if (this->_control_flag == true && Input2.GamePad0.Down.Down == true) {
			//if ((this->_game_pad_data.Buttons & GamePadButtons.Down) != 0) {
			this->updateMoveAngle(270);

		} else {

			this->_move_speed_per = 0;
		}
		*/

		// 移動処理
		if (this->_move_speed_per > 0) {

			this->updateMove(this->getRunSpeed());

		}
	}
	//this->updateCameraMove();


}

void CharaPlayer::sendComment(std::string comment) {

	if (this->_comment_delay_count <= 0) {
		//@TODO
		//this->_comment_ui_obj.setComment(comment, 0);
		this->_comment_delay_count = 0;
	}
}
void CharaPlayer::sendDirectComment(std::string comment) {
	//@TODO
	//this->_comment_ui_obj.setComment(comment, 0);
	this->_comment_delay_count = 10;
}
void CharaPlayer::sendTypeComment(charaCommentType comment_type, charaSexualType chara_type) {
	//@TODO
	//this->sendComment(this->_comment_list.getComment(comment_type, chara_type));

}
void CharaPlayer::sendTypeCommentDirect(charaCommentType comment_type, charaSexualType chara_type) {
	//@TODO
	//this->sendDirectComment(this->_comment_list.getComment(comment_type, chara_type));

}
void CharaPlayer::sendSexualComment() {

	charaSexualState now_sexual_state = this->_sexual_state;


	if (now_sexual_state != charaSexualState::normal) {
		// コメント内容を決める
		charaCommentType sexual_comment_type = charaCommentType::no_type;
		switch (now_sexual_state) {
		case charaSexualState::feel_hot:
			sexual_comment_type = charaCommentType::feel_hot_normal;
			break;
		case charaSexualState::oestrus:
			sexual_comment_type = charaCommentType::feel_hot_normal;
			break;
		case charaSexualState::extasy:
			sexual_comment_type = charaCommentType::extasy;
			//this->sendDirectComment(this->_comment_list.getComment(sexual_comment_type, charaSexualType.normal));
			//Debug.WriteLine("exstasy now");
			//return;
			break;
		}

		// コメントタイプを決める
		//@TODO
		//this->sendComment(this->_comment_list->getComment(sexual_comment_type, charaSexualType::normal));
	}


	//charaCommentType.honey_start, charaSexualType.normal
}

void CharaPlayer::setGroupList() {
	this->_my_group_list = this->_chara_seed->getMyGroupList();
}
//test only -------------------------------------------------

void CharaPlayer::testComment() {
	if (this->_comment_delay_count <= 0) {

		// テスト用コメント投稿
		//keybord to D
		/*
		if(this->_control_flag == true && Input2.GamePad0.L.Down == true) {
		if (this->_test_comment_num % 4 <= 1) {
		this->sendComment("テスト投稿だよー\n"+this->_test_comment_num+"つ目だよー");
		} else {
		this->sendComment("テスト投稿だよー "+this->_test_comment_num+"つ目だよー");
		}
		this->_test_comment_num++;

		}
		*/
	}
	else {

	}
}
void CharaPlayer::testState() {
	return;
	// keybord to S
	/*
	if (this->_control_flag == true && Input2.GamePad0.Triangle.Press == true) {

		this->sendComment("毒なう");

		this->_state_list->setState(abnormalStateType::feel_hot, 1);

	}
	// */
}
void CharaPlayer::testAction() {
	//
	if (this->_down_flag == true) {
		return;
	}

	//Debug.WriteLine("[charaPlayer] spell state : "+this->_spell_status);

	if (this->checkSpellFlag() == true) {
		return;
	}

	/*
	// skill action -----------------------------------------
	if (this->_control_flag == true && Input2.GamePad0.L.Down == true && this->_control_flag == true && Input2.GamePad0.R.Down == true) {
		// keybord to Q and E

	}
	else if (this->_control_flag == true && Input2.GamePad0.L.Down == true) {
		// keybord to Q

		if (this->_control_flag == true && Input2.GamePad0.Circle.Press == true) {
			// keybord to D
			//MagicShot
			SkillBase set_skill_obj = new MagicShot(this, this->getAllCharaList());
			this->setSkill(set_skill_obj);


		}
		else if (this->_control_flag == true && Input2.GamePad0.Cross.Press == true) {
			// keybord to S


		}
		else if (this->_control_flag == true && Input2.GamePad0.Square.Press == true) {
			// keybord to A


		}
		else if (this->_control_flag == true && Input2.GamePad0.Triangle.Press == true) {
			// keybord to W


		}

	}
	else if (this->_control_flag == true && Input2.GamePad0.R.Down == true) {
		// keybord to E

		if (this->_control_flag == true && Input2.GamePad0.Circle.Press == true) {
			// keybord to D


		}
		else if (this->_control_flag == true && Input2.GamePad0.Cross.Press == true) {
			// keybord to S

			//FrostBreakerSlash
			SkillBase set_skill_obj = new FrostBreakerSlash(this, this->getAllCharaList());
			this->setSkill(set_skill_obj);

		}
		else if (this->_control_flag == true && Input2.GamePad0.Square.Press == true) {
			// keybord to A

			//DrawnWindSlash
			SkillBase set_skill_obj = new DrawnWindSlash(this, this->getAllCharaList());
			this->setSkill(set_skill_obj);

		}
		else if (this->_control_flag == true && Input2.GamePad0.Triangle.Press == true) {
			// keybord to W
			SwordSlash set_skill_obj = new SwordSlash(this, this->getAllCharaList());
			this->setSkill(set_skill_obj);
		}

	}
	else {
		// keybord to D
		if (this->_control_flag == true && Input2.GamePad0.Circle.Press == true) {

			if ((this->_game_pad_data.Buttons & GamePadButtons.Cross) != 0) {
			}

		}
		//keybord to A
		if (this->_control_flag == true && Input2.GamePad0.Square.Press == true) {
			bool attack_flag = this->setSkill(new Kogahazan(this, this->_all_chara_list));


			if (attack_flag == true) {
				this->sendComment(this->_comment_list.getComment(charaCommentType.chara_attack, charaSexualType.normal));
			}


		}
		if (this->_control_flag == true && Input2.GamePad0.Triangle.Press == true) {
			// keybord to W
			SkillBase set_skill_obj = new SpeedThrust(this, this->getAllCharaList());
			this->setSkill(set_skill_obj);
		}

		// skill action end -------------------------------------
		// etc action -------------------------------------------
		if (this->checkActionFlag() == true) {
			// keybord to Q
			
//			if (this->_control_flag == true && Input2.GamePad0.L.Press == true) {

//			bool use_item_flag = this->_use_item_list.itemUse(useItemId.testHpHeal);
//			if (use_item_flag == true) {
//			this->sendComment("もぐもぐ…");
//			} else {
//			this->sendComment("アイテム切れだよ…");
//			}


//			}


			// keybord to Z  press 1 frame only
			if (this->_control_flag == true && Input2.GamePad0.Select.Press == true) {

				this->sendComment("剣装備なう");
				this->_equip_item_list.itemUse(this->_test_weapon_index);

			}
			// keybord to Z  press 1 frame only
			if (this->_control_flag == true && Input2.GamePad0.Start.Press == true) {

				if (this->_equip_item_list.itemUse(1)) {
					this->sendComment("鞘装備なう");
				}
			}
			if (this->_control_flag == true && Input2.GamePad0.Circle.Press == true) {

				if (this->_equip_item_list.itemUse(2) == true) {
					this->sendComment("両手剣装備なう");
				};
			}
			// keybord to S
			if (this->_control_flag == true && Input2.GamePad0.Cross.Press == true) {
				bool jump_flag = this->setJumpNormal(4.0);
				if (jump_flag == true) {
					this->sendComment("じゃ～んぷ");
				}
			}
		}
	}
	*/
}

void CharaPlayer::setCharaMapPoint(double point_x, double point_y) {

	this->setDrawX(point_x);
	this->setDrawY(point_y);
	this->updateBlockPoint();
	this->updateCamera();
}