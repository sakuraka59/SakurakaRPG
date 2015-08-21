#include "SlashTemplate1.h"
//#include "../../hit/HitCircle.h"

#include <math.h>
#include "../../../../../chara/CharaBase.h"

SlashTemplate1::SlashTemplate1(CharaBase* chara_obj, int attack_range, int attack_speed) : EffectBase(chara_obj){
	this->_anime_range = attack_range - 16;	// 16�̓p�[�e�B�N���̔����̃T�C�Y
	this->_anime_time = attack_speed;
	this->_frame_end_time = this->_anime_time + 10;
}

void SlashTemplate1::magicInitExtend() {
	// �`��̏���
	//	this->_texture_info = ResourceManage.getTextureInfo("/Application/res/magic/magictest.png", 2, 2);
	this->_width = 32;
	this->_height = 32;

	// ������ƕ�������
	this->_draw_z = 30 + 8;

	// ���@���̂̐ݒ�
	this->_frame_time = this->_anime_time;

	//	this->_move_speed = 7.5;

	// �G�t�F�N�g�̔������S���W��ێ�
	this->_effect_base_x = this->_draw_x;
	this->_effect_base_y = this->_draw_y;

	// �E���獶�֎a���G�t�F�N�g�A�j���[�V����
	//	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/effect/slash/slash_test.plist");
	//	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/effect/slash/slash_1.plist");
	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/effect/slash/slash_2.plist");
	//	this->_test_particle = cocos2d::ParticleSystemQuad::create("particle/effect/slash/slash_3.plist");



	this->_test_particle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);//ParticleSystem::PositionType::RELATIVE
	this->_particle_width = 16;
	this->_particle_height = 16;
	//	this->_test_particle->setPosition((particle_width / 2), (particle_height / 2));

	this->addChild(this->_test_particle);

	int effect_range = this->_anime_range;

	int start_angle_correct = 80;	// �����ʒu�����p


	double move_x = (double)(cos((float)((this->_angle + start_angle_correct) * M_PI / 180)) * effect_range);
	double move_y = (double)(sin((float)((this->_angle + start_angle_correct) * M_PI / 180)) * effect_range);
	this->_draw_x = this->_effect_base_x + move_x;
	this->_draw_y = this->_effect_base_y + move_y;

	this->_angle -= start_angle_correct;				// ������������

}
void SlashTemplate1::UpdateDetail() {

	this->_angle += 160 / this->_anime_time;
	this->_draw_z -= 30 / this->_anime_time;
	int effect_range = this->_anime_range;

	double move_x = (double)(cos((float)((this->_angle) * M_PI / 180)) * effect_range);
	double move_y = (double)(sin((float)((this->_angle) * M_PI / 180)) * effect_range);
	this->_draw_x = this->_effect_base_x + move_x;
	this->_draw_y = this->_effect_base_y + move_y;

}
