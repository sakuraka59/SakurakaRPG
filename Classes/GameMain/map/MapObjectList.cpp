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
	
	
	/*
	this->_draw_flag = true;
	this->addChild(this->_object_draw_list);
	//*/

	this->_draw_flag = false;
	this->removeChild(this->_object_draw_list, true);

	int set_x = (int)(0 + this->_draw_correction_x);
	int set_y = (int)(this->_draw_y - this->_draw_correction_y);
	this->setPosition(set_x, set_y);

	this->_before_x = this->_player_obj->getMapBlockX();
	this->_before_y = this->_player_obj->getMapBlockY();
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
	// /*
	if (this->_draw_flag == true) {
		this->_object_draw_list->addChild(map_obj);
		this->_map_obj_draw_list[map_block_x] = true;
	}
	// */
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
	int width_side = this->mapDrawWidth();
	int height_side = this->mapDrawHeight();


	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();

	// Yマス座標移動した場合
	if (this->_before_y != player_map_y) {
		if (this->_before_y < player_map_y){
			// 上へ移動

			// 描画範囲外の場合、オブジェクトの表示を全削除
			if (this->_map_block_y < player_map_y - height_side) {
				this->removeObjectDrawY(height_side);
			} else {
				// 描画範囲内の場合
				this->resetObjectDrawY(width_side, height_side);
			}

		} else {
			// 下へ移動
			if (this->_map_block_y > player_map_y - height_side) {
				this->removeObjectDrawY(height_side);
			}
			else {
				// 描画範囲内の場合
				this->resetObjectDrawY(width_side, height_side);
			}
		}

		this->_before_y = this->_player_obj->getMapBlockY();
	}

	// Xマス座標移動した場合
	if (this->_draw_flag == true) {
		if (this->_before_x != player_map_x) {

			if (this->_before_x < player_map_x){
				// 右へ移動
				// 自身の位置から端の隣なので「-1」が必要
				int remove_x = player_map_x - width_side -1;
				this->removeObjectDrawX(remove_x);


				// 右へ移動
				int add_x = player_map_x + width_side;
				this->resetObjectDrawX(add_x);
			} else {
				// 左へ移動
				// 自身の位置から端の隣なので「+1」が必要
				int remove_x = player_map_x + width_side + 1;
				this->removeObjectDrawX(remove_x);


				// 右へ移動
				int add_x = player_map_x - width_side;
				this->resetObjectDrawX(add_x);
			}
			this->_before_x = this->_player_obj->getMapBlockX();
		}
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
	return;
}
//-------------------------------------------------------------------
//	キャラクター初期位置設定後の各種オブジェクト描画
//-------------------------------------------------------------------
void MapObjectList::mapSetDrawInit() {
	
	// キャラクターのマス座標から端までのマス数
	int width_side = this->mapDrawWidth();
	int height_side = this->mapDrawHeight();

	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();
	if (this->_map_block_y < player_map_y - height_side ||
		this->_map_block_y > player_map_y + height_side) {

		return;
	}

	this->resetObjectDrawY(width_side, height_side);
}
//-------------------------------------------------------------------
//	オブジェクトの描画マス範囲
//-------------------------------------------------------------------
int MapObjectList::mapDrawWidth() {
	int draw_width = ceil(GAME_WIDTH / MAP_BLOCK_WIDTH) / 2;
	draw_width += 1;

//	draw_width -= 2;
	return draw_width;
}
//-------------------------------------------------------------------
//	オブジェクトの描画マス範囲
//-------------------------------------------------------------------
int MapObjectList::mapDrawHeight(){
	int draw_height = ceil(GAME_HEIGHT / MAP_BLOCK_HEIGHT) / 2;
	draw_height += 2;

//	draw_height -= 3;
	return draw_height;
}

//-------------------------------------------------------------------
//	Yマス座標の描画範囲外での非表示処理
//-------------------------------------------------------------------
void MapObjectList::removeObjectDrawY(int height_side) {
	if (this->_draw_flag == false) {
		return;
	}
//	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();
	int check_y_min = player_map_y - height_side;
	int check_y_max = player_map_y + height_side;
	if (this->_map_block_y >= check_y_min && this->_map_block_y <= check_y_max) {
		return;
	}
	int random_map_width = RandomDungeonSetting::getDungeonWidth();
	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		/*
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}
		// */
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
void MapObjectList::resetObjectDrawY(int width_side, int height_side) {
	
	
	if (this->_draw_flag == true) {
		return;
	}
	int random_map_width = RandomDungeonSetting::getDungeonWidth();

	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();

	int check_y_min = player_map_y - height_side;
	int check_y_max = player_map_y + height_side;
	if (this->_map_block_y < check_y_min || this->_map_block_y > check_y_max) {
		return;
	}

	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}
		int check_x_min = player_map_x - width_side;
		int check_x_max = player_map_x + width_side;
		if (map_block_x < check_x_min || map_block_x > check_x_max) {
			continue;
		}
		this->_object_draw_list->addChild(check_map_obj);
		this->_map_obj_draw_list[map_block_x] = true;

	}
	// 自身のオブジェクトの表示を表示
	this->addChild(this->_object_draw_list, true);
	this->_draw_flag = true;
}

//-------------------------------------------------------------------
//	Xマス座標の描画範囲外での非表示処理
//-------------------------------------------------------------------
void MapObjectList::removeObjectDrawX(int remove_x) {
	if (this->_draw_flag == false) {
		return;
	}

	MapObjectBase* check_map_obj = this->getMapObject(remove_x);
	if (check_map_obj == nullptr) {
		return;
	}
	this->_object_draw_list->removeChild(check_map_obj, true);
	this->_map_obj_draw_list[remove_x] = false;
}

//-------------------------------------------------------------------
//	Xマス座標の描画範囲内への表示再開処理
//-------------------------------------------------------------------
void MapObjectList::resetObjectDrawX(int reset_x) {
	if (this->_draw_flag == false) {
		return;
	}
	if (this->_map_obj_draw_list[reset_x] == true) {
		return;
	}

	MapObjectBase* check_map_obj = this->getMapObject(reset_x);
	if (check_map_obj == nullptr) {
		return;
	}
	
	this->_object_draw_list->addChild(check_map_obj, true);
	this->_map_obj_draw_list[reset_x] = true;
}
