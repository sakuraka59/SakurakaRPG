#pragma once
#include "../../RenderObject.h"
#include "cocos2d.h"

#include <memory>

class GameCamera;
class HitSquare;
class MapObjectBase : public RenderObject {

public: cocos2d::ParticleSystemQuad* test_particle;

	// object size
protected: int _OBJECT_WIDTH = 96;
protected: int _OBJECT_HEIGHT = 192;

private: bool _DRAW_FLAG = false;

//		private int _GAME_WIDTH = 960;
//		private int _GAME_HEIGHT = 544;
private: int _draw_correction_x = 0;
private: int _draw_correction_y = 30;
private: GameCamera* _camera_obj;

// hit check type 1:cercle 2:square 3:ground size square(test only)
private: int _hit_check_type = 3;
//protected: HitSquare* _hit_square_obj;

protected: HitSquare _hit_square_obj;

private: double _anime_num = 0;
private: double _anime_move_speed = 0.3;
private: int _sanime_statue = 0;

public: MapObjectBase(int map_block_x, int map_block_y, GameCamera* camera_obj);
public: void Update();
public: int getHitCheckType();
public: HitSquare* getHitSquare();
public: void resetDrawObject();
public: void removeDrawObject();


};