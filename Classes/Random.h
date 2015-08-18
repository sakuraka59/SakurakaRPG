#pragma once 
#include <random>
class Random {

private: std::random_device _rnd;     // 非決定的な乱数生成器を生成
private: std::mt19937 _mt;

public: Random() {
	std::mt19937 mt(this->_rnd());
	this->_mt = mt;
}
//-------------------------------------------------------------------
//	 0 ～ 受け取った数値までの間からランダムで返す
//	 0を受け取らせれば0確定で返す
//	 ○○分の1をやりたい場合は、○○-1を受け取らせると良い
//	（100分の1の場合、99を受け取らせれば0～99の100通りになる）
//-------------------------------------------------------------------
public: int getRandNum(int num) {

	std::uniform_int_distribution<> rand_num(0, num);

	return rand_num(this->_mt);
}
};