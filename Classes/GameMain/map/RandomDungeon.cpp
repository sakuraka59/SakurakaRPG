#include <math.h>
#include <random>
#include "RandomDungeon.h"
#include "RandomDungeonSetting.h"
#include "../../Random.h"
#include "randomRoadType.h"
#include "RandomDungeonRoom.h"

RandomDungeon::RandomDungeon() {


	int dungeon_width = RandomDungeonSetting::getDungeonWidth();
	int dungeon_height = RandomDungeonSetting::getDungeonHeight();
	this->_rand_obj = new Random();

	switch (RandomDungeonSetting::_MAP_CREATE_TYPE) {
	case 1:
		// ���������@
		this->DungeonCreateRogelike(dungeon_width, dungeon_height);

		break;
	case 2:
		// �I���W�i��
		this->DungeonCreateOriginal(dungeon_width, dungeon_height);
		break;
	}
}

void RandomDungeon::DungeonCreateRogelike(int dungeon_width, int dungeon_height) {
	// �܂��͔z��̏�����
	for (int x = 0; x < dungeon_width; x++) {
		for (int y = 0; y < dungeon_height; y++) {
			this->_map_data[x][y] = 1;
			this->_map_ground_data[x][y] = 1;
		}
	}


	int map_frame_size = (int)(ceil((double)(RandomDungeonSetting::_ROAD_WIDTH / 2)) + RandomDungeonSetting::_ROOM_FRAME_SIZE);

	// 1�����̍ő�T�C�Y = 1MAP�̑傫�� - (((����/2)+�ǃu���b�N��)*2)
	int room_width_max = RandomDungeonSetting::_DUNGEON_MAP_X - (map_frame_size * 2) - (RandomDungeonSetting::_ROAD_WIDTH + RandomDungeonSetting::_ROOM_FRAME_SIZE);
	if (room_width_max < 0) {
		room_width_max = 0;
	}
	int room_height_max = RandomDungeonSetting::_DUNGEON_MAP_Y - (map_frame_size * 2) - (RandomDungeonSetting::_ROAD_WIDTH + RandomDungeonSetting::_ROOM_FRAME_SIZE);
	if (room_height_max < 0) {
		room_height_max = 0;
	}

	std::unordered_map<int, std::unordered_map<int, RandomDungeonRoom*>> map_rooms_list;

	// �}�b�v�̊e�������쐬
	for (int x = 0; x < RandomDungeonSetting::_DUNGEON_BLOCK_X; x++) {

		for (int y = 0; y < RandomDungeonSetting::_DUNGEON_BLOCK_Y; y++) {
			map_rooms_list[x][y] = new RandomDungeonRoom(room_width_max, room_height_max, RandomDungeonSetting::_ROAD_WIDTH, RandomDungeonSetting::_DUNGEON_MAP_X, RandomDungeonSetting::_DUNGEON_MAP_Y, map_frame_size, this->_rand_obj);
			map_rooms_list[x][y]->setDungeonRoad(x, y, RandomDungeonSetting::_DUNGEON_BLOCK_X, RandomDungeonSetting::_DUNGEON_BLOCK_Y);

		}
	}

	// �}�b�v���f�[�^�ɓW�J����
	// �}�b�v�̊e�������쐬
	for (int x = 0; x < RandomDungeonSetting::_DUNGEON_BLOCK_X; x++) {
		for (int y = 0; y < RandomDungeonSetting::_DUNGEON_BLOCK_Y; y++) {
			int map_base_x = x * RandomDungeonSetting::_DUNGEON_MAP_X;
			int map_base_y = y * RandomDungeonSetting::_DUNGEON_MAP_Y;

			std::unordered_map<int, std::unordered_map<int, int>> room_data = map_rooms_list[x][y]->getRoomData();

			// �ʘH���Ȃ���
			// �E�Ɖ������`�F�b�N���āA���݂��ɂȂ���
			for (int i = 0; i < 2; i++) {
				bool next_flag = false;

				switch (i) {
				case 0: // right
					if (x >= RandomDungeonSetting::_DUNGEON_BLOCK_X - 1) {
						next_flag = true;
					}
					else {

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
		}
	}
}

void RandomDungeon::DungeonCreateOriginal(int dungeon_width, int dungeon_height) {

	// �܂��͔z��̏�����

	for (int x = 0; x < dungeon_width; x++) {
		for (int y = 0; y < dungeon_height; y++) {
			if (x <= 0 || x >= dungeon_width - 1 ||
				y <= 0 || y >= dungeon_height - 1) {
				this->_map_data[x][y] = 5;
			}
			else {
				this->_map_data[x][y] = 1;
			}
			this->_map_ground_data[x][y] = 1;
		}
	}
	// �����ɂ��␳
	int frame_num = RandomDungeonSetting::_MAP_FRAME_NUM;	//�O�g�̕Ǖ�

	int road_top_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;
	int road_bottom_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;
	int road_left_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;
	int road_right_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2) + frame_num;

	int block_core_width = RandomDungeonSetting::_MAP_WIDTH;
	int block_core_height = RandomDungeonSetting::_MAP_HEIGHT;
	int block_core_count = 0;
	int block_core_max = (block_core_width)* (block_core_height);

	int room_max = RandomDungeonSetting::_ROOM_MAX;

	int map_all_block_num = this->getMapBlockNum();

	int first_core_x = -1;
	int first_core_y = -1;
	// �ő啔�������A�����̏������s��
	for (int room_num = 0; room_num < room_max; room_num++) {

		int free_core_num = this->getMapDataFreeNum();
		if (free_core_num <= 0) {
			break;
		}

		int room_core = this->_rand_obj->getRandNum(free_core_num);

		// �����̊�ʒu�̏�����
		int room_core_x = -1;
		int room_core_y = -1;

		// �S�u���b�N������
		int block_base_count = 0;
		for (int block_base_count = 0; block_base_count < map_all_block_num; block_base_count++) {
			
			int check_room_core_x = (block_base_count % block_core_width) + RandomDungeonSetting::_MAP_FRAME_NUM;// + road_left_correct;
			int check_room_core_y = (int)ceil((double)(block_base_count / block_core_width)) + RandomDungeonSetting::_MAP_FRAME_NUM;// + road_top_correct;						

			// �����ꏊ���ǃf�[�^�ł���ꍇ
			if (this->_map_data[check_room_core_x][check_room_core_y] == 1) {

				// �z�u�ꏊ�ɂ�����A���������I��
				if (room_core <= 0) {

					// �����̊�ʒu�̌���
					room_core_x = check_room_core_x;
					room_core_y = check_room_core_y;

					break;
				}
				// �R�A�̈ʒu�����炷
				room_core--;
			}
		}
		// ������W�J����
		int set_room_min = RandomDungeonSetting::_ROOM_MIN;
		if (block_core_count <= set_room_min) {


			if (block_core_count == 0) {
				this->setRoomExpansion(room_core_x, room_core_y);
				this->setRoadFirstRoom(room_core_x, room_core_y);
				first_core_x = room_core_x;
				first_core_y = room_core_y;

				this->setMapData(room_core_x, room_core_y, 2);


			}
			else {
				if (room_core_x >= 0 && room_core_y >= 0) {

					if (this->setRoadSearchMin(room_core_x, room_core_y, first_core_x, first_core_y) == true) {
						this->setMapData(room_core_x, room_core_y, 2);

					}
				}

			}
		}
		else {
			if (room_core_x >= 0 && room_core_y >= 0) {

				if (this->checkRoadCreateRandom(room_core_x, room_core_y) == true) {
					this->setRoomExpansion(room_core_x, room_core_y);

					this->setMapData(room_core_x, room_core_y, 5);
				}
			}
		}

		// �����̃u���b�N���𑝂₷
		// @TODO �����̃R�A���݂̂����ǉ����ĂȂ��̂ŁA�����̍L�����A�������ʘH����ύX���邱��
		block_core_count++;

	}
}

// �}�X�w��ɂ��A�������쐬
void RandomDungeon::setRoomExpansion(int room_core_x, int room_core_y) {
	int map_width = RandomDungeonSetting::getDungeonWidth();
	int map_height = RandomDungeonSetting::getDungeonHeight();

	int room_width_randon_num = RandomDungeonSetting::_ROOM_MAX_WIDTH - RandomDungeonSetting::_ROOM_MIN_WIDTH;
	int room_height_randon_num = RandomDungeonSetting::_ROOM_MAX_HEIGHT - RandomDungeonSetting::_ROOM_MIN_HEIGHT;

	Random* rand_obj = this->_rand_obj;
	int room_width = RandomDungeonSetting::_ROOM_MIN_WIDTH + rand_obj->getRandNum(room_width_randon_num);
	int room_height = RandomDungeonSetting::_ROOM_MIN_HEIGHT + rand_obj->getRandNum(room_height_randon_num);

	int room_start_x = (int)floor((double)(room_width / 2));
	int room_start_y = (int)floor((double)(room_height / 2));


	// �����̉���
	for (int x = 0; x < room_width; x++) {

		int expansion_x = room_core_x - room_start_x + x;

		// �}�b�v�O�̏ꍇ�͉����������Ȃ�
		if (expansion_x < 0 || expansion_x >= map_width) {
			continue;
		}

		// �����̏c��
		for (int y = 0; y < room_height; y++) {

			int expansion_y = room_core_y - room_start_y + y;
			// �}�b�v�O�̏ꍇ�͉����������Ȃ�
			if (expansion_y < 0 || expansion_y >= map_height) {
				continue;
			}

			// �ǂ̏ꍇ�̂ݏ�������
			if (this->_map_data[expansion_x][expansion_y] == 1 || this->_map_data[expansion_x][expansion_y] == 4) {

				this->setMapData(expansion_x, expansion_y, 3);
			}
		}
	}
}

// �}�X�w��ɂ��A�������邩����
void RandomDungeon::setRoadFirstRoom(int room_core_x, int room_core_y) {
	Random* rand_obj = this->_rand_obj;
	
	this->setRoadExpansion(room_core_x, room_core_y, 0, rand_obj->getRandNum(20) + 10);
	this->setRoadExpansion(room_core_x, room_core_y, 1, rand_obj->getRandNum(20) + 10);
	this->setRoadExpansion(room_core_x, room_core_y, 2, rand_obj->getRandNum(20) + 10);
	this->setRoadExpansion(room_core_x, room_core_y, 3, rand_obj->getRandNum(20) + 10);

}

// �}�X�w��ɂ��A�������邩����(�ȈՔ�
bool RandomDungeon::setRoadSearchMin(int room_core_x, int room_core_y, int first_core_x, int first_core_y) {
	Random* rand_obj = this->_rand_obj;
	int road_num = rand_obj->getRandNum(10) + 10;
	// X��������Y�������������̒��S�n�ƍ����Ă���ꍇ
	if (room_core_x == first_core_x) {
		if (room_core_y > first_core_y) {
			// �m��A��֓������
			this->setRoadExpansion(room_core_x, room_core_y, 0, road_num);
		}
		else if (room_core_y < first_core_y) {
			// �m��A���֓������
			this->setRoadExpansion(room_core_x, room_core_y, 2, road_num);
		}
	} else if (room_core_y == first_core_y) {
		if (room_core_x > first_core_x) {
			// �m��A�E�֓������
			this->setRoadExpansion(room_core_x, room_core_y, 3, road_num);
		}
		else if (room_core_x < first_core_x) {
			// �m��A���֓������
			this->setRoadExpansion(room_core_x, room_core_y, 1, road_num);
		}
	} else {
		// �㉺���E�ɏ����������S�n���Ȃ��̂ŁA������������

		int road_type = -1;
		int sub_road_type = -1;
		int rand_num = rand_obj->getRandNum(2);
		//	Debug.WriteLine("[RandomDungeon]setRoadSearchMin rand_num "+rand_num);
		if (room_core_x > first_core_x) {
			// ����
			if (room_core_y > first_core_y) {
				// ����ɕ���������̂ŕʕ����܂ŒT������
				road_type = 3;
				sub_road_type = 0;

				// ������A�ǂ��炩��T�����邩�����_���Ō��߂�
				if (rand_num == 1) {
					road_type = 0;
					sub_road_type = 3;
				}

			} else if (room_core_y < first_core_y) {
				// �����ɕ���������̂ŕʕ����܂ŒT������
				road_type = 3;
				sub_road_type = 2;

				// �������A�ǂ��炩��T�����邩�����_���Ō��߂�
				if (rand_num == 1) {
					road_type = 2;
					sub_road_type = 3;
				}
			}
		} else if (room_core_x < first_core_x) {
			// �E��
			if (room_core_y > first_core_y) {
				// �E��ɕ���������̂ŕʕ����܂ŒT������
				road_type = 1;
				sub_road_type = 0;

				// �E����A�ǂ��炩��T�����邩�����_���Ō��߂�
				if (rand_num == 1) {
					road_type = 0;
					sub_road_type = 1;
				}

			} else if (room_core_y < first_core_y) {
				// �E���ɕ���������̂ŕʕ����܂ŒT������
				road_type = 1;
				sub_road_type = 2;

				// �E�����A�ǂ��炩��T�����邩�����_���Ō��߂�
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

//	�ʘH���쐬�ł��邩�`�F�b�N
//	�����̒��S�n����ʘH�����΂��A�ʘH���Ȃ����ĕʂ̕�����ʘH�Ɍq���邩�`�F�b�N
void RandomDungeon::checkRoadCreate(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type, int sub_road_type) {

	std::unordered_map<int, std::unordered_map<int, int>> map_search_data;
	// �z��̃R�s�[
	for (int copy_x = 0; copy_x < RandomDungeonSetting::getDungeonWidth(); copy_x++) {
		for (int copy_y = 0; copy_y < RandomDungeonSetting::getDungeonHeight(); copy_y++) {
			map_search_data[copy_x][copy_y] = this->_map_data[copy_x][copy_y];

		}
	}


	int turn_point_x = -1;
	int turn_point_y = -1;
	int turn_next_road_num = -1;

	int expansion_x = room_core_x;
	int expansion_y = room_core_y;


	// ���C���ƋȂ�������̃T�u�̒ʘH�������擾 -------------
	int main_load_search_num = 0;
	int sub_load_search_num = 0;

	switch (road_type) {
	case 0:
		main_load_search_num = room_core_y - first_core_y;
		break;
	case 2:
		main_load_search_num = first_core_y - room_core_y;
		break;
	case 1:
		main_load_search_num = first_core_x - room_core_x;
		break;
	case 3:
		main_load_search_num = room_core_x - first_core_x;
		break;
	}

	switch (sub_road_type) {
	case 0:
		sub_load_search_num = room_core_y - first_core_y;
		break;
	case 2:
		sub_load_search_num = first_core_y - room_core_y;
		break;
	case 1:
		sub_load_search_num = first_core_x - room_core_x;
		break;
	case 3:
		sub_load_search_num = room_core_x - first_core_x;
		break;
	}

	main_load_search_num += 1;
	sub_load_search_num += 1;

	int main_load_num = 0;
	int sub_load_num = 0;
	// �T��
	for (int i = 0; i < main_load_search_num; i++) {

		switch (road_type) {
		case 0:
			expansion_y = room_core_y - i;
			expansion_x = room_core_x;
			break;
		case 1:
			expansion_x = room_core_x + i;
			expansion_y = room_core_y;
			break;
		case 2:
			expansion_y = room_core_y + i;
			expansion_x = room_core_x;
			break;
		case 3:
			expansion_x = room_core_x - i;
			expansion_y = room_core_y;
			break;
		}

		turn_point_x = expansion_x;
		turn_point_y = expansion_y;

		for (int j = 0; j < sub_load_search_num; j++) {

			switch (sub_road_type) {
			case 0:
				expansion_y = room_core_y - j;
				break;
			case 1:
				expansion_x = room_core_x + j;
				break;
			case 2:
				expansion_y = room_core_y + j;
				break;
			case 3:
				expansion_x = room_core_x - j;
				break;
			}

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
	// �������
	// ���C���̓��̕����ɂ���ĕ␳�l�������ɂ���̂ŏ���������

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

//	�ʘH���쐬�ł��邩�`�F�b�N
//	�ȈՔłȂ̂ŕ����̒��S�n����ʘH�����΂��ĕʂ̕�����ʘH�Ɍq���邩�`�F�b�N
bool RandomDungeon::checkRoadCreateMini(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type) {

	std::unordered_map<int, std::unordered_map<int, int>>map_search_data;

	// �z��̃R�s�[
	for (int copy_x = 0; copy_x < RandomDungeonSetting::getDungeonWidth(); copy_x++) {
		for (int copy_y = 0; copy_y < RandomDungeonSetting::getDungeonHeight(); copy_y++) {
			map_search_data[copy_x][copy_y] = this->_map_data[copy_x][copy_y];

		}
	}
	// �ʘH�������擾 -------------
	int main_load_search_num = 0;


	switch (road_type) {
	case 0:
		main_load_search_num = room_core_y - first_core_y;
		break;
	case 2:
		main_load_search_num = first_core_y - room_core_y;
		break;
	case 1:
		main_load_search_num = first_core_x - room_core_x;
		break;
	case 3:
		main_load_search_num = room_core_x - first_core_x;
		break;
	}
	main_load_search_num += 1;

	bool ret_flag = this->checkRoadCreateMiniDetail(room_core_x, room_core_y, main_load_search_num, road_type, map_search_data);

	return ret_flag;
}

// �ʘH�쐬�`�F�b�N�B�����_����
bool RandomDungeon::checkRoadCreateRandom(int room_core_x, int room_core_y) {

	std::unordered_map<int, std::unordered_map<int, int>> map_search_data;
	// �z��̃R�s�[
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

// �ʘH�쐬�`�F�b�N�B�����_���ł̏ڍ׏���
bool RandomDungeon::checkRoadCreateMiniDetail(int room_core_x, int room_core_y, int main_load_search_num, int road_type, std::unordered_map<int, std::unordered_map<int, int>>map_search_data) {
	int expansion_x = room_core_x;
	int expansion_y = room_core_y;

	bool search_start = false;


	Random* rand_obj = this->_rand_obj;
	// �T��
	for (int i = 0; i < main_load_search_num; i++) {
		switch (road_type) {
		case 0:
			expansion_y = room_core_y - i;
			expansion_x = room_core_x;
			break;
		case 1:
			expansion_x = room_core_x + i;
			expansion_y = room_core_y;
			break;
		case 2:
			expansion_y = room_core_y + i;
			expansion_x = room_core_x;
			break;
		case 3:
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
				this->setRoomExpansion(room_core_x, room_core_y);
				this->setRoadExpansion(room_core_x, room_core_y, road_type, i);
				return true;
			}
		}
	}
	return false;
}

// �ʘH���쐬
void RandomDungeon::setRoadExpansion(int room_core_x, int room_core_y, int road_type, int road_num) {
	int map_width = RandomDungeonSetting::getDungeonWidth();
	int map_height = RandomDungeonSetting::getDungeonHeight();

	// �����ɂ��␳
	int road_top_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);
	int road_bottom_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);
	int road_left_correct = (int)floor((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);
	int road_right_correct = (int)ceil((double)(RandomDungeonSetting::_ROAD_WIDTH - 1) / 2);

	// type����A�L�΂����������߂�
	int road_x = 0;
	int road_y = 0;

	int road_correct = 0;
	switch (road_type) {
	case 0:	// ��
		road_y = -1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_HEIGHT;
		break;
	case 1:	// �E
		road_x = 1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_WIDTH;
		break;
	case 2:	// ��
		road_y = 1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_HEIGHT;
		break;
	case 3:	// ��
		road_x = -1;
		road_correct = RandomDungeonSetting::_ROOM_MAX_WIDTH;
		break;
	}

	// ��������
	for (int i = 0; i < (road_num + road_correct); i++) {
		int expansion_x = room_core_x + (i * road_x);
		int expansion_y = room_core_y + (i * road_y);

		// �}�b�v�O�̏ꍇ�͉����������Ȃ�
		if (expansion_x < 0 || expansion_x >= map_width ||
			expansion_y < 0 || expansion_y >= map_height) {
			break;
		}

		if (this->_map_data[expansion_x][expansion_y] == 1) {
			this->setMapData(expansion_x, expansion_y, 4);

			// �}�b�v�����L����
			switch (road_type) {
			case 0:	// ��
			case 2:	// ��

				for (int j = 0; j < RandomDungeonSetting::_ROAD_WIDTH; j++) {

					int load_expansion_x = (expansion_x - road_left_correct + j);
					// �}�b�v�O�̏ꍇ�͉����������Ȃ�
					if (load_expansion_x < 0 || load_expansion_x >= map_width) {
						continue;
					}
					if (this->_map_data[load_expansion_x][expansion_y] == 1) {
						this->setMapData(load_expansion_x, expansion_y, 4);
					}
				}
				break;
			case 1:	// �E
			case 3:	// ��
				for (int j = 0; j < RandomDungeonSetting::_ROAD_WIDTH; j++) {

					int load_expansion_y = (expansion_y - road_top_correct + j);
					// �}�b�v�O�̏ꍇ�͉����������Ȃ�
					if (load_expansion_y < 0 || load_expansion_y >= map_height) {
						continue;
					}
					if (this->_map_data[expansion_x][load_expansion_y] == 1) {
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

	if (map_type == 4) {
		this->_map_ground_data[expansion_x][expansion_y] = 100;

	}
}

std::unordered_map<int, std::unordered_map<int, int>> RandomDungeon::getMapData() {
	return this->_map_data;
}
std::unordered_map<int, std::unordered_map<int, int>> RandomDungeon::getMapGroundData() {
	return this->_map_ground_data;
}
int RandomDungeon::getMapDataFreeNum() {
	int count = 0;

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

	count = RandomDungeonSetting::getDungeonWidth() * RandomDungeonSetting::getDungeonHeight();

	return count;
}