#include <math.h>
#include <random>
#include "RandomDungeon.h"
#include "RandomDungeonSetting.h"
#include "../../Random.h"
#include "randomRoadType.h"
#include "RandomDungeonRoom.h"

RandomDungeon::RandomDungeon() {

	//this->_map_data = new int[RandomDungeonSetting::getDungeonWidth(), RandomDungeonSetting::getDungeonHeight()];

	int dungeon_width = RandomDungeonSetting::getDungeonWidth();
	int dungeon_height = RandomDungeonSetting::getDungeonHeight();
	this->_rand_obj = new Random();

	switch (RandomDungeonSetting::_MAP_CREATE_TYPE) {
	case 1:
		// 部屋分割法
		this->DungeonCreateRogelike(dungeon_width, dungeon_height);

		break;
	case 2:
		// オリジナル
		this->DungeonCreateOriginal(dungeon_width, dungeon_height);
		break;
	}
}

void RandomDungeon::DungeonCreateRogelike(int dungeon_width, int dungeon_height) {
	// まずは配列の初期化
	for (int x = 0; x < dungeon_width; x++) {
		for (int y = 0; y < dungeon_height; y++) {
			this->_map_data[x][y] = 1;
		}
	}

	//ceil((double)(RandomDungeonSetting::_ROAD_WIDTH / 2));

	int map_frame_size = (int)(ceil((double)(RandomDungeonSetting::_ROAD_WIDTH / 2)) + RandomDungeonSetting::_ROOM_FRAME_SIZE);

	// 1部屋の最大サイズ = 1MAPの大きさ - (((道幅/2)+壁ブロック分)*2)
	int room_width_max = RandomDungeonSetting::_DUNGEON_MAP_X - (map_frame_size * 2) - (RandomDungeonSetting::_ROAD_WIDTH + RandomDungeonSetting::_ROOM_FRAME_SIZE);
	if (room_width_max < 0) {
		room_width_max = 0;
	}
	int room_height_max = RandomDungeonSetting::_DUNGEON_MAP_Y - (map_frame_size * 2) - (RandomDungeonSetting::_ROAD_WIDTH + RandomDungeonSetting::_ROOM_FRAME_SIZE);
	if (room_height_max < 0) {
		room_height_max = 0;
	}
	//Dictionary<int, Dictionary<int, RandomDungeonRoom>> map_rooms_list = new Dictionary<int, Dictionary<int, RandomDungeonRoom>>();
	std::unordered_map<int, std::unordered_map<int, RandomDungeonRoom*>> map_rooms_list;

	// マップの各部屋を作成
	for (int x = 0; x < RandomDungeonSetting::_DUNGEON_BLOCK_X; x++) {
		/*
		if (map_rooms_list.find(x) == map_rooms_list.end()) {
			map_rooms_list[x] = new std::unordered_map<int, RandomDungeonRoom>::;
		}
		//*/
		for (int y = 0; y < RandomDungeonSetting::_DUNGEON_BLOCK_Y; y++) {
			map_rooms_list[x][y] = new RandomDungeonRoom(room_width_max, room_height_max, RandomDungeonSetting::_ROAD_WIDTH, RandomDungeonSetting::_DUNGEON_MAP_X, RandomDungeonSetting::_DUNGEON_MAP_Y, map_frame_size, this->_rand_obj);
			map_rooms_list[x][y]->setDungeonRoad(x, y, RandomDungeonSetting::_DUNGEON_BLOCK_X, RandomDungeonSetting::_DUNGEON_BLOCK_Y);
			//map_rooms_list[x][y]->writeDebug();

		}
	}

	// マップをデータに展開する
	// マップの各部屋を作成
	for (int x = 0; x < RandomDungeonSetting::_DUNGEON_BLOCK_X; x++) {
		for (int y = 0; y < RandomDungeonSetting::_DUNGEON_BLOCK_Y; y++) {
			int map_base_x = x * RandomDungeonSetting::_DUNGEON_MAP_X;
			int map_base_y = y * RandomDungeonSetting::_DUNGEON_MAP_Y;

			std::unordered_map<int, std::unordered_map<int, int>> room_data = map_rooms_list[x][y]->getRoomData();

			// 通路をつなげる
			// 右と下だけチェックして、お互いにつなげる
			for (int i = 0; i < 2; i++) {
				bool next_flag = false;
				//						int join_point_x = -1;
				//						int join_point_y = -1;
				switch (i) {
				case 0: // right
					if (x >= RandomDungeonSetting::_DUNGEON_BLOCK_X - 1) {
						next_flag = true;
					}
					else {
						//Debug.WriteLine("map_block_point x:"+(x + 1)+" y:"+y+" next block left:"+map_rooms_list[x + 1][y]->getRoadPositionLeft());
						map_rooms_list[x][y]->joinRoad(randomRoadType::right, map_rooms_list[x + 1][y]->getRoadPositionLeft());
						map_rooms_list[x + 1][y]->joinRoad(randomRoadType::left, map_rooms_list[x][y]->getRoadPositionRight());
					}
					break;
				case 1: // bottom
					if (y >= RandomDungeonSetting::_DUNGEON_BLOCK_Y - 1) {
						next_flag = true;
					}
					else {
						map_rooms_list[x][y]->joinRoad(randomRoadType::bottom, map_rooms_list[x][y + 1]->getRoadPositionTop());
						map_rooms_list[x][y + 1]->joinRoad(randomRoadType::top, map_rooms_list[x][y]->getRoadPositionBottom());
					}
					break;
				}

				if (next_flag == true) {
					continue;
				}
			}

			for (int room_x = 0; room_x < RandomDungeonSetting::_DUNGEON_MAP_X; room_x++) {
				for (int room_y = 0; room_y < RandomDungeonSetting::_DUNGEON_MAP_Y; room_y++) {
					int map_access_x = map_base_x + room_x;
					int map_access_y = map_base_y + room_y;



					this->_map_data[map_access_x, map_access_y] = room_data[room_x, room_y];
				}
			}

			//this->_map_data[,]
		}
	}
}

void RandomDungeon::DungeonCreateOriginal(int dungeon_width, int dungeon_height) {

	// まずは配列の初期化

	for (int x = 0; x < dungeon_width; x++) {
		for (int y = 0; y < dungeon_height; y++) {
			if (x <= 0 || x >= dungeon_width - 1 ||
				y <= 0 || y >= dungeon_height - 1) {
				this->_map_data[x][y] = 5;
			}
			else {
				this->_map_data[x][y] = 1;
			}

		}
	}
	// 道幅による補正
	int frame_num = RandomDungeonSetting::_MAP_FRAME_NUM;	//外枠の壁幅

	int road_top_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;
	int road_bottom_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;
	int road_left_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;
	int road_right_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;

	//				int block_core_width = (dungeon_width - road_left_correct - road_right_correct);
	//				int block_core_height = (dungeon_height - road_top_correct - road_bottom_correct);
	int block_core_width = RandomDungeonSetting::_MAP_WIDTH;
	int block_core_height = RandomDungeonSetting::_MAP_HEIGHT;
	int block_core_count = 0;
	int block_core_max = (block_core_width)* (block_core_height);

	int room_max = RandomDungeonSetting::_ROOM_MAX;


	//	Debug.WriteLine("[RandomDungeon]correct "+road_top_correct+"/"+road_bottom_correct+"/"+road_left_correct+"/"+road_right_correct+"/");

	int map_all_block_num = this->getMapBlockNum();

	int first_core_x = -1;
	int first_core_y = -1;
	// 最大部屋数分、部屋の準備を行う
	for (int room_num = 0; room_num < room_max; room_num++) {

		int free_core_num = this->getMapDataFreeNum();
		if (free_core_num <= 0) {
			break;
		}

		int room_core = this->_rand_obj->getRandNum(free_core_num);

		// 部屋の基準位置の初期化
		int room_core_x = -1;
		int room_core_y = -1;
		//	Debug.WriteLine("[RandomDungeon]set core num"+room_core);
		// 全ブロックを検索

		int block_base_count = 0;
		for (int block_base_count = 0; block_base_count < map_all_block_num; block_base_count++) {
		//while (block_base_count >= free_core_num) {
			
			int check_room_core_x = (block_base_count % block_core_width) + RandomDungeonSetting::_MAP_FRAME_NUM;// + road_left_correct;
			int check_room_core_y = (int)ceil((double)(block_base_count / block_core_width)) + RandomDungeonSetting::_MAP_FRAME_NUM;// + road_top_correct;						

			// 検索場所が壁データである場合
			if (this->_map_data[check_room_core_x][check_room_core_y] == 1) {

				// 配置場所についたら、検索処理終了
				if (room_core <= 0) {

					// 部屋の基準位置の決定
					//room_core_x = block_base_count % dungeon_width;
					//room_core_y = (int)ceil((double)(block_base_count / dungeon_width));
					room_core_x = check_room_core_x;
					room_core_y = check_room_core_y;

					/*
					if (block_core_count == 0) {
					room_core_x = 10 - 7;
					room_core_y = 10 + 7;
					} else if (block_core_count == 1) {
					room_core_x = 10;
					room_core_y = 10;
					}
					*/
					//this->_map_data[room_core_x, room_core_y] = 2;
					//	Debug.WriteLine("[RandomDungeon]set Room Core"+room_core_x+"."+room_core_y);

					break;
				}
				// コアの位置を減らす
				room_core--;
			}
		}
		//Debug.WriteLine("[RandomDungeon]room_core nokori " + room_core);
		// 部屋を展開する
		int set_room_min = RandomDungeonSetting::_ROOM_MIN;
		if (block_core_count <= set_room_min) {


			if (block_core_count == 0) {
				//Debug.WriteLine("[RandomDungeon]create first room " + room_core_x + "/" + room_core_y);
				this->setRoomExpansion(room_core_x, room_core_y);
				this->setRoadFirstRoom(room_core_x, room_core_y);
				first_core_x = room_core_x;
				first_core_y = room_core_y;
				//this->_map_data[room_core_x, room_core_y] = 2;
				this->setMapData(room_core_x, room_core_y, 2);


			}
			else {
				if (room_core_x >= 0 && room_core_y >= 0) {
					//Debug.WriteLine("[RandomDungeon]check create min room " + room_core_x + "/" + room_core_y + " block:" + this->_map_data[room_core_x, room_core_y]);
					if (this->setRoadSearchMin(room_core_x, room_core_y, first_core_x, first_core_y) == true) {
						//Debug.WriteLine("[RandomDungeon]create min room " + room_core_x + "/" + room_core_y);
						//this->setRoomExpansion(room_core_x, room_core_y);
						this->setMapData(room_core_x, room_core_y, 2);

					}
				}

			}
		}
		else {
			if (room_core_x >= 0 && room_core_y >= 0) {
				//Debug.WriteLine("[RandomDungeon]check create rand room " + room_core_x + "/" + room_core_y + " block:" + this->_map_data[room_core_x, room_core_y]);
				if (this->checkRoadCreateRandom(room_core_x, room_core_y) == true) {
					this->setRoomExpansion(room_core_x, room_core_y);
					//this->_map_data[room_core_x, room_core_y] = 5;
					this->setMapData(room_core_x, room_core_y, 5);
					//Debug.WriteLine("[RandomDungeon]create rand room " + room_core_x + "/" + room_core_y);
					
				}
			}
		}

		/*
		if (room_max > 1 && block_core_count == 0) {

		}
		// */

		// 部屋のブロック数を増やす
		// @TODO 部屋のコア分のみしか追加してないので、部屋の広さ分、引いた通路分を変更すること
		block_core_count++;
		//block_core_count+=9;

	}
}

// マス指定による、部屋を作成
void RandomDungeon::setRoomExpansion(int room_core_x, int room_core_y) {
	int map_width = RandomDungeonSetting::getDungeonWidth();
	int map_height = RandomDungeonSetting::getDungeonHeight();

	int room_width_randon_num = RandomDungeonSetting::_ROOM_MAX_WIDTH - RandomDungeonSetting::_ROOM_MIN_WIDTH;
	int room_height_randon_num = RandomDungeonSetting::_ROOM_MAX_HEIGHT - RandomDungeonSetting::_ROOM_MIN_HEIGHT;
	//Debug.WriteLine("[RandomDungeon]setRoomExpansion random max size : "+ room_width_randon_num +"/"+ room_height_randon_num);			

	Random* rand_obj = this->_rand_obj;
	int room_width = RandomDungeonSetting::_ROOM_MIN_WIDTH + rand_obj->getRandNum(room_width_randon_num);
	int room_height = RandomDungeonSetting::_ROOM_MIN_HEIGHT + rand_obj->getRandNum(room_height_randon_num);


	//Debug.WriteLine("[RandomDungeon]setRoomExpansion room size : "+ room_width +"/"+ room_height);			
	int room_start_x = (int)floor((double)(room_width / 2));
	int room_start_y = (int)floor((double)(room_height / 2));


	// 部屋の横分
	for (int x = 0; x < room_width; x++) {

		int expansion_x = room_core_x - room_start_x + x;

		// マップ外の場合は何も処理しない
		if (expansion_x < 0 || expansion_x >= map_width) {
			continue;
		}

		// 部屋の縦分
		for (int y = 0; y < room_height; y++) {

			int expansion_y = room_core_y - room_start_y + y;
			// マップ外の場合は何も処理しない
			if (expansion_y < 0 || expansion_y >= map_height) {
				continue;
			}

			// 壁の場合のみ書き換え
			if (this->_map_data[expansion_x][expansion_y] == 1 || this->_map_data[expansion_x][expansion_y] == 4) {
				//	this->_map_data[expansion_x, expansion_y] = 3;
				this->setMapData(expansion_x, expansion_y, 3);
			}
		}
	}
}

// マス指定による、道を作れるか検索
void RandomDungeon::setRoadFirstRoom(int room_core_x, int room_core_y) {
	Random* rand_obj = this->_rand_obj;
	
	//this->setRoadExpansion(room_core_x, room_core_y, rand_obj->getRandNum(4), rand_obj->getRandNum(10) + 10);
	this->setRoadExpansion(room_core_x, room_core_y, 0, rand_obj->getRandNum(20) + 10);
	this->setRoadExpansion(room_core_x, room_core_y, 1, rand_obj->getRandNum(20) + 10);
	this->setRoadExpansion(room_core_x, room_core_y, 2, rand_obj->getRandNum(20) + 10);
	this->setRoadExpansion(room_core_x, room_core_y, 3, rand_obj->getRandNum(20) + 10);
	/*
	this->setRoadExpansion(room_core_x, room_core_y, 0, rand_obj->getRandNum(10) + 20);
	this->setRoadExpansion(room_core_x, room_core_y, 1, rand_obj->getRandNum(10) + 20);
	this->setRoadExpansion(room_core_x, room_core_y, 2, rand_obj->getRandNum(10) + 20);
	this->setRoadExpansion(room_core_x, room_core_y, 3, rand_obj->getRandNum(10) + 20);
	*/
}

// マス指定による、道を作れるか検索(簡易版
bool RandomDungeon::setRoadSearchMin(int room_core_x, int room_core_y, int first_core_x, int first_core_y) {
	Random* rand_obj = this->_rand_obj;
	int road_num = rand_obj->getRandNum(10) + 10;
	// XもしくはY軸が初期部屋の中心地と合っている場合
	if (room_core_x == first_core_x) {
		if (room_core_y > first_core_y) {
			// 確定、上へ道を作る
			this->setRoadExpansion(room_core_x, room_core_y, 0, road_num);
		}
		else if (room_core_y < first_core_y) {
			// 確定、下へ道を作る
			this->setRoadExpansion(room_core_x, room_core_y, 2, road_num);
		}
	} else if (room_core_y == first_core_y) {
		if (room_core_x > first_core_x) {
			// 確定、右へ道を作る
			this->setRoadExpansion(room_core_x, room_core_y, 3, road_num);
		}
		else if (room_core_x < first_core_x) {
			// 確定、左へ道を作る
			this->setRoadExpansion(room_core_x, room_core_y, 1, road_num);
		}
	} else {
		// 上下左右に初期部屋中心地がないので、検索をかける

		int road_type = -1;
		int sub_road_type = -1;
		int rand_num = rand_obj->getRandNum(2);
		//	Debug.WriteLine("[RandomDungeon]setRoadSearchMin rand_num "+rand_num);
		if (room_core_x > first_core_x) {
			// 左側
			if (room_core_y > first_core_y) {
				// 左上に部屋があるので別部屋まで探索する
				road_type = 3;
				sub_road_type = 0;

				// 左か上、どちらから探索するかランダムで決める
				if (rand_num == 1) {
					road_type = 0;
					sub_road_type = 3;
				}

			} else if (room_core_y < first_core_y) {
				// 左下に部屋があるので別部屋まで探索する
				road_type = 3;
				sub_road_type = 2;

				// 左か下、どちらから探索するかランダムで決める
				if (rand_num == 1) {
					road_type = 2;
					sub_road_type = 3;
				}
			}
		} else if (room_core_x < first_core_x) {
			// 右側
			if (room_core_y > first_core_y) {
				// 右上に部屋があるので別部屋まで探索する
				road_type = 1;
				sub_road_type = 0;

				// 右か上、どちらから探索するかランダムで決める
				if (rand_num == 1) {
					road_type = 0;
					sub_road_type = 1;
				}

			} else if (room_core_y < first_core_y) {
				// 右下に部屋があるので別部屋まで探索する
				road_type = 1;
				sub_road_type = 2;

				// 右か下、どちらから探索するかランダムで決める
				if (rand_num == 1) {
					road_type = 2;
					sub_road_type = 1;
				}

			}
		}

		if (road_type != -1 && sub_road_type != -1) {
			//		this->checkRoadCreate(room_core_x, room_core_y, first_core_x, first_core_y, road_type, sub_road_type);
			if (this->checkRoadCreateMini(room_core_x, room_core_y, first_core_x, first_core_y, road_type) == true) {
				return true;
			}
		}
	}
	return false;
}

//	通路を作成できるかチェック
//	部屋の中心地から通路を延ばし、通路が曲がって別の部屋や通路に繋がるかチェック
void RandomDungeon::checkRoadCreate(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type, int sub_road_type) {
	//int[, ] map_search_data = new int[RandomDungeonSetting::getDungeonWidth(), RandomDungeonSetting::getDungeonHeight()];
	std::unordered_map<int, std::unordered_map<int, int>> map_search_data;
	// 配列のコピー
	for (int copy_x = 0; copy_x < RandomDungeonSetting::getDungeonWidth(); copy_x++) {
		for (int copy_y = 0; copy_y < RandomDungeonSetting::getDungeonHeight(); copy_y++) {
			map_search_data[copy_x][copy_y] = this->_map_data[copy_x][copy_y];

		}
	}
	//	int [][] hoge;


	//map_search_data.CopyTo(this->_map_data, 0);
	//int[,] map_search_data = this->_map_data;



	int turn_point_x = -1;
	int turn_point_y = -1;
	int turn_next_road_num = -1;

	//map_search_data.CopyTo(this->_map_data, 0)
	int expansion_x = room_core_x;
	int expansion_y = room_core_y;


	// メインと曲がった後のサブの通路長さを取得 -------------
	int main_load_search_num = 0;
	int sub_load_search_num = 0;

	switch (road_type) {
	case 0:
		main_load_search_num = room_core_y - first_core_y;
		break;
	case 2:
		//	expansion_y = room_core_y - i;
		main_load_search_num = first_core_y - room_core_y;
		break;
	case 1:
		main_load_search_num = first_core_x - room_core_x;
		break;
	case 3:
		//	expansion_x = room_core_x + i;
		main_load_search_num = room_core_x - first_core_x;
		break;
	}

	switch (sub_road_type) {
	case 0:
		sub_load_search_num = room_core_y - first_core_y;
		break;
	case 2:
		//	expansion_y = room_core_y - i;
		sub_load_search_num = first_core_y - room_core_y;
		break;
	case 1:
		sub_load_search_num = first_core_x - room_core_x;
		break;
	case 3:
		//	expansion_x = room_core_x + i;
		sub_load_search_num = room_core_x - first_core_x;
		break;
	}

	main_load_search_num += 1;
	sub_load_search_num += 1;
	//	Debug.WriteLine("[RandomDungeon]get road size "+main_load_search_num+"/"+sub_load_search_num+"");
	//	Debug.WriteLine("[RandomDungeon]---------------------------");

	int main_load_num = 0;
	int sub_load_num = 0;
	// 探す
	for (int i = 0; i < main_load_search_num; i++) {

		switch (road_type) {
		case 0:
			//expansion_y--;
			expansion_y = room_core_y - i;
			expansion_x = room_core_x;
			break;
		case 1:
			//expansion_x++;
			expansion_x = room_core_x + i;
			expansion_y = room_core_y;
			break;
		case 2:
			//expansion_y++;
			expansion_y = room_core_y + i;
			expansion_x = room_core_x;
			break;
		case 3:
			//expansion_x--;
			expansion_x = room_core_x - i;
			expansion_y = room_core_y;
			break;
		}

		turn_point_x = expansion_x;
		turn_point_y = expansion_y;

		for (int j = 0; j < sub_load_search_num; j++) {

			switch (sub_road_type) {
			case 0:
				//expansion_y--;
				expansion_y = room_core_y - j;
				break;
			case 1:
				//expansion_x++;
				expansion_x = room_core_x + j;
				break;
			case 2:
				//expansion_y++;
				expansion_y = room_core_y + j;
				break;
			case 3:
				//expansion_x--;
				expansion_x = room_core_x - j;
				break;
			}

			//	Debug.WriteLine("[RandomDungeon]search "+expansion_x+":"+expansion_y+"	("+i+":"+j+")");


			if (expansion_x < 0 || expansion_x >= RandomDungeonSetting::getDungeonWidth() ||
				expansion_y < 0 || expansion_y >= RandomDungeonSetting::getDungeonHeight()) {

				break;
			}

			if (map_search_data[expansion_x][expansion_y] == 5) {
				break;
			}

			if (map_search_data[expansion_x][expansion_y] == 1) {
				map_search_data[expansion_x][expansion_y] = 4;
			}
			else {
				//	Debug.WriteLine("[RandomDungeon]search break"+expansion_x+":"+expansion_y+"	("+i+":"+j+")");
				//						turn_next_road_num = j;
				sub_load_num = j;
				break;
			}

		}
		if (sub_load_num > 0) {
			main_load_num = i;
			break;
		}

		//break;
	}

	if (main_load_num < 0 || sub_load_num < 0) {
		return;
	}
	// 道を作る
	// メインの道の方向によって補正値が微妙にあるので処理分ける

	switch (road_type) {
	case 0:
		if (main_load_num - 1 < 0) {
			this->setRoadExpansion(turn_point_x, turn_point_y - 2, sub_road_type, sub_load_num);
		}
		else {
			this->setRoadExpansion(room_core_x, room_core_y, road_type, main_load_num - 1);
			this->setRoadExpansion(turn_point_x, turn_point_y - 1, sub_road_type, sub_load_num);
		}
		break;
	case 1:
		this->setRoadExpansion(room_core_x, room_core_y, road_type, main_load_num - 1);
		this->setRoadExpansion(turn_point_x + 1, turn_point_y, sub_road_type, sub_load_num);
		break;
	case 2:
		if (main_load_num - 1 < 0) {
			this->setRoadExpansion(turn_point_x, turn_point_y, sub_road_type, sub_load_num);
		}
		else {
			this->setRoadExpansion(room_core_x, room_core_y, road_type, main_load_num - 1);
			this->setRoadExpansion(turn_point_x, turn_point_y, sub_road_type, sub_load_num);
		}
		break;
	case 3:
		if (main_load_num - 1 < 0) {
			this->setRoadExpansion(turn_point_x - 1, turn_point_y, sub_road_type, sub_load_num);
		}
		else {
			this->setRoadExpansion(room_core_x, room_core_y, road_type, main_load_num - 1);
			this->setRoadExpansion(turn_point_x - 1, turn_point_y, sub_road_type, sub_load_num);
		}
		break;
	}
}

//	通路を作成できるかチェック
//	簡易版なので部屋の中心地から通路を延ばして別の部屋や通路に繋がるかチェック
bool RandomDungeon::checkRoadCreateMini(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type) {
	//int[, ] map_search_data = new int[RandomDungeonSetting::getDungeonWidth(), RandomDungeonSetting::getDungeonHeight()];
	std::unordered_map<int, std::unordered_map<int, int>>map_search_data;
	// 配列のコピー
	for (int copy_x = 0; copy_x < RandomDungeonSetting::getDungeonWidth(); copy_x++) {
		for (int copy_y = 0; copy_y < RandomDungeonSetting::getDungeonHeight(); copy_y++) {
			map_search_data[copy_x][copy_y] = this->_map_data[copy_x][copy_y];

		}
	}
	// 通路長さを取得 -------------
	int main_load_search_num = 0;


	switch (road_type) {
	case 0:
		main_load_search_num = room_core_y - first_core_y;
		break;
	case 2:
		//	expansion_y = room_core_y - i;
		main_load_search_num = first_core_y - room_core_y;
		break;
	case 1:
		main_load_search_num = first_core_x - room_core_x;
		break;
	case 3:
		//	expansion_x = room_core_x + i;
		main_load_search_num = room_core_x - first_core_x;
		break;
	}
	main_load_search_num += 1;

	bool ret_flag = this->checkRoadCreateMiniDetail(room_core_x, room_core_y, main_load_search_num, road_type, map_search_data);

	return ret_flag;
}

// 通路作成チェック。ランダム版
bool RandomDungeon::checkRoadCreateRandom(int room_core_x, int room_core_y) {
	//int[, ] map_search_data = new int[RandomDungeonSetting::getDungeonWidth(), RandomDungeonSetting::getDungeonHeight()];
	std::unordered_map<int, std::unordered_map<int, int>> map_search_data;
	// 配列のコピー
	for (int copy_x = 0; copy_x < RandomDungeonSetting::getDungeonWidth(); copy_x++) {
		for (int copy_y = 0; copy_y < RandomDungeonSetting::getDungeonHeight(); copy_y++) {
			map_search_data[copy_x][copy_y] = this->_map_data[copy_x][copy_y];

		}
	}
	Random* rand_obj = this->_rand_obj;
	int main_load_search_num = 20;
	int road_type = rand_obj->getRandNum(4);

	bool ret_flag = this->checkRoadCreateMiniDetail(room_core_x, room_core_y, main_load_search_num, road_type, map_search_data);
	return ret_flag;
}

// 通路作成チェック。ランダム版の詳細処理
bool RandomDungeon::checkRoadCreateMiniDetail(int room_core_x, int room_core_y, int main_load_search_num, int road_type, std::unordered_map<int, std::unordered_map<int, int>>map_search_data) {
	int expansion_x = room_core_x;
	int expansion_y = room_core_y;

	bool search_start = false;


	Random* rand_obj = this->_rand_obj;
	// 探す
	for (int i = 0; i < main_load_search_num; i++) {
		switch (road_type) {
		case 0:
			//expansion_y--;
			expansion_y = room_core_y - i;
			expansion_x = room_core_x;
			break;
		case 1:
			//expansion_x++;
			expansion_x = room_core_x + i;
			expansion_y = room_core_y;
			break;
		case 2:
			//expansion_y++;
			expansion_y = room_core_y + i;
			expansion_x = room_core_x;
			break;
		case 3:
			//expansion_x--;
			expansion_x = room_core_x - i;
			expansion_y = room_core_y;
			break;
		}

		if (map_search_data[expansion_x][expansion_y] == 5) {
			break;
		}
		else if (map_search_data[expansion_x][expansion_y] == 1) {
			map_search_data[expansion_x][expansion_y] = 4;
			search_start = true;
		}
		else {
			if (search_start == true) {
				//	Debug.WriteLine("[DandomDngeon]checkRoadCreateMini search ok");
				this->setRoomExpansion(room_core_x, room_core_y);
				this->setRoadExpansion(room_core_x, room_core_y, road_type, i);
				return true;
			}
		}
	}
	return false;
}

// 通路を作成
void RandomDungeon::setRoadExpansion(int room_core_x, int room_core_y, int road_type, int road_num) {
	int map_width = RandomDungeonSetting::getDungeonWidth();
	int map_height = RandomDungeonSetting::getDungeonHeight();

	// 道幅による補正
	int road_top_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);
	int road_bottom_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);
	int road_left_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);
	int road_right_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);

	// typeから、伸ばす方向を決める
	int road_x = 0;
	int road_y = 0;

	int road_correct = 0;
	switch (road_type) {
	case 0:	// 上
		road_y = -1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_HEIGHT;
		break;
	case 1:	// 右
		road_x = 1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_WIDTH;
		break;
	case 2:	// 下
		road_y = 1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_HEIGHT;
		break;
	case 3:	// 左
		road_x = -1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_WIDTH;
		break;
	}

	// 道を引く
	for (int i = 0; i < (road_num + road_correct); i++) {
		int expansion_x = room_core_x + (i * road_x);
		int expansion_y = room_core_y + (i * road_y);

		// マップ外の場合は何も処理しない
		if (expansion_x < 0 || expansion_x >= map_width ||
			expansion_y < 0 || expansion_y >= map_height) {
			break;
		}

		if (this->_map_data[expansion_x][expansion_y] == 1) {
			//this->_map_data[expansion_x, expansion_y] = 4;
			this->setMapData(expansion_x, expansion_y, 4);

			// マップ幅分広げる
			switch (road_type) {
			case 0:	// 上
			case 2:	// 下

				for (int j = 0; j < RandomDungeonSetting::_ROAD_WIDTH; j++) {

					int load_expansion_x = (expansion_x - road_left_correct + j);
					// マップ外の場合は何も処理しない
					if (load_expansion_x < 0 || load_expansion_x >= map_width) {
						continue;
					}
					if (this->_map_data[load_expansion_x][expansion_y] == 1) {
						//this->_map_data[load_expansion_x, expansion_y] = 4;
						this->setMapData(load_expansion_x, expansion_y, 4);
					}
				}
				break;
			case 1:	// 右
			case 3:	// 左
				for (int j = 0; j < RandomDungeonSetting::_ROAD_WIDTH; j++) {

					int load_expansion_y = (expansion_y - road_top_correct + j);
					// マップ外の場合は何も処理しない
					if (load_expansion_y < 0 || load_expansion_y >= map_height) {
						continue;
					}
					if (this->_map_data[expansion_x][load_expansion_y] == 1) {
						//this->_map_data[expansion_x, load_expansion_y] = 4;
						this->setMapData(expansion_x, load_expansion_y, 4);
					}
				}
				break;
			}

		}
	}
}

void RandomDungeon::setMapData(int expansion_x, int expansion_y, int map_type) {
	if (expansion_x < RandomDungeonSetting::_MAP_FRAME_NUM ||
		expansion_x >= RandomDungeonSetting::getDungeonWidth() - RandomDungeonSetting::_MAP_FRAME_NUM ||
		expansion_y < RandomDungeonSetting::_MAP_FRAME_NUM ||
		expansion_y >= RandomDungeonSetting::getDungeonHeight() - RandomDungeonSetting::_MAP_FRAME_NUM) {
		return;
	}
	this->_map_data[expansion_x][expansion_y] = map_type;
}

std::unordered_map<int, std::unordered_map<int, int>> RandomDungeon::getMapData() {
	return this->_map_data;
}

int RandomDungeon::getMapDataFreeNum() {
	int count = 0;

//	int[int, int] hoge;

	for (int x = 0; x < RandomDungeonSetting::getDungeonWidth(); x++) {
		for (int y = 0; y < RandomDungeonSetting::getDungeonHeight(); y++) {
			if (this->_map_data[x][y] == 1) {

				count++;
			}
		}
	}
	
	return count;
}
int RandomDungeon::getMapBlockNum() {
	int count = 0;

	//	int[int, int] hoge;

	count = RandomDungeonSetting::getDungeonWidth() * RandomDungeonSetting::getDungeonHeight();

	return count;
}