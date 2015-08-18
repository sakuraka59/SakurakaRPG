#pragma once 
#include <random>
class Random {

private: std::random_device _rnd;     // �񌈒�I�ȗ���������𐶐�
private: std::mt19937 _mt;

public: Random() {
	std::mt19937 mt(this->_rnd());
	this->_mt = mt;
}
//-------------------------------------------------------------------
//	 0 �` �󂯎�������l�܂ł̊Ԃ��烉���_���ŕԂ�
//	 0���󂯎�点���0�m��ŕԂ�
//	 ��������1����肽���ꍇ�́A����-1���󂯎�点��Ɨǂ�
//	�i100����1�̏ꍇ�A99���󂯎�点���0�`99��100�ʂ�ɂȂ�j
//-------------------------------------------------------------------
public: int getRandNum(int num) {

	std::uniform_int_distribution<> rand_num(0, num);

	return rand_num(this->_mt);
}
};