#include "SeedHuman.h"
#include "../../charaGroupList.h"

#include "human_part\HumanTest.h"

SeedHuman::SeedHuman(CharaBase* chara_obj) : SeedBase(chara_obj) {

	// �푰�ݒ� ----------------------------------------------
	this->_run_speed = 3;
	this->_walk_speed = 0.5;
	this->_base_hp = 10000;
	this->_base_sp = 2000;

	this->_vision_range = 30.0;
	this->_vision_angle = 45;

	this->_width = 15;
	this->_height = 48;

	// set group --------------------------------------------
	// my group
	this->_my_group_list.push_back(charaGroupList::human);

	// no target group
	this->_fellow_group_list.push_back(charaGroupList::player);

	// target group
	this->_target_group_list.push_back(charaGroupList::inhabitant);
	this->_target_group_list.push_back(charaGroupList::monster);

	//-------------------------------------------------------

	// �ǂݍ���
	/*
	this->setSpriteData("/Application/res/avatar/human/base/human_base_1.png", 1, 6) ;
	// �\���\�ӏ���ǉ����Ă���
	this->_parts_list.Add( "body_base", new EquipSprite(ResourceManage.getSpriteTile(this->_file_name, this->_file_x, this->_file_y), new Vector2i(0,4)) );

	this->_parts_list.Add( "head_base", new EquipSprite(ResourceManage.getSpriteTile(this->_file_name, this->_file_x, this->_file_y), new Vector2i(0,5)) );

	*/

	// �e�X�g�p -------------------------------------------------

	// �\���\�ӏ���ǉ����Ă���


	/*
	this->_parts_list.Add( "arm_back", new HumanArmBack());
	this->AddChild(this->_parts_list["arm_back"]);

	this->_parts_list.Add( "leg_back", new HumanLegBack());
	this->AddChild(this->_parts_list["leg_back"]);

	this->_parts_list.Add( "body", new HumanBody());
	this->AddChild(this->_parts_list["body"]);

	this->_parts_list.Add( "head", new HumanHead());
	this->AddChild(this->_parts_list["head"]);

	this->_parts_list.Add( "hair", new HumanHair());
	this->AddChild(this->_parts_list["hair"]);

	this->_parts_list.Add( "leg_front", new HumanLegFront());
	this->AddChild(this->_parts_list["leg_front"]);

	this->_parts_list.Add( "arm_front", new HumanArmFront());
	this->AddChild(this->_parts_list["arm_front"]);
	//*/

	// �g�����ǂ������� -----------------------------------
	//*
	//this->_parts_list.Add("test", new HumanTest());
	this->_parts_list["test"] = new HumanTest(this->_chara_obj);
	this->addChild(this->_parts_list["test"]);

	// Plaeyr��p ��ʉE�̃L�����N�^�[�\��
//	this->setSpriteData("/Application/res/avatar/test/test_cus_chara.png", 1, 1);
//	this->_view_parts_list.Add("body_base", new EquipSprite(ResourceManage.getSpriteTile(this->_file_name, this->_file_x, this->_file_y), new Vector2i(0, 0)));
	// */

	// �e�X�g�p�@�����܂� -----------------------------------------

	// �`��p�␳
	this->_draw_correct_x = (int)((float)(340 / 2) *0.20f);
	this->_draw_correct_y = 0;

	this->_scale_per = 1.0f;//0.22f;

	
	//this->Scale = new Vector2(this->_scale_per, this->_scale_per);
	this->setScale(this->_scale_per);
	

	// �`��ݒ�
	/*
	foreach (PartSetBase parts_data in this->_parts_list.Values) {

	this->AddChild(parts_data);
	}
	*/

}
/*
void SeedHuman::Update() {

}
*/
void SeedHuman::updateAngleDetail() {
	this->_parts_list["test"]->updateAngle(this->_angle_direction);
}