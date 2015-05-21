#pragma once

#include <unordered_map>
#include <random>
#include "RandomDungeonSetting.h"

class Random;

class RandomDungeon {
private: std::unordered_map<int, std::unordered_map<int, int>> _map_data;
private: Random* _rand_obj;
public: RandomDungeon();

// ���������@�Ń}�b�v�쐬
private: void DungeonCreateRogelike(int dungeon_width, int dungeon_height);

// �Ǝ������Ń}�b�v�쐬
private: void DungeonCreateOriginal(int dungeon_width, int dungeon_height);

// �}�X�w��ɂ��A�������쐬
private: void setRoomExpansion(int room_core_x, int room_core_y);

// �}�X�w��ɂ��A�������邩����
private: void setRoadFirstRoom(int room_core_x, int room_core_y);

// �}�X�w��ɂ��A�������邩����(�ȈՔ�
private: bool setRoadSearchMin(int room_core_x, int room_core_y, int first_core_x, int first_core_y);

//	�ʘH���쐬�ł��邩�`�F�b�N
//	�����̒��S�n����ʘH�����΂��A�ʘH���Ȃ����ĕʂ̕�����ʘH�Ɍq���邩�`�F�b�N
private: void checkRoadCreate(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type, int sub_road_type);

//	�ʘH���쐬�ł��邩�`�F�b�N
//	�ȈՔłȂ̂ŕ����̒��S�n����ʘH�����΂��ĕʂ̕�����ʘH�Ɍq���邩�`�F�b�N
private: bool checkRoadCreateMini(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type);

// �ʘH�쐬�`�F�b�N�B�����_����
private: bool checkRoadCreateRandom(int room_core_x, int room_core_y);

// �ʘH�쐬�`�F�b�N�B�����_���ł̏ڍ׏���
private: bool checkRoadCreateMiniDetail(int room_core_x, int room_core_y, int main_load_search_num, int road_type, std::unordered_map<int, std::unordered_map<int, int>>map_search_data);


// �ʘH���쐬
private: void setRoadExpansion(int room_core_x, int room_core_y, int road_type, int road_num);

private: void setMapData(int expansion_x, int expansion_y, int map_type);

public: std::unordered_map<int, std::unordered_map<int, int>> getMapData();

private: int getMapDataFreeNum();

private: int getMapBlockNum();
};