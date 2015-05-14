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
	
	this->_map_obj_line_list[0] = new MapObjectList(0, this->_play_camera, this->_player_obj);

	this->_map_obj_line_list[0]->setObject(0);
	this->_order_object_list->addChild(this->_map_obj_line_list[0], this->_map_obj_line_list[0]->getDrawY());
	
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
	//std::unordered_map<std::string, CMyClass>::iterator iterator;
	/*
	for (auto itr = this->_map_obj_line_list.begin(); itr != this->_map_obj_line_list.end(); ++itr) {
		//MapObjectList* hoge = itr->first;
		
	}
	// */
	
	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {
//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
		this->_map_obj_line_list[map_obj_iterator->first]->Update();
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
		CharaBase* chara_data = *chara_iterator;
		chara_data->Update();
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