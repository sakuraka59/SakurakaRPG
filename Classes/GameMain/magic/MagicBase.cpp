#include "MagicBase.h"

#include "../chara/CharaBase.h"
#include "../GameCamera.h"
#include "../GAME_SETTING.h"
#include "../shadow/ShadowObjectList.h"

MagicBase::MagicBase(CharaBase* chara_obj) {

	// 各種魔法ごとの初期設定を行う
	// C#と違い、コンストラクタ
//	this->magicInit();

//	this->_camera_obj = camera_obj;
	// 誰が放った魔法か
	this->_chara_obj = chara_obj;



//	this->_object_sprite = new SpriteTile(){ TextureInfo = this->_texture_info };
//	this->_object_sprite.TileIndex2D = sprite_vector;
//	this->_object_sprite.Scale = new Vector2(this._width, this._height);

	//this._DRAW_FLAG = true;
//	this.AddChild(this._object_sprite);


	/*
	this->_draw_x = draw_x;
	this->_draw_y = draw_y;
	this->_draw_z = draw_z;
	this->_angle = angle;

	// draw point
	this->_before_x = (int)(this->_draw_x - (this->_width / 2));
	this->_before_y = (int)((this->_draw_y + this->_draw_z) );
	*/


//	this->setPosition(((float)this->_before_x), ((float)this->_before_y));

//	this->_before_x = (int)(this->_draw_x - this->_camera_obj->getCameraX() - (this->_width / 2));
//	this->_before_y = (int)((this->_draw_y + this->_draw_z) - this->_camera_obj->getCameraY());


/*
	this->Position = new Vector2(
		((float)this->_before_x),
		((float)this->_before_y)
		);
*/
//	chara_obj->setShadowList(this);

}
void MagicBase::magicInit(int draw_x, int draw_y, int draw_z, double angle) {
	this->_draw_x = draw_x;
	this->_draw_y = draw_y;
	this->_draw_z = draw_z;
	this->_angle = angle;

	this->_before_x = (int)(this->_draw_x - (this->_width / 2));
	this->_before_y = (int)((this->_draw_y + this->_draw_z));

	this->magicInitExtend();
}
void MagicBase::magicInitExtend() {
}
void MagicBase::Update() {
	if (this->_frame_time <= 0) {
		// 影を消す準備
		this->_shadow_remove_flag = true;

		// 演出が完全終了した場合、オブジェクト破棄の準備をする
		if (this->_frame_end_time <= 0) {
			this->_remove_flag = true;
			return;
		}
		
		
	}



	if (this->_frame_time > 0 && this->_shadow_flag == true) {
		this->UpdateDetail();
		this->drawUpdate();
		this->_frame_time--;
	} else {
		this->_frame_end_time--;
	}
}

void MagicBase::drawUpdate() {

	int set_x = (int)(this->_draw_x - (this->_width / 2));
	int set_y = (int)((this->_draw_y + this->_draw_z) );

//	int set_x = (int)(this->_draw_x - this->_camera_obj->getCameraX() - (this->_width / 2));
//	int set_y = (int)((this->_draw_y + this->_draw_z) - this->_camera_obj->getCameraY());
	if (this->_before_x != set_x || this->_before_y != set_y) {

		// 画面描画範囲外による描画管理

		/*
		this->Position = new Vector2(set_x, set_y);
		//				Debug.WriteLine("[MapObjectBase]changePosition "+ set_x +":"+ set_y);

		if (set_x > GAME_WIDTH - 64 || set_x < 0 || set_y > GAME_HEIGHT - 64 || set_y < 0 - 64) {
			this->_draw_flag = false;
			this->RemoveChild(this->_object_sprite, true);
		}
		else {
			if (this->_draw_flag == false) {
				this->_draw_flag = true;
				this->AddChild(this->_object_sprite);
			}
		}
		*/

//		this->setPosition(set_x, set_y);
		this->_test_particle->setPosition(set_x + this->_particle_width, set_y + this->_particle_height);
		this->_before_x = (int)(this->_draw_x);
		this->_before_y = (int)(this->_draw_y);

//		this->_before_x = (int)(this->_draw_x - this->_camera_obj->getCameraX());
//		this->_before_y = (int)(this->_draw_y - this->_camera_obj->getCameraY());
	}
	//			DrawHelpers
	//			Director.Instance.DrawHelpers.DrawCircle
	//			Director.Instance.DrawHelpers.SetColor( Colors.Red );
}
void MagicBase::UpdateDetail() {

}

//-----------------------------------------------------------
bool MagicBase::getRemoveFlag() {
	return this->_remove_flag;
}
int MagicBase::getMapBlockX() {
	//return (int)FMath.Floor((float)(this->_draw_x / GameSetting._MAP_BLOCK_WIDTH));

	return (int)(this->_draw_x / MAP_BLOCK_WIDTH);
}
int MagicBase::getMapBlockY() {
	//return (int)FMath.Floor((float)(this->_draw_y / GameSetting._MAP_BLOCK_HEIGHT));
	return (int)(this->_draw_y / MAP_BLOCK_HEIGHT);
}
HitCircle* MagicBase::getHitCircle() {
	return this->_hit_circle_obj;
}
CharaBase* MagicBase::getCharaObj(){
	return this->_chara_obj;
}

void MagicBase::hitCharaDamage(CharaBase* hit_chara_obj) {
	hit_chara_obj->directDamageHp(100);
	this->_chara_obj->setTargetChara(hit_chara_obj);

}

float MagicBase::getDrawPositionX() {
	return (float)(this->_draw_x);
//	return (float)(this->_draw_x - this->_camera_obj->getCameraX());
}
float MagicBase::getDrawPositionY() {
	return (float)(this->_draw_y);
//	return (float)(this->_draw_y - this->_camera_obj->getCameraY());
}

double MagicBase::getHitHeight() {
	return this->_hit_height;
}

bool MagicBase::getOrderSetFlag() {
	return this->_order_set_flag;
}
void MagicBase::setOrderSetFlag() {
	this->_order_set_flag = true;
}

bool MagicBase::getShadowRemoveFlag() {
	return this->_shadow_remove_flag;
}
void MagicBase::removeShadow(ShadowObjectList* shadow_list) {
	if (this->_shadow_flag == true) {
		this->_shadow_flag = false;
		shadow_list->removeRenderObject(this);
	}
}