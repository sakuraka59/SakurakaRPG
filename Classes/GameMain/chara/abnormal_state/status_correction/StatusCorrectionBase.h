#pragma once
#include "../StateAuto.h"
#include "../../mainStateType.h"

class CharaBase;

class StatusCorrectionBase : public StateAuto {

private: int _before_frame_state = 0;
private: mainStateType _correction_state = mainStateType::_no_type;
public: StatusCorrectionBase(CharaBase* chara_obj, mainStateType main_state_type);

protected: int getCorrectionNum();

protected: void startStateEffect() override;
protected: void stateEffect() override;
protected: virtual void endStateEffect();
};