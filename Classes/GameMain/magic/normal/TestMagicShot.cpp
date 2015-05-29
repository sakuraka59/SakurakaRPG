#include "TestMagicShot.h"
#include "../../hit/HitCircle.h"
#include <math.h>

TestMagicShot::TestMagicShot(CharaBase* chara_obj, int draw_x, int draw_y, int draw_z, double angle)
	: MagicBase(chara_obj, draw_x, draw_y, draw_z, angle){

}

void TestMagicShot::magicInit() {
	// •`‰æ‚Ì€”õ
//	this->_texture_info = ResourceManage.getTextureInfo("/Application/res/magic/magictest.png", 2, 2);
	this->_width = 30;
	this->_height = 30;

	// –‚–@Ž©‘Ì‚ÌÝ’è
	this->_frame_time = 20;
	this->_move_speed = 10.0;

	//			this->_hit_square_obj = new HitSquare(ref this->_draw_x, ref this->_draw_y, this->_width, this->_height, ref this->_angle);
	this->_hit_circle_obj = new HitCircle(this, this->_width / 2);
	this->_hit_height = 16;


	cocos2d::ParticleSystemQuad* test_particle = cocos2d::ParticleSystemQuad::create("particle/magic/normal/testShot.plist");
	test_particle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);//ParticleSystem::PositionType::RELATIVE
	//	cocos2d::Size imgSize = this->test_particle->getContentSize();
	int particle_width = 64;
	int particle_height = 64;
	test_particle->setPosition((particle_width / 2), (particle_height / 2));

	this->addChild(test_particle);
}
void TestMagicShot::UpdateDetail() {

	double move_x = (double)(cos((float)(this->_angle * M_PI / 180)) * this->_move_speed);
	double move_y = (double)(sin((float)(this->_angle * M_PI / 180)) * this->_move_speed);
	this->_draw_x += move_x;
	this->_draw_y += move_y;
}