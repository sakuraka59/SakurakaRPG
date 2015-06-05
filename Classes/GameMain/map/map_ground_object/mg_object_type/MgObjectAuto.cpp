#include "MgObjectAuto.h"
#include "../../../chara/CharaBase.h"
void MgObjectAuto::activeObject(CharaBase* chara_obj) {
	chara_obj->sendComment("‚Ç[‚ñI");
	chara_obj->healHp(1);
}