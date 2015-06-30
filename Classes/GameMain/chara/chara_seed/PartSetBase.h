#pragma once
#include "../../../RenderObject.h"
#include <unordered_map>

using namespace std;

class PartBase;
class CharaBase;
enum class partsAngleType;
class PartSetBase : public RenderObject
{
// 各方向ごとのパーツリスト
// 1:正面 2:左手前 3:左 4:左奥 5:奥 6:右奥 7:右 8:右手前
public: unordered_map<partsAngleType, PartBase*> _parts_obj_list;
private: partsAngleType _angle_direction;
protected: CharaBase* _chara_obj;
public: PartSetBase(CharaBase* chara_obj);

public: virtual void Update();
public: void updateAngle(partsAngleType angle_type);
};