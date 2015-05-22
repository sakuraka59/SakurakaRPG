#include "cocos2d.h"
#include "../GAME_SETTING.h"
#include "MapObjectList.h"
#include "MapObjectBase.h"
#include "../GameCamera.h"
#include "RandomDungeonSetting.h"
#include "../chara/CharaPlayer.h"
#include "../../Random.h"


MapObjectList::MapObjectList(int map_block_y, GameCamera* camera_obj, CharaPlayer* player_obj)
{
	this->_player_obj = player_obj;
	this->_camera_obj = camera_obj;
	//this->_texture_info = texture_info;

	//this->_object_sprite_list = new SpriteList(this->_texture_info);
//	this->_draw_correction_x = (MAP_BLOCK_WIDTH - this->_OBJECT_WIDTH) / 2;
	this->_object_draw_list = new RenderObject();

	this->_map_block_y = map_block_y;
	this->_draw_y = (map_block_y * MAP_BLOCK_HEIGHT);
	int hoge = 0;
	this->addChild(this->_object_draw_list);


	int set_x = (int)(0 + this->_draw_correction_x);
	int set_y = (int)(this->_draw_y - this->_draw_correction_y);
	this->setPosition(set_x, set_y);
	/*
	cocos2d::ParticleSystemQuad* particle = cocos2d::ParticleSystemQuad::create("particle/test_particle.plist");
	particle->setPosition(0, 0);
	this->addChild(particle);
	// */

}

void MapObjectList::setObject(int map_block_x){

	/*
	MapObjectBase map_obj = new MapObjectBase(
		this._texture_info,
		new Vector2i(5, 2),
		map_block_x, this._map_block_y
		, this._camera_obj
		);
	*/
	//			map_obj.Update();
	//			this._object_draw_list.AddChild(map_obj.getObjectSprite());

	MapObjectBase* map_obj = new MapObjectBase(
		map_block_x, this->_map_block_y
		, this->_camera_obj
		);
	this->_map_obj_line_list[map_block_x] = map_obj;
	this->_map_obj_draw_list[map_block_x] = false;

	// @TODO とりあえず全オブジェクトを描画する
	this->_object_draw_list->addChild(map_obj);
	//this->addChild(map_obj);
	this->_map_obj_draw_list[map_block_x] = true;
}
bool MapObjectList::checkMapObject(int map_block_x) {
	//this._map_obj_line_list[map_block_x];	

	
	if (this->_map_obj_line_list[map_block_x] == nullptr) {
		return false;
	}
	
	return true;
}
MapObjectBase* MapObjectList::getMapObject(int map_block_x) {
	if (this->checkMapObject(map_block_x) == false) {
		return nullptr;
	}
	return this->_map_obj_line_list[map_block_x];

}
void MapObjectList::Update() {

	
	//---------------------------------------------------------------
	//	2015-05-22 修正案
	//	1：X座標、Y座標が移動していた場合 → Xブロック、Yブロックが移動していた場合に変更
	//
	//	・Y座標移動時
	//		1：自身（MapobjectLine)が非表示になった場合、子要素をすべてRemove
	//		2：自身が表示になった場合、基準点（プレイヤーキャラクター）からの子要素のみAdd
	//	・X座標移動時
	//		1：そもそも自身が非表示の場合、何もしない
	//		2：ブロックが移動しない限り、何もしない
	//		3：描画範囲内に入った場合にAdd
	//		4：描画範囲外になった場合、Remove
	//---------------------------------------------------------------

	// キャラクターのマス座標から端までのマス数
	int width_side = 1;
	int height_side = 1;

	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();
	

	// Yマス座標移動した場合
	if (this->_before_y != player_map_y) {
		if (this->_before_y < player_map_y){
			// 上へ移動

			// 描画範囲外の場合、オブジェクトの表示を全削除
			if (this->_map_block_y < player_map_y - height_side) {
				this->removeLineObjectDraw();
			} else {
				// 描画範囲内の場合
				this->resetLineObjectDraw(player_map_y, width_side);
			}

		} else {
			// 下へ移動

		}

	}

	this->_before_x = this->_player_obj->getMapBlockX();
	this->_before_y = this->_player_obj->getMapBlockY();
	return;
	/*
	int set_x = (int)(0 + this->_draw_correction_x);
	int set_y = (int)(this->_draw_y - this->_draw_correction_y);

//	int set_x = (int)(0 - this->_camera_obj->getCameraX() + this->_draw_correction_x);
//	int set_y = (int)(this->_draw_y - this->_camera_obj->getCameraY() - this->_draw_correction_y);

	// カメラが動いた場合のみ
	if (set_x != this->_before_x || set_y != this->_before_y) {
		//this->Position = new Vector2(set_x, set_y);
		this->setPosition(set_x, set_y);

		// /*
		
		Random* rand_obj = new Random();

		this->_before_x = set_x;
		this->_before_y = set_y;

		int player_map_y = this->_player_obj->getMapBlockY();

		int obj_draw_width = (int)ceil((double)GAME_WIDTH / (double)MAP_BLOCK_WIDTH); +1;
		int obj_draw_height = (int)ceil((double)GAME_HEIGHT / (double)MAP_BLOCK_HEIGHT); ;
		bool draw_change_flag = false;
		
		// ライン上のオブジェクトを非表示にする
		if (this->_draw_flag == true) {
			if (this->_map_block_y + obj_draw_height < player_map_y ||
				this->_map_block_y - obj_draw_height > player_map_y) {

				this->removeChild(this->_object_draw_list, true);
				this->_draw_flag = false;

				draw_change_flag = true;
			}
		} else {
			if (this->_map_block_y + obj_draw_height >= player_map_y &&
				this->_map_block_y - obj_draw_height <= player_map_y) {
				this->addChild(this->_object_draw_list);
				this->_draw_flag = true;

				draw_change_flag = true;
			}
		}
		
		// x -----------------------------
		//*
		int player_map_x = this->_player_obj->getMapBlockX();
		int check_x_width = (obj_draw_width + 1);
		for (int check_obj_x = 0; check_obj_x < (check_x_width * 2 + 1); check_obj_x++){

			int check_map_x = player_map_x - check_x_width + check_obj_x;
			MapObjectBase* check_map_obj = this->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				continue;
			}
			//	Debug.WriteLine("[MapObjectList]rand : "+rand_obj.Next(1000000));
			//	Debug.WriteLine("[MapObjectList]check_obj_x : "+check_obj_x+"_map_block_y : "+this->_map_block_y);

			if (check_map_x + obj_draw_width < player_map_x ||
				check_map_x - obj_draw_width > player_map_x) {

				if (this->_map_obj_draw_list[check_map_x] == true) {

					this->_object_draw_list->removeChild(check_map_obj, true);

					this->_map_obj_draw_list[check_map_x] = false;
				}
				//						check_map_obj.removeDrawObject();

			}
			else if (check_map_x + obj_draw_width >= player_map_x &&
				check_map_x - obj_draw_width <= player_map_x) {
				if (this->_map_obj_draw_list[check_map_x] == false) {

					this->_object_draw_list->addChild(check_map_obj);

					this->_map_obj_draw_list[check_map_x] = true;
				}
				//						this->_object_sprite_list.AddChild(check_map_obj.getObjectSprite());
				//						check_map_obj.resetDrawObject();

			}
			
		}
		//	this->_map_obj_line_list[map_block_x]
		
		delete rand_obj;
		
	}



	// 各オブジェクトアニメーション
	int draw_block_width = RandomDungeonSetting::getDungeonWidth();
//	int draw_block_width = (int)ceil((double)GAME_WIDTH / (double)MAP_BLOCK_WIDTH);
	if (this->_draw_flag == true) {
		for (int map_x = 0; map_x < draw_block_width; map_x++) {

			if (this->_map_obj_line_list[map_x] != nullptr  &&
				this->_map_obj_draw_list[map_x] == true) {

				this->_map_obj_line_list[map_x]->Update();
			}
		}
	}
	// */
}
//-------------------------------------------------------------------
//	Yマス座標の描画範囲外での非表示処理
//-------------------------------------------------------------------
void MapObjectList::removeLineObjectDraw() {
	if (this->_draw_flag == false) {
		return;
	}
	int random_map_width = RandomDungeonSetting::getDungeonWidth();
	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}
		this->_map_obj_draw_list[map_block_x] = false;
	}
	this->_object_draw_list->removeAllChildren();
	// 自身のオブジェクトの表示を全削除
	this->removeChild(this->_object_draw_list, true);
	this->_draw_flag = false;
}
//-------------------------------------------------------------------
//	Yマス座標の描画範囲内への表示再開処理
//-------------------------------------------------------------------
void MapObjectList::resetLineObjectDraw(int player_map_x, int width_side) {
	return;
	int random_map_width = RandomDungeonSetting::getDungeonWidth();
	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}

		if (map_block_x < player_map_x - width_side || map_block_x > player_map_x + width_side) {
			continue;
		}
		this->_object_draw_list->addChild(check_map_obj);
		this->_map_obj_draw_list[map_block_x] = true;

	}
	// 自身のオブジェクトの表示を表示
	this->addChild(this->_object_draw_list, true);
	this->_draw_flag = true;
}