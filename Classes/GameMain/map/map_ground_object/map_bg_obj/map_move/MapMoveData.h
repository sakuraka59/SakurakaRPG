#pragma once

#include "cocos2d.h"

using namespace cocos2d;
class MapMoveData : public Ref {
private: int _map_move_type = -1;	// �ړ���}�b�v�^�C�v
private: int _move_block_x = 0;		// �ړ���X�}�X���W
private: int _move_block_y = 0;		// �ړ���Y�}�X���W
private: int _extend_data_1 = -1;	// �g���f�[�^����1
private: int _extend_data_2 = -1;	// �g���f�[�^����2

// [�}�b�v�^�C�v = 1�Œ�,	�ړ���X�}�X���W,	�ړ���Y�}�X���W,	���[���h�}�b�v�pX,		���[���h�}�b�v�pY]
// [�}�b�v�^�C�v = 2�Œ�,	�ړ���X�}�X���W,	�ړ���Y�}�X���W,	�~�j�}�b�v����ID,		0�Œ�]
// [�}�b�v�^�C�v = 3�Œ�,	0�Œ�,				0�Œ�,				�����_���}�b�v����ID,	0�Œ�]

public: MapMoveData(int map_move_type, int move_block_x, int move_block_y, int extend_data_1, int extend_data_2);
public: int getMoveType();		// �ړ���}�b�v�^�C�v��Ԃ�
public: int getMoveBlockX();	// �ړ���X�}�X���W��Ԃ�
public: int getMoveBlockY();	// �ړ���Y�}�X���W��Ԃ�
public: int getExtendData1();	// �g���f�[�^����1��Ԃ�
public: int getExtendData2();	// �g���f�[�^����2��Ԃ�
};