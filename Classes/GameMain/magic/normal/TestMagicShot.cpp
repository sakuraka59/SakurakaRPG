#include "TestMagicShot.h"
#include "../../hit/HitCircle.h"
#include <math.h>

TestMagicShot::TestMagicShot(CharaBase* chara_obj)
	: MagicBase(chara_obj){

}

void TestMagicShot::magicInitExtend() {
	// •`‰æ‚Ì€”õ
//	this->_texture_info = ResourceManage.getTextureInfo("/Application/res/magic/magictest.png", 2, 2);
	this->_width = 10;
	this->_height = 32;
	
	// ‚¿‚å‚Á‚Æ•‚‚©‚¹‚é
	this->_draw_z += 10;

	// –‚–@Ž©‘Ì‚ÌÝ’è
	this->_frame_time = 60;
	this->_frame_end_time = 30;
	this->_move_speed = 10.0;

	//			this->_hit_square_obj = new HitSquare(ref this->_draw_x, ref this->_draw_y, this->_width, this->_height, ref this->_angle);
	this->_hit_circle_obj = new HitCircle(this, this->_width / 2);
	this->_hit_height = 16;

	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/magic/normal/testShot4.plist");
//	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/effect/slash/slash_test.plist");

//	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/magic/normal/testShot_endress.plist");
//	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/magic/fire/fire_ball.plist");
//	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/magic/fire/fire_ball_endress.plist");
	
	this->_test_particle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);//ParticleSystem::PositionType::RELATIVE

	this->_particle_width = 16;
	this->_particle_height = 16;
//	this->_test_particle->setPosition((particle_width / 2), (particle_height / 2));

	this->addChild(this->_test_particle);
	// setSourcePosition
	

	
}
void TestMagicShot::UpdateDetail() {

	double move_x = (double)(cos((float)(this->_angle * M_PI / 180)) * this->_move_speed);
	double move_y = (double)(sin((float)(this->_angle * M_PI / 180)) * this->_move_speed);
	this->_draw_x += move_x;
	this->_draw_y += move_y;
}