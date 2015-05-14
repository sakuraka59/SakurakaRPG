#include "MapGroundList.h"

#include <math.h>
#include "../GAME_SETTING.h"
#include "MapGroundBase.h"
#include "../chara/CharaPlayer.h"
#include "../GameCamera.h"
#include "RandomDungeonSetting.h"

#include "../../Random.h"

MapGroundList::MapGroundList(GameCamera* camera_obj, std::unordered_map<int, std::unordered_map<int, int>> map_data, int map_type, CharaPlayer* player_obj) {
	//this->_texture_info = ResourceManage.getTextureInfo("/Application/res/map/maptest.png", 2, 3);
	this->_camera_obj = camera_obj;
	//this->_ground_sprite_list = new SpriteList(this->_texture_info);

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
				this->_texture_info,
				vector_list[random_num],
				i % 15, (int)(i / 15),
				15, 9
				);
				*/
			MapGroundBase* test_obj = new MapGroundBase(i % map_test_width, (int)(i / map_test_width) * (-1), map_test_width, map_test_height, 0);
			this->_ground_sprite_list->addChild(test_obj);
			//this->_ground_sprite_list->addChild(test_obj);
		}
		break;
	case 1:

		/*
		int map_width = map_data.GetLength(0);
		int map_height = map_data.GetLength(1);
		*/
		int map_width = RandomDungeonSetting::getDungeonWidth();
		int map_height = RandomDungeonSetting::getDungeonHeight();
		for (int x = 0; x < map_width; x++) {
			/*
			if (this->_ground_obj_list.ContainsKey(x) == false) {
				this->_ground_obj_list[x] = new Dictionary<int, SpriteTile>();
			}
			if (this->_map_draw_list.ContainsKey(x) == false) {
				this->_map_draw_list[x] = new Dictionary<int, bool>();
			}
			*/
			
			for (int y = 0; y < map_height; y++) {

				MapGroundBase* test_obj = new MapGroundBase(
					x, y * (-1),
					map_width, map_height,
					map_data[x][y]
					);


				this->_ground_obj_list[x][y * (-1)] = test_obj;
				//this->_ground_sprite_list.AddChild(this->_ground_obj_list[x][y]);
				//this->_ground_sprite_list->addChild(test_obj);

				this->_map_draw_list[x][(y * (-1))] = false;
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
	
	//*
	for (int x = 0; x < draw_block_width + (outer_size_x * 2); x++) {
		int set_x = block_draw_x + x - (draw_block_width/2) -outer_size_x;


		for (int y = 0; y < draw_block_height + (outer_size_y * 2); y++) {
			int set_y = block_draw_y + y - (draw_block_height / 2) - outer_size_y;
			if (this->_ground_obj_list[set_x][set_y] == nullptr) {
				continue;
			}

			this->_map_draw_list[set_x][set_y] = true;
			this->_ground_sprite_list->addChild(this->_ground_obj_list[set_x][set_y]);

		}
	}
	//*/
	// キャラクターをセットする
	this->setCharaPoint();
}
void MapGroundList::Update() {
	this->_ground_sprite_list->setPosition(
		(float)(0 - this->_camera_obj->getCameraX()),
		(float)(0 - this->_camera_obj->getCameraY())
	);

	
	int block_draw_x = (this->_player_obj->getMapBlockX());
	int block_draw_y = (this->_player_obj->getMapBlockY());

	//*
	if (block_draw_x != this->_before_block_draw_x ||
		block_draw_y != this->_before_block_draw_y) {

		int draw_block_width = (int)ceil((double)GAME_WIDTH / (double)MAP_BLOCK_WIDTH);
		int draw_block_height = (int)ceil((double)GAME_HEIGHT / (double)MAP_BLOCK_HEIGHT);

		int draw_num_x = abs(block_draw_x - this->_before_block_draw_x);
		int draw_num_y = abs(block_draw_y - this->_before_block_draw_y);

		int map_max_x = 0;
		int map_max_y = 0;
		switch (this->_map_type) {
		case 0:
			break;
		case 1:
			map_max_x = RandomDungeonSetting::getDungeonWidth();
			map_max_y = RandomDungeonSetting::getDungeonHeight();
			break;
		}
		for (int check_x = 0; check_x < draw_num_x; check_x++) {
			if (block_draw_x > this->_before_block_draw_x) {
				// 描画削除するX座標を取得
				int remove_block_draw_x = this->_before_block_draw_x - (int)floor((double)draw_block_width / 2) + check_x + this->_map_outer_size_x;
				// 描画追加するX座標を取得
				int add_block_draw_x = this->_before_block_draw_x + (int)floor((double)draw_block_width / 2) + 1 + check_x - this->_map_outer_size_x;

				this->reviewGroundBlockX(add_block_draw_x, remove_block_draw_x, block_draw_y, map_max_y);

			}
			else if (block_draw_x < this->_before_block_draw_x) {
				// 描画削除するX座標を取得
				int remove_block_draw_x = this->_before_block_draw_x + (int)floor((double)draw_block_width / 2) - check_x - this->_map_outer_size_x;
				// 描画追加するX座標を取得
				int add_block_draw_x = this->_before_block_draw_x - (int)floor((double)draw_block_width / 2) - 1 - check_x + this->_map_outer_size_x;

				this->reviewGroundBlockX(add_block_draw_x, remove_block_draw_x, block_draw_y, map_max_y);
			}
		}

		for (int check_y = 0; check_y < draw_num_y; check_y++) {
			if (block_draw_y > this->_before_block_draw_y) {
				// 描画削除するY座標を取得
				int remove_block_draw_y = this->_before_block_draw_y - (int)floor((double)draw_block_height / 2) + check_y + this->_map_outer_size_y;
				// 描画追加するY座標を取得
				int add_block_draw_y = this->_before_block_draw_y + (int)floor((double)draw_block_height / 2) + 1 + check_y - this->_map_outer_size_y;

				this->reviewGroundBlockY(add_block_draw_y, remove_block_draw_y, block_draw_x, map_max_x);

			}
			else if (block_draw_y < this->_before_block_draw_y) {
				// 描画削除するY座標を取得
				int remove_block_draw_y = this->_before_block_draw_y + (int)floor((double)draw_block_height / 2) - check_y - this->_map_outer_size_y;
				// 描画追加するY座標を取得
				int add_block_draw_y = this->_before_block_draw_y - (int)floor((double)draw_block_height / 2) - 1 - check_y + this->_map_outer_size_y;

				this->reviewGroundBlockY(add_block_draw_y, remove_block_draw_y, block_draw_x, map_max_x);
			}
		}
	}

	//*/

	this->_before_block_draw_x = block_draw_x;
	this->_before_block_draw_y = block_draw_y;
	
}
void MapGroundList::reviewGroundBlockX(int add_block_draw_x, int remove_block_draw_x, int block_draw_y, int map_max_y) {
	int draw_block_height = (int)ceil((double)GAME_HEIGHT / (double)MAP_BLOCK_HEIGHT);
	int map_draw_size_y = (draw_block_height / 2) - this->_map_outer_size_y;

	for (int y = 0; y < 1 + (map_draw_size_y * 2); y++) {
		int remove_block = block_draw_y + y - map_draw_size_y;

		// 描画追加処理
		
		if (this->_ground_obj_list[add_block_draw_x][remove_block] != nullptr  &&
			this->_map_draw_list[add_block_draw_x][remove_block] == false) {
		

			this->_ground_sprite_list->addChild(this->_ground_obj_list[add_block_draw_x][remove_block]);
			this->_map_draw_list[add_block_draw_x][remove_block] = true;
		}

	
		if (remove_block >= map_max_y) {
			continue;
		}

		// 左側のブロックを削除
		if (this->_ground_obj_list[remove_block_draw_x][remove_block] != nullptr  &&
			this->_map_draw_list[remove_block_draw_x][remove_block] == true) {

			this->_ground_sprite_list->removeChild(this->_ground_obj_list[remove_block_draw_x][remove_block], true);
			this->_map_draw_list[remove_block_draw_x][remove_block] = false;
		}

		// 描画追加処理
		/*
		if (this->_ground_obj_list.ContainsKey(add_block_draw_x) == true &&
		this->_ground_obj_list[add_block_draw_x].ContainsKey(remove_block) == true &&
		this->_map_draw_list.ContainsKey(add_block_draw_x) == true &&
		this->_map_draw_list[add_block_draw_x].ContainsKey(remove_block) == true &&
		this->_map_draw_list[add_block_draw_x][remove_block] == false) {


			this->_ground_sprite_list.AddChild(this->_ground_obj_list[add_block_draw_x][remove_block]);
			this->_map_draw_list[add_block_draw_x][remove_block] = true;
		}

		if (remove_block >= map_max_y) {
			continue;
		}

		// 左側のブロックを削除
		if (this->_ground_obj_list.ContainsKey(remove_block_draw_x) == true &&
		this->_ground_obj_list[remove_block_draw_x].ContainsKey(remove_block) == true &&
		this->_map_draw_list.ContainsKey(remove_block_draw_x) == true &&
		this->_map_draw_list[remove_block_draw_x].ContainsKey(remove_block) == true &&
		this->_map_draw_list[remove_block_draw_x][remove_block] == true) {

			this->_ground_sprite_list.RemoveChild(this->_ground_obj_list[remove_block_draw_x][remove_block], true);
			this->_map_draw_list[remove_block_draw_x][remove_block] = false;
		}

		//*/

	}
}
void MapGroundList::reviewGroundBlockY(int add_block_draw_y, int remove_block_draw_y, int block_draw_x, int map_max_x) {
	int draw_block_width = (int)ceil((double)GAME_WIDTH / (double)MAP_BLOCK_WIDTH);
	int map_draw_size_x = (draw_block_width/2)-this->_map_outer_size_x;

	for (int x = 0; x < 1 + (map_draw_size_x * 2); x++) {

		int remove_block = block_draw_x + x - map_draw_size_x;

		if (this->_ground_obj_list[remove_block][add_block_draw_y] != nullptr  &&
			this->_map_draw_list[remove_block][add_block_draw_y] == false) {

			this->_ground_sprite_list->addChild(this->_ground_obj_list[remove_block][add_block_draw_y]);
			this->_map_draw_list[remove_block][add_block_draw_y] = true;
		}

		if (this->_ground_obj_list[remove_block][add_block_draw_y] != nullptr  &&
			this->_map_draw_list[remove_block][add_block_draw_y] == true) {

			this->_ground_sprite_list->removeChild(this->_ground_obj_list[remove_block][remove_block_draw_y], true);
			this->_map_draw_list[remove_block][remove_block_draw_y] = false;
		}
	}
	/*
	int map_draw_size_x = 7 - this->_map_outer_size_x;
	for (int x = 0; x < 1 + (map_draw_size_x * 2); x++) {
		int remove_block = block_draw_x + x - map_draw_size_x;

		// 描画追加処理
		if (this->_ground_obj_list.ContainsKey(remove_block) == true &&
			this->_ground_obj_list[remove_block].ContainsKey(add_block_draw_y) == true &&
			this->_map_draw_list.ContainsKey(remove_block) == true &&
			this->_map_draw_list[remove_block].ContainsKey(add_block_draw_y) == true &&
			this->_map_draw_list[remove_block][add_block_draw_y] == false) {

			this->_ground_sprite_list.AddChild(this->_ground_obj_list[remove_block][add_block_draw_y]);
			this->_map_draw_list[remove_block][add_block_draw_y] = true;
		}
				
		if (remove_block >= map_max_x) {
			continue;	
		}
	
		// 左側のブロックを削除
		if (this->_ground_obj_list.ContainsKey(remove_block) == true &&
			this->_ground_obj_list[remove_block].ContainsKey(remove_block_draw_y) == true &&
			this->_map_draw_list.ContainsKey(remove_block) == true &&
			this->_map_draw_list[remove_block].ContainsKey(remove_block_draw_y) == true &&
			this->_map_draw_list[remove_block][remove_block_draw_y] == true) {

			this->_ground_sprite_list.RemoveChild(this->_ground_obj_list[remove_block][remove_block_draw_y], true);

			this->_map_draw_list[remove_block][remove_block_draw_y] = false;
		}
	}
	*/
}
void MapGroundList::setCharaPoint() {
	//*
	int map_width = RandomDungeonSetting::getDungeonWidth();
	int map_height = RandomDungeonSetting::getDungeonHeight();
			
	int room_block_count = 0;
	for (int x = 0; x < map_width; x++) {
		for (int y=0; y < map_height; y++) {
					
			if (this->_map_data[x][y] == 2) {
				room_block_count++;
			}
		}
	}
			
	Random* rand_obj = new Random();
			
	int chara_room_x = 0;
	int chara_room_y = 0;
	int chara_room_num = rand_obj->getRandNum(room_block_count);
	int check_room_block_count = 0;
			
			
//			bool room_check_break_flag = false;
			
	for (int x = 0; x < map_width; x++) {
		for (int y=0; y < map_height; y++) {
					
			if (this->_map_data[x][y] == 2) {
				//Debug.WriteLine("check :"+ x +":"+ y);
				if (chara_room_num == check_room_block_count) {
					chara_room_x = x;
					chara_room_y = y;
							
							
					// test
							
					if (SET_MAP_MODE == 1) {
						chara_room_x = 1;
						chara_room_y = 1;
					}
							
					//Debug.WriteLine("set :"+ chara_room_x +":"+ chara_room_y);
					double chara_x = 64 * chara_room_x + (64 /2);
					double chara_y = (64 * chara_room_y - (64 /2)) * (-1);
							
					this->_player_obj->setDrawX(chara_x);
					this->_player_obj->setDrawY(chara_y);
					return;
				} else {
					check_room_block_count++;
				}
			}
		}
	}
	
	// */
}
std::unordered_map<int, std::unordered_map<int, int>> MapGroundList::getMapData() {
	return this->_map_data;
}