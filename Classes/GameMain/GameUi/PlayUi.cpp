#include "cocos2d.h"
#include "../../ResourceManage.h"
#include "PlayUi.h"
//#include "../chara/chara_seed/SeedBase.h"

#include "../GAME_SETTING.h"
#include "../GameCamera.h"
#include "../chara/CharaPlayer.h"
#include "../shadow/ShadowObjectList.h"
#include "../skill/SkillList.h"
#include "../map/MapBase.h"
#include "../map/MapObjectList.h"
#include "../map/MapObjectBase.h"

#include "../hit/HitCheck.h"
#include "../hit/HitCircle.h"
#include "../hit/HitSquare.h"


using namespace cocos2d;

PlayUi::PlayUi(PlayerCommentUI* comment_ui_obj, cocos2d::EventListenerKeyboard* KEYBORD_EVENT) {
	// test ---------------------------------------------------------
//	this->_test_sprite = Sprite::create("HelloWorld.png");
//	this->_test_sprite->setPosition(new Vec2(500,0));
//	this->_test_sprite->setPosition(500, 200);
//	this->addChild(this->_test_sprite);
//	this->_test_sprite = ResourceManage::getSprite("icon.png");

//	SeedBase* hoge = new SeedBase();
//	CharaBase* piyo = new CharaBase();
	// test end -----------------------------------------------------
	this->_order_object_list = new RenderObject();

	// 表示場所のカメラ情報
	this->_play_camera = new GameCamera();

	// オブジェクトの影情報
	this->_shadow_list = new ShadowObjectList(this->_play_camera);

	// スキルオブジェクトの宣言
//	this->_skill_list = new SkillList();

	// プレイヤーキャラクターの宣言
	this->_player_obj = new CharaPlayer(this->_play_camera, comment_ui_obj, this->_chara_list, this->_skill_list, this->_magic_list, this->_shadow_list);
	
	this->_chara_list.push_back(this->_player_obj);
	this->_order_object_list->addChild(this->_player_obj, (int)(this->_player_obj->getDrawY() * (-1)));

	//マップ情報の宣言
	//if (SET_VIEW_STATE == 1) {
		this->_map_obj = new MapBase(this->_play_camera, this->_player_obj);
		this->addChild(this->_map_obj);
	//}




	this->addChild(this->_order_object_list);

	// テスト
	/*
	this->_map_obj_line_list[0] = new MapObjectList(0, this->_play_camera, this->_player_obj);

	this->_map_obj_line_list[0]->setObject(0);
	this->_order_object_list->addChild(this->_map_obj_line_list[0], this->_map_obj_line_list[0]->getDrawY());
	*/
	this->_map_obj_line_list = this->_map_obj->getMapObjectLineList();
	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {
//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
//		this->_map_obj_line_list[map_obj_iterator->first]->Update();
//		map_obj_line;
		this->_order_object_list->addChild(this->_map_obj_line_list[map_obj_iterator->first], this->_map_obj_line_list[map_obj_iterator->first]->getDrawY() * (-1));

	}
	
	
	/*
	ParticleSystemQuad* particle = ParticleSystemQuad::create("particle/test_particle.plist");
	particle->setPosition(0, 0);
	this->addChild(particle);
	*/

	this->_map_obj->Init();
}
void PlayUi::Update(){
	// マップアップデート処理
//	if (SET_VIEW_STATE == 1) {
		this->_map_obj->Update();
//	}
	
	/*
	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {
//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
//		this->_map_obj_line_list[map_obj_iterator->first]->Update();
//		map_obj_line;
		
	}
	// */
	/*
	foreach(KeyValuePair<int, Dictionary<int, MapObjectBase>> list_pair in this._map_obj_list) {
		foreach(KeyValuePair<int, MapObjectBase> pair in list_pair.Value) {
			pair.Value.Update();
		}
	}
	*/
	// キャラクターのアップデート処理
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_obj = *chara_iterator;
		chara_obj->Update();
		// マップオブジェクトとの当たり判定
		this->checkHitMapObject(chara_obj);
	}

	// 魔法更新

	// スキルあたり判定

	this->_player_obj->updateCamera();
	this->_play_camera->Update();

	// 描画更新
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_obj = *chara_iterator;
		this->_order_object_list->reorderChild(chara_obj, (int)chara_obj->getDrawY() * (-1));
		chara_obj->updateDraw();
	}
}
void PlayUi::checkHitMapObject(CharaBase* chara_obj) {
	//			if (chara_obj.getDrawX() != chara_obj.getBeforeX() ||
	//			    chara_obj.getDrawY() != chara_obj.getBeforeY()) {
	
	int chara_map_x = chara_obj->getMapBlockX();
	int chara_map_y = chara_obj->getMapBlockY();

	//			HitCheck hit_check_obj = new HitCheck();
	//			Debug.WriteLine("chara point:"+ chara_map_x+"/"+chara_map_y);


	for (int y = -1; y < 3; y++) {
		int check_map_y = chara_map_y + y;

		
		if (this->_map_obj_line_list[check_map_y] == nullptr) {
			continue;
		}
		
		for (int x = -1; x < 3; x++) {
			int check_map_x = chara_map_x + x;

			//							MapObjectBase check_map_obj = this._map_obj_line_list.getMapObject(check_map_x);
			MapObjectBase* check_map_obj = this->_map_obj_line_list[check_map_y]->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				//								Debug.WriteLine("[PlayUI]hit check "+check_map_x+":"+check_map_y);
				continue;
			}

			HitCircle* circle_obj = chara_obj->getHitCircle();
			//*
			if (check_map_obj->getHitCheckType() == 3) {

				HitSquare* square_obj = check_map_obj->getHitSquare();
				//HitCheck.checkRectAndCircle(circle_obj, square_obj);
				//Debug.WriteLine("["+this.GetType()+"]check_chara:"+circle_obj.getRadius());


				if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
					// 適当に戻す
					chara_obj->setBeforeInsertDraw();
				}
			}
			//*/
		}
	}

	
	//			Debug.WriteLine("------------------");
	//			} else {
	//				Debug.WriteLine("before no");
	//			}

	//now_block_x = chara_obj._draw_x/ GameSetting._MAP_BLOCK_WIDTH;

}