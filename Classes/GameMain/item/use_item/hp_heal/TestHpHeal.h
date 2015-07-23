#pragma once
#include "../UseItem.h"


class TestHpHeal : public UseItem {

public: TestHpHeal();
public: bool useSkill() override;
};