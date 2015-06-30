#pragma once
#include "../../../RenderObject.h"
#include <unordered_map>

using namespace std;

class PartBase;
class CharaBase;
enum class partsAngleType;
class PartSetBase : public RenderObject
{
// �e�������Ƃ̃p�[�c���X�g
// 1:���� 2:����O 3:�� 4:���� 5:�� 6:�E�� 7:�E 8:�E��O
public: unordered_map<partsAngleType, PartBase*> _parts_obj_list;
private: partsAngleType _angle_direction;
protected: CharaBase* _chara_obj;
public: PartSetBase(CharaBase* chara_obj);

public: virtual void Update();
public: void updateAngle(partsAngleType angle_type);
};