#pragma once
#include "../../PartSetBase.h"


class PartBase;

class HumanTest : public PartSetBase
{
private: std::shared_ptr<PartBase> _part_test;
public: HumanTest();

};