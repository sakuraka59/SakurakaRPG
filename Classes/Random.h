#pragma once 
#include <random>
class Random {

private: std::random_device _rnd;     // ”ñŒˆ’è“I‚È—”¶¬Ší‚ð¶¬
private: std::mt19937 _mt;

public: Random() {
	std::mt19937 mt(this->_rnd());
	this->_mt = mt;
}

public: int getRandNum(int num) {

	std::uniform_int_distribution<> rand_num(0, num);
	return rand_num(this->_mt);
}
};