#pragma once
#include "cocos2d.h"
#include "../../RenderObject.h"


class CharaBase;
class HitCircle;
class GameCamera;

class MagicBase : public RenderObject {

// move angle
protected: double _angle = -1;
protected: double _move_speed = 0;

// 0 = object delete
protected: int _frame_time = 0;

protected: int _width = 0;
protected: int _height = 0;

protected: CharaBase* _chara_obj;
//		protected HitSquare _hit_square_obj;
protected: HitCircle* _hit_circle_obj;

private: GameCamera* _camera_obj;

private: int _before_x = 0;
private: int _before_y = 0;
private: bool _draw_flag = true;

private: bool _order_set_flag = false;
private: bool _remove_flag = false;

//private SpriteTile _object_sprite;
//protected TextureInfo _texture_info;

// hit check to correct
protected: double _hit_height = 0;

public: MagicBase(CharaBase* chara_obj, int draw_x, int draw_y, int draw_z, double angle);


public: virtual void magicInit();
public: void Update();
private: void drawUpdate();
protected: virtual void UpdateDetail();
public: bool getRemoveFlag();
public: int getMapBlockX();
public: int getMapBlockY();
public: HitCircle* getHitCircle();
public: CharaBase* getCharaObj();
public: void hitCharaDamage(CharaBase* hit_chara_obj);
public: float getDrawPositionX() override;
public: float getDrawPositionY() override;
public: double getHitHeight();

public: bool getOrderSetFlag();
public: void setOrderSetFlag();
};