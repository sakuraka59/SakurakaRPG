#include "../GAME_SETTING.h"
#include "MapObjectList.h"
#include "MapObjectBase.h"
#include "../GameCamera.h"
#include "cocos2d.h"
MapObjectList::MapObjectList(int map_block_y, GameCamera* camera_obj, CharaPlayer* player_obj)
{
	this->_player_obj = player_obj;
	this->_camera_obj = camera_obj;
	//this->_texture_info = texture_info;

	//this->_object_sprite_list = new SpriteList(this->_texture_info);
	this->_draw_correction_x = (MAP_BLOCK_WIDTH - this->_OBJECT_WIDTH) / 2;

	this->_map_block_y = map_block_y;
	this->_draw_y = (map_block_y * MAP_BLOCK_HEIGHT);

	//this->AddChild(this->_object_sprite_list);
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
	//			this._object_sprite_list.AddChild(map_obj.getObjectSprite());

	MapObjectBase* map_obj = new MapObjectBase(
		map_block_x, this->_map_block_y
		, this->_camera_obj
		);
	this->_map_obj_line_list[map_block_x] = map_obj;
	this->_map_obj_draw_list[map_block_x] = false;

	// @TODO とりあえず全オブジェクトを描画する
	this->addChild(map_obj);
	this->_map_obj_draw_list[map_block_x] = true;
}
bool MapObjectList::checkMapObject(int map_block_x) {
	//this._map_obj_line_list[map_block_x];	

	/*
	if (this->_map_obj_line_list.ContainsKey(map_block_x) == false) {
		return false;
	}
	*/
	return true;
}
MapObjectBase* MapObjectList::getMapObject(int map_block_x) {
	if (this->checkMapObject(map_block_x) == false) {
		return NULL;
	}
	return this->_map_obj_line_list[map_block_x];

}
void MapObjectList::Update() {
	int set_x = (int)(0 - this->_camera_obj->getCameraX() + this->_draw_correction_x);
	int set_y = (int)(this->_draw_y - this->_camera_obj->getCameraY() - this->_draw_correction_y);
	
	// カメラが動いた場合のみ
	if (set_x != this->_before_x || set_y != this->_before_y) {
		//this->Position = new Vector2(set_x, set_y);
		this->setPosition(set_x, set_y);


		/*
		Random rand_obj = new Random();

		this->_before_x = set_x;
		this->_before_y = set_y;

		int player_map_y = this->_player_obj.getMapBlockY();

		int test_map_width = 7 + 1;
		int test_map_height = 4 + 1;
		bool draw_change_flag = false;
		// ライン上のオブジェクトを非表示にする
		if (this->_draw_flag == true) {
			if (this->_map_block_y + test_map_height < player_map_y ||
				this->_map_block_y - test_map_height > player_map_y) {
				this->RemoveChild(this->_object_sprite_list, true);
				this->_draw_flag = false;

				draw_change_flag = true;
			}
		}
		else {
			if (this->_map_block_y + test_map_height >= player_map_y &&
				this->_map_block_y - test_map_height <= player_map_y) {
				this->AddChild(this->_object_sprite_list);
				this->_draw_flag = true;

				draw_change_flag = true;
			}
		}

		// x -----------------------------
		int player_map_x = this->_player_obj.getMapBlockX();
		int check_x_width = (test_map_width + 1);
		for (int check_obj_x = 0; check_obj_x < (check_x_width * 2 + 1); check_obj_x++){

			int check_map_x = player_map_x - check_x_width + check_obj_x;
			MapObjectBase check_map_obj = this->getMapObject(check_map_x);
			if (check_map_obj == null) {
				continue;
			}
			//	Debug.WriteLine("[MapObjectList]rand : "+rand_obj.Next(1000000));
			//	Debug.WriteLine("[MapObjectList]check_obj_x : "+check_obj_x+"_map_block_y : "+this->_map_block_y);

			if (check_map_x + test_map_width < player_map_x ||
				check_map_x - test_map_width > player_map_x) {

				if (this->_map_obj_draw_list[check_map_x] == true) {

					this->_object_sprite_list.RemoveChild(check_map_obj.getObjectSprite(), true);
					this->_map_obj_draw_list[check_map_x] = false;
				}
				//						check_map_obj.removeDrawObject();

			}
			else if (check_map_x + test_map_width >= player_map_x &&
				check_map_x - test_map_width <= player_map_x) {
				if (this->_map_obj_draw_list[check_map_x] == false) {

					this->_object_sprite_list.AddChild(check_map_obj.getObjectSprite());
					this->_map_obj_draw_list[check_map_x] = true;
				}
				//						this->_object_sprite_list.AddChild(check_map_obj.getObjectSprite());
				//						check_map_obj.resetDrawObject();

			}
		}
		//	this->_map_obj_line_list[map_block_x]
		*/
	}
}