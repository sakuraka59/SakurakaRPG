#pragma once

class RandomDungeonSetting{
// ���ʐݒ� -----------------------------------------------------
// road width
public: static const int _ROAD_WIDTH = 3;

// �����쐬�̃A���S���Y���̎w��
// 1�F���[�O���C�N�ɂ����镔�������@�ɂ��쐬
// 2�F�����_���n�_�I������̕����W�J�ɂ��쐬
public: static const int _MAP_CREATE_TYPE = 2;

// 1�F���[�O���C�N�ɂ����镔�������@�ɂ��쐬 ------------------
// room num
public: static const int _DUNGEON_BLOCK_X = 7;
public: static const int _DUNGEON_BLOCK_Y = 5;

// room width and height
public: static const int _DUNGEON_MAP_X = 15;//15;
public: static const int _DUNGEON_MAP_Y = 10;//9;
public: static const int _ROOM_FRAME_SIZE = 2;

// 2�F�����_���n�_�I������̕����W�J�ɂ��쐬�ɂĎg�p ----------
// map size
public: static const int _MAP_WIDTH = 16 * 4;
public: static const int _MAP_HEIGHT = 9 * 4;
public: static const int _MAP_FRAME_NUM = 1;

// ������
public: static const int _ROOM_MIN = 5;
public: static const int _ROOM_MAX = 7;

public: static const int _ROOM_MIN_WIDTH = 12;
public: static const int _ROOM_MIN_HEIGHT = 6;
public: static const int _ROOM_MAX_WIDTH = 16;
public: static const int _ROOM_MAX_HEIGHT = 9;

public: static int getDungeonWidth() {
	int dungeon_width = 0;
	switch (RandomDungeonSetting::_MAP_CREATE_TYPE) {
	case 1:
		dungeon_width = RandomDungeonSetting::_DUNGEON_MAP_X * RandomDungeonSetting::_DUNGEON_BLOCK_X;
		break;
	case 2:
		dungeon_width = RandomDungeonSetting::_MAP_WIDTH + (RandomDungeonSetting::_MAP_FRAME_NUM * 2);
		break;
	}
	return dungeon_width;
}
public: static int getDungeonHeight() {
	int dungeon_height = 0;
	switch (RandomDungeonSetting::_MAP_CREATE_TYPE) {
	case 1:
		dungeon_height = RandomDungeonSetting::_DUNGEON_MAP_Y * RandomDungeonSetting::_DUNGEON_BLOCK_Y;
		break;
	case 2:
		dungeon_height = RandomDungeonSetting::_MAP_HEIGHT + (RandomDungeonSetting::_MAP_FRAME_NUM * 2);
		break;
	}
	return dungeon_height;
}
};