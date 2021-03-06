#include "cocos2d.h"
#include "../../ResourceManage.h"
#include "PlayUi.h"
//#include "../chara/chara_seed/SeedBase.h"

#include "../GAME_SETTING.h"
#include "../GameCamera.h"

#include "../chara/CharaPlayer.h"
#include "../chara/CharaNpc.h"
#include "../chara/chara_comment/CharaCommentList.h"

#include "../item/ItemMasterList.h"

#include "../shadow/ShadowObjectList.h"


#include "../map/MapBase.h"
#include "../map/MapObjectList.h"
#include "../map/MapObjectBase.h"
#include "../map/map_ground_object/MapGroundObjectList.h"
#include "../map/map_ground_object/MapGroundObjectBase.h"
#include "../map/map_ground_object/map_bg_obj/map_move/MapMoveManager.h"

#include "../magic/MagicBase.h"

#include "../hit/HitCheck.h"
#include "../hit/HitCircle.h"
#include "../hit/HitSquare.h"

using namespace std;
using namespace cocos2d;

PlayUi::PlayUi(PlayerCommentUI* comment_ui_obj) {
	// test ---------------------------------------------------------
//	this->_test_sprite = Sprite::create("HelloWorld.png");
//	this->_test_sprite->setPosition(new Vec2(500,0));
//	this->_test_sprite->setPosition(500, 200);
//	this->addChild(this->_test_sprite);
//	this->_test_sprite = ResourceManage::getSprite("icon.png");

//	SeedBase* hoge = new SeedBase();
//	CharaBase* piyo = new CharaBase();




	// test end -----------------------------------------------------

	// シングルトン系の初期化
	ItemMasterList::loadItemList();
	CharaCommentList::loadCommentList();


	// 描画順番差し替えが必要なオブジェクト
	this->_order_object_list = new RenderObject();

	// 表示場所のカメラ情報
	this->_play_camera = new GameCamera();

	// オブジェクトの影情報
	this->_shadow_list = new ShadowObjectList(this->_play_camera);


	// プレイヤーキャラクターの宣言
	this->_player_obj = new CharaPlayer(this->_play_camera, comment_ui_obj, &this->_chara_list, &this->_magic_list, this->_shadow_list);
	
	this->_chara_list.push_back(this->_player_obj);
	this->_shadow_list->setRenderObject(this->_player_obj);


	this->_order_object_list->addChild(this->_player_obj, (int)(this->_player_obj->getDrawY() * (-1)));

	//マップ情報の宣言
	//if (SET_VIEW_STATE == 1) {
	this->_map_obj = new MapBase(this->_play_camera, this->_player_obj);
	this->addChild(this->_map_obj);
	//}


	//if (SET_MAP_MODE == 1) {
	for (int i = 0; i < 1; i++){
		CharaNpc* npc_obj = new CharaNpc(400 + 50 * i, -100, this->_play_camera, &this->_chara_list, &this->_magic_list, this->_shadow_list);
			
		this->_npc_list.push_back(npc_obj);
		this->_chara_list.push_back(npc_obj);

		this->_shadow_list->setRenderObject(npc_obj);
		this->_map_obj->setCharaPoint(npc_obj, 3);

		this->_order_object_list->addChild(npc_obj, (int)(npc_obj->getDrawY() * (-1)));
	}
	//}


	// 影は地面の上で、かつorder切り替える系オブジェクトの下
	this->addChild(this->_shadow_list);

	this->addChild(this->_order_object_list);

	// テスト
	/*
	this->_map_obj_line_list[0] = new MapObjectList(0, this->_play_camera, this->_player_obj);

	this->_map_obj_line_list[0]->setObject(0);
	this->_order_object_list->addChild(this->_map_obj_line_list[0], this->_map_obj_line_list[0]->getDrawY());
	*/

	
	
	/*
	ParticleSystemQuad* particle = ParticleSystemQuad::create("particle/test_particle.plist");
	particle->setPosition(0, 0);
	this->addChild(particle);
	*/

	this->_map_obj->Init();

	this->_map_obj_line_list = this->_map_obj->getMapObjectLineList();

	this->_mg_object_list_obj = this->_map_obj->getMgObjectList();
//	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {

	//for(auto pair:mp){

		//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
		//		this->_map_obj_line_list[map_obj_iterator->first]->Update();
		//		map_obj_line;
		//this->_order_object_list->addChild(this->_map_obj_line_list[map_obj_iterator->first], this->_map_obj_line_list[map_obj_iterator->first]->getDrawY() * (-1));
	for (auto map_obj_line : this->_map_obj_line_list) {
		this->_order_object_list->addChild(map_obj_line.second, map_obj_line.second->getDrawY() *(-1));
	}
}
void PlayUi::Update(){
	// マップアップデート処理

	this->_map_obj->Update();
	this->_mg_object_list_obj->UpdateInit();



	// キャラクターのアップデート処理
	for (CharaBase* chara_obj : this->_chara_list) {
		chara_obj->Update();
		// マップオブジェクトとの当たり判定
		this->checkHitMapObject(chara_obj);
		this->checkHitMapGroundObject(chara_obj);
	}


	// スキルあたり判定

	this->_player_obj->updateCamera();
	this->_play_camera->Update();

	// キャラクター描画更新
	for (CharaBase* chara_obj : this->_chara_list) {
		this->_order_object_list->reorderChild(chara_obj, (int)chara_obj->getDrawY() * (-1));
		chara_obj->updateDraw();
	}


	// 魔法の更新処理 -----------------------------------------
	list<MagicBase*> delete_magic_list;

	for(MagicBase* magic_obj : this->_magic_list) {
		//Debug.WriteLine("[PlayUI]test:"+ hoge);
		if (magic_obj->getOrderSetFlag() == false) {
			this->_order_object_list->addChild(magic_obj, (int)magic_obj->getDrawY() * (-1));
			magic_obj->setOrderSetFlag();
		}

		magic_obj->Update();
		if (magic_obj->getShadowRemoveFlag() == true) {
			magic_obj->removeShadow(this->_shadow_list);
		}

		if (magic_obj->getRemoveFlag() == true) {

			// ループ内で元リストから削除するとエラー発生するので、削除処理は別に行う
			delete_magic_list.push_back(magic_obj);

		} else {
			this->_order_object_list->reorderChild(magic_obj, (int)magic_obj->getDrawY() * (-1));
			
			this->checkHitMagic(magic_obj, &delete_magic_list);
		}

	}
	// 削除リストに入った魔法を削除する
	
	for(MagicBase* magic_obj : delete_magic_list) {

//		this->_shadow_list->removeRenderObject(magic_obj);
		this->_order_object_list->removeChild(magic_obj, true);
		this->_magic_list.remove(magic_obj);
		//delete magic_obj;
	}


	// 影描画する
	this->_shadow_list->Update();

	// プレイヤーの調べる系アクション処理
	if (this->_player_obj->getSearchFlag() == true) {

		this->playerSearchAction();
	}

	// 調べる系終えた後、マップ移動の更新処理
	if (MapMoveManager::checkMapMove() == true) {
		this->setMapMove();
	}
	//
	float camera_set_x = this->_play_camera->getCameraX();
	float camera_set_y = this->_play_camera->getCameraY();
	this->setPosition(camera_set_x, camera_set_y);
}
void PlayUi::checkHitMapObject(CharaBase* chara_obj) {

//	return;

	int chara_map_x = chara_obj->getMapBlockX();
	int chara_map_y = chara_obj->getMapBlockY();

	for (int y = -1; y < 3; y++) {
		int check_map_y = chara_map_y + y;

		
		if (this->_map_obj_line_list[check_map_y] == nullptr) {
			continue;
		}
		
		for (int x = -1; x < 3; x++) {
			int check_map_x = chara_map_x + x;

			MapObjectBase* check_map_obj = this->_map_obj_line_list[check_map_y]->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				continue;
			}

			
			HitCircle* circle_obj = chara_obj->getHitCircle();

			if (check_map_obj->getHitCheckType() == 3) {

				HitSquare* square_obj = check_map_obj->getHitSquare();

				if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
					// 適当に戻す
					chara_obj->setBeforeInsertDraw();
				}
			}
		}
	}
}
void PlayUi::checkHitMapGroundObject(CharaBase* chara_obj) {
	int chara_map_x = chara_obj->getMapBlockX();
	int chara_map_y = chara_obj->getMapBlockY();

	/*
	unordered_map<int, unordered_map<int, MapGroundObjectBase*>>* mg_obj_data_ptr = this->_mg_object_list_obj->getGroundObjData();
	unordered_map<int, unordered_map<int, MapGroundObjectBase*>>mg_obj_data = *mg_obj_data_ptr;
	*/
	unordered_map<int, unordered_map<int, MapGroundObjectBase*>> mg_obj_data = this->_mg_object_list_obj->getGroundObjData();

	for (int y = -1; y < 2; y++) {
		int check_map_y = chara_map_y + y;

		for (int x = -1; x < 2; x++) {
			int check_map_x = chara_map_x + x;

			
			MapGroundObjectBase* mb_obj = mg_obj_data[check_map_x][check_map_y];

			if (mb_obj == nullptr) {
				continue;
			}
			
			if (mb_obj->getHitFlag() != true) {
				continue;
			}


			HitCircle* circle_obj = chara_obj->getHitCircle();


			HitSquare* square_obj = mb_obj->getHitSquare();

			if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
				mb_obj->autoActive(chara_obj);
				// 適当に戻す
				
			}
			
		}
	}
}
void PlayUi::checkHitMagic(MagicBase* magic_obj, std::list<MagicBase*>* delete_magic_list) {
	if (magic_obj->getHitCheckFlag() != true) {
		return;
	}
	int main_obj_map_x = magic_obj->getMapBlockX();
	int main_obj_map_y = magic_obj->getMapBlockY();
	HitCircle* circle_obj = magic_obj->getHitCircle();

	// キャラクターとの当たり判定
	for(CharaBase* chara_obj : this->_chara_list) {
		// 放った本人は当たらない
		if (magic_obj->getCharaObj() == chara_obj) {
			continue;
		}

		// 倒した敵には当たらない
		if (chara_obj->getDownFlag() == true) {
			continue;
		}
		if (HitCheck::checkCircleAndCircle(circle_obj, chara_obj->getHitCircle()) == true &&
			this->checkHeightHit(magic_obj, chara_obj) == true) {
			// 当たった判定あり
			magic_obj->hitCharaDamage(chara_obj);
			magic_obj->removeShadow(this->_shadow_list);
			//delete_magic_list->push_back(magic_obj);
		}
	}

	// オブジェクトとの当たり判定 ----------------------------------------
	for (int y = -1; y < 2; y++) {
		int check_map_y = main_obj_map_y + y;

		if (this->_map_obj_line_list[check_map_y] == nullptr) {
			continue;
		}
		for (int x = -1; x < 2; x++) {
			int check_map_x = main_obj_map_x + x;

			MapObjectBase* check_map_obj = this->_map_obj_line_list[check_map_y]->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				continue;
			}


			HitSquare* square_obj = check_map_obj->getHitSquare();

			HitCheck::checkRectAndCircle(circle_obj, square_obj);
			// とりあえず適当に判定をもつ

			//Debug.WriteLine("["+this.GetType()+"]check_magic:"+circle_obj.getRadius());
			if (check_map_obj->getHitCheckType() == 3) {

				if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
					// 当たった判定あり
					magic_obj->removeShadow(this->_shadow_list);
					//delete_magic_list->push_back(magic_obj);
				}
			}

		}
	}

}
bool PlayUi::checkHeightHit(MagicBase* magic_obj, CharaBase* check_chara_obj) {

	double hit_height_base = (double)(magic_obj->getDrawZ());
	double hit_height_top = (double)(hit_height_base + magic_obj->getHitHeight());
	double chara_height_base = (double)(check_chara_obj->getDrawZ());
	double chara_height_top = (double)(check_chara_obj->getDrawZ() + check_chara_obj->getHitHeight());

	if (hit_height_top >= chara_height_base &&
		hit_height_base <= chara_height_top) {

		return true;
	}
	return false;
}
CharaPlayer* PlayUi::getCharaPlayerObj() {
	return this->_player_obj;
}

void PlayUi::playerSearchAction() {
	
	CharaPlayer* chara_obj = this->_player_obj;
	double chara_search_x = chara_obj->getSearchX();
	double chara_search_y = chara_obj->getSearchY();

	int search_map_x = (int)floor(chara_search_x / MAP_BLOCK_WIDTH);
	int search_map_y = (int)floor(chara_search_y / MAP_BLOCK_WIDTH);

	// マップ上の通常オブジェクトを調べる
	if (this->_map_obj_line_list[search_map_y] != nullptr) {
		MapObjectBase* map_object_obj = this->_map_obj_line_list[search_map_y]->getMapObject(search_map_x);
		if (map_object_obj != nullptr) {
			if (map_object_obj->getActionFlag() == true) {
				
				HitSquare* obj_square_obj = map_object_obj->getHitSquare();

				
				double test_angle = 0;
				HitSquare* search_square_obj = new HitSquare(chara_search_x, chara_search_y, 1, 1, test_angle);
				if (HitCheck::checkRectAndRect(obj_square_obj, search_square_obj) == true) {
					map_object_obj->actionActive(chara_obj);
					return;
				}
			}
		}
	}
	// マップ上の地面オブジェクトを調べる -------------------------------------
	/*
	unordered_map<int, unordered_map<int, MapGroundObjectBase*>>* mg_obj_data_ptr = this->_mg_object_list_obj->getGroundObjData();
	unordered_map<int, unordered_map<int, MapGroundObjectBase*>>mg_obj_data = *mg_obj_data_ptr;
	*/
	unordered_map<int, unordered_map<int, MapGroundObjectBase*>> mg_obj_data = this->_mg_object_list_obj->getGroundObjData();

	MapGroundObjectBase* mb_obj = mg_obj_data[search_map_x][search_map_y];

	auto point_hoge = &this->_mg_object_list_obj;
	if (mb_obj == nullptr) {
		return;
	}

	if (mb_obj->getActionFlag() != true) {
		return;
	}

	HitSquare* obj_square_obj = mb_obj->getHitSquare();
	
	double test_angle = 0;
	HitSquare* search_square_obj = new HitSquare(chara_search_x, chara_search_y, 1, 1, test_angle);

	if (HitCheck::checkRectAndRect(obj_square_obj, search_square_obj) == true) {
		mb_obj->actionActive(chara_obj);
	}
	int hoge = 1;

	/*
	for (int y = -1; y < 3; y++) {
		int check_map_y = search_map_y + y;

		for (int x = -1; x < 3; x++) {
			int check_map_x = search_map_x + x;

			MapGroundObjectBase* mb_obj = mg_obj_data[check_map_x][check_map_y];
		}
	}
	
	return;

	/*
	std::unordered_map<int, unordered_map<int, MapGroundObjectBase*>> mg_obj_data = this->_mg_object_list_obj->getGroundObjData();

	for (int y = -1; y < 3; y++) {
		int check_map_y = chara_map_y + y;

		for (int x = -1; x < 3; x++) {
			int check_map_x = chara_map_x + x;


			MapGroundObjectBase* mb_obj = mg_obj_data[check_map_x][check_map_y];

			if (mb_obj == nullptr) {
				continue;
			}

			if (mb_obj->getHitFlag() != true) {
				continue;
			}


			HitCircle* circle_obj = chara_obj->getHitCircle();


			HitSquare* square_obj = mb_obj->getHitSquare();

			if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
				mb_obj->autoActive(chara_obj);
				// 適当に戻す

			}

		}
	}
	*/

}
/*
void PlayUi::setItemUiObj(ItemUi* item_ui_obj){
//	this->_item_ui_obj = item_ui_obj;
}
//*/
void PlayUi::setMapMove() {
	// とりあえず現状のマップオブジェクトを初期化する必要あり
	for (auto map_obj_line : this->_map_obj_line_list) {
		this->_order_object_list->removeChild(map_obj_line.second, true);
	}


	this->_map_obj->mapMoveUpdate();

	this->_map_obj_line_list = this->_map_obj->getMapObjectLineList();
	for (auto map_obj_line : this->_map_obj_line_list) {
		this->_order_object_list->addChild(map_obj_line.second, map_obj_line.second->getDrawY() *(-1));
		//mapSetDrawInit
		map_obj_line.second->mapSetDrawInit();
	}

	this->_mg_object_list_obj = this->_map_obj->getMgObjectList();

}