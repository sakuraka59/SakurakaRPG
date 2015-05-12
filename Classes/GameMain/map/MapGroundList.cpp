#include "MapGroundList.h"

#include <math.h>
#include "../GAME_SETTING.h"
#include "MapGroundBase.h"
#include "../chara/CharaPlayer.h"


MapGroundList::MapGroundList(GameCamera* camera_obj, std::unordered_map<int, int> map_data, int map_type, CharaPlayer* player_obj) {
	//this._texture_info = ResourceManage.getTextureInfo("/Application/res/map/maptest.png", 2, 3);
	this->_camera_obj = camera_obj;
	//this._ground_sprite_list = new SpriteList(this._texture_info);

	this->_map_data = map_data;
	this->_player_obj = player_obj;

	this->_map_type = map_type;


	this->_ground_sprite_list = new RenderObject();
	/*
	Vector2i[] vector_list = new Vector2i[]{
		new Vector2i(0, 0),	// 何もない
			new Vector2i(0, 2),	// デフォルト壁
			new Vector2i(1, 1),	// 部屋
			new Vector2i(1, 2),	// 通路
			new Vector2i(0, 1),	// 通路接続
			new Vector2i(0, 0),	// 強制壁
			new Vector2i(1, 0)	// 
	};
	*/
	int map_test_width = 15;
	int map_test_height = 9;

	switch (map_type) {
	case 0:
		//Random rnd = new Random();

		for (int i = 0; i < map_test_width * map_test_height; i++) {

			int random_num = 0;// rnd.Next(4);
			/*
			MapGroundBase* test_obj = new MapGroundBase(
				this._texture_info,
				vector_list[random_num],
				i % 15, (int)(i / 15),
				15, 9
				);
				*/
			MapGroundBase* test_obj = new MapGroundBase(i % map_test_width, (int)(i / map_test_width), map_test_width, map_test_height, 0);
			this->_ground_sprite_list->addChild(test_obj);
			//this->_ground_sprite_list->addChild(test_obj);
		}
		break;
	case 1:
		/*
		int map_width = map_data.GetLength(0);
		int map_height = map_data.GetLength(1);

		for (int x = 0; x < map_width; x++) {
			if (this._ground_obj_list.ContainsKey(x) == false) {
				this._ground_obj_list[x] = new Dictionary<int, SpriteTile>();
			}
			if (this._map_draw_list.ContainsKey(x) == false) {
				this._map_draw_list[x] = new Dictionary<int, bool>();
			}
			for (int y = 0; y < map_height; y++) {

				MapGroundBase test_obj = new MapGroundBase(
					this._texture_info,
					vector_list[map_data[x, y]],
					x, y * (-1),
					map_width, map_height
					);


				this._ground_obj_list[x][y * (-1)] = test_obj.getGroundSprite();
				//this._ground_sprite_list.AddChild(this._ground_obj_list[x][y]);


				this._map_draw_list[x][y * (-1)] = false;
			}

		}
		//*/
		break;
	}

	this->_ground_sprite_list->setPosition(0, 0);
	this->addChild(this->_ground_sprite_list);
}
void MapGroundList::Init(){
	
	// 地面ブロックの描画をする
	int block_draw_x = this->_player_obj->getMapBlockX();
	int block_draw_y = this->_player_obj->getMapBlockY();

	int draw_block_width = (int)ceil((double)GAME_WIDTH / (double)MAP_BLOCK_WIDTH);
	int draw_block_height = (int)ceil((double)GAME_HEIGHT / (double)MAP_BLOCK_HEIGHT);

	int outer_size_x = this->_map_outer_size_x * (-1);
	int outer_size_y = this->_map_outer_size_y * (-1);

	/*
	for (int x = 0; x < draw_block_width + (outer_size_x * 2); x++) {
		int set_x = block_draw_x + x - 7 - outer_size_x;

		if (this->_ground_obj_list->ContainsKey(set_x) == false) {
			continue;
		}
		for (int y = 0; y < draw_block_height + (outer_size_y * 2); y++) {
			int set_y = block_draw_y + y - 4 - outer_size_y;
			if (this->_ground_obj_list[set_x]->ContainsKey(set_y) == false) {
				continue;
			}

			this->_map_draw_list[set_x][set_y] = true;
			this->_ground_sprite_list->addChild(this->_ground_obj_list[set_x][set_y]);

		}
	}
	*/
	// キャラクターをセットする
	this->setCharaPoint();
}
void MapGroundList::Update() {

}
void MapGroundList::reviewGroundBlockX(int add_block_draw_x, int remove_block_draw_x, int block_draw_y, int map_max_y) {

}
void MapGroundList::reviewGroundBlockY(int add_block_draw_y, int remove_block_draw_y, int block_draw_x, int map_max_x) {

}
void MapGroundList::setCharaPoint() {

}