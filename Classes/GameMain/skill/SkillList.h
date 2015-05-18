#pragma once

#include "cocos2d.h"
#include <memory>
#include "SkillBase.h"
class SkillBase;

class SkillList : cocos2d::Node {
public:SkillList();
	/*
public: 
	std::unique_ptr<SkillBase> hoge;

	SkillList() {
		this->TestMethod(hoge.get());
		hoge->skillInit();
	};
	
private:
	void TestMethod(SkillBase* hoge_p) {
		hoge_p->skillInit();
	};
	*/
};