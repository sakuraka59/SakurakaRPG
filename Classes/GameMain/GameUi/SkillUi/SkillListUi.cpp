#include "SkillListUi.h"

#include "../../GAME_SETTING.h"
#include "../../../Input/Gamepad.h"

#include "../../chara/CharaPlayer.h"
//#include "../../chara/controll_setting/ControlSetting.h"
#include "../../skill/SkillList.h"
#include "../../skill/SkillBase.h"

#include "../ControllSettingUi.h"
SkillListUi::SkillListUi(CharaPlayer* chara_obj) {
	this->_chara_obj = chara_obj;
	this->_skill_list = chara_obj->getSkillList();

	
	// type ---------------------------------------------------------
	this->_type_bg_render_obj = this->getBgRenderObj();

	this->_type_label_obj = new RenderObject();
	this->_type_label_obj->setPosition(20, 400);
	this->_type_bg_render_obj->addChild(this->_type_label_obj);

	// detail -------------------------------------------------------
	this->_detail_bg_render_obj = this->getBgRenderObj();

	this->_detail_label_obj = new RenderObject();
	this->_detail_label_obj->setPosition(20, 400);
	this->_detail_bg_render_obj->addChild(this->_detail_label_obj);

	this->_detail_bg_render_obj->setPosition(-220, 0);
	// --------------------------------------------------------------

	// controll setting ui 
	this->_controll_setting_ui_obj = new ControllSettingUi(chara_obj, controllSettingType::skill);
	

	this->_controll_setting_ui_obj->setPosition(-220 - (this->_controll_setting_ui_obj->getDrawWidth() + 20), 0);
	// @TODO test
//	this->addChild(this->_controll_setting_ui_obj);

	// --------------------------------------------------------------

	this->addChild(this->_type_bg_render_obj);

	
	// �ꗗ������
	this->initTypeLabelList();

}
RenderObject* SkillListUi::getBgRenderObj() {
	RenderObject* bg_render_obj = new RenderObject();

	int bg_alpha = 128;
	int line_width = this->_LINE_WIDTH;
	int bg_width = this->_BG_WIDTH;

	//---------------------------------------------------------------
	cocos2d::Rect arrow_rect = cocos2d::Rect(0, 0, 25, 2);
	cocos2d::Sprite* arrow_sprite = cocos2d::Sprite::create();

	arrow_sprite->setTextureRect(arrow_rect);
	arrow_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	arrow_sprite->setOpacity(255);

	auto anchor_point_arrow = new cocos2d::Vec2(0, 0);
	arrow_sprite->setAnchorPoint(*anchor_point_arrow);
	arrow_sprite->setPosition(-5, 400 - (this->_FONT_SIZE / 2));
	bg_render_obj->addChild(arrow_sprite, 2);

	//---------------------------------------------------------------


	cocos2d::Rect base_rect = cocos2d::Rect(0, 0, bg_width - (line_width * 2), GAME_HEIGHT);
	cocos2d::Sprite* base_sprite = cocos2d::Sprite::create();

	base_sprite->setTextureRect(base_rect);
	base_sprite->setColor(cocos2d::Color3B(0, 0, 0));
	base_sprite->setOpacity(bg_alpha);

	auto anchor_point_base = new cocos2d::Vec2(0, 0);
	base_sprite->setAnchorPoint(*anchor_point_base);
	base_sprite->setPosition(line_width, 0);
	bg_render_obj->addChild(base_sprite, 0);

	// line

	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, 5, GAME_HEIGHT);
	cocos2d::Sprite* frame_sprite = cocos2d::Sprite::create();

	frame_sprite->setTextureRect(frame_rect);
	frame_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite->setOpacity(bg_alpha);

	auto anchor_point_line = new cocos2d::Vec2(0, 0);
	frame_sprite->setAnchorPoint(*anchor_point_line);
	frame_sprite->setPosition(0, 0);
	bg_render_obj->addChild(frame_sprite, 1);

	cocos2d::Rect frame_rect2 = cocos2d::Rect(0, 0, 5, GAME_HEIGHT);
	cocos2d::Sprite* frame_sprite2 = cocos2d::Sprite::create();

	frame_sprite2->setTextureRect(frame_rect2);
	frame_sprite2->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite2->setOpacity(bg_alpha);

	frame_sprite2->setAnchorPoint(*anchor_point_line);
	frame_sprite2->setPosition(bg_width - line_width, 0);
	bg_render_obj->addChild(frame_sprite2, 1);

	return bg_render_obj;
}
// ------------------------------------------------------------------
void SkillListUi::openUi() {
	this->removeChild(this->_detail_bg_render_obj);
	this->removeChild(this->_controll_setting_ui_obj);
	this->_controll_type = 0;
	
	this->_type_cursor = 0;
	this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));

	this->_detail_label_obj->removeAllChildren();

}
void SkillListUi::closeUi() {

	this->removeChild(this->_detail_bg_render_obj);
	this->removeChild(this->_controll_setting_ui_obj);

	this->_detail_label_obj->removeAllChildren();

	this->_controll_setting_ui_obj->closeUi();
}
void SkillListUi::openDetailList() {
	
	skillType skill_type = this->_type_list[this->_type_cursor];

	this->_detail_label_obj->removeAllChildren();
	this->_detail_label_obj->addChild(this->_detail_label_list[skill_type]);
	this->_open_detail_type = skill_type;

	// �\���ʒu������
	this->_detail_cursor = 0;
	this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_detail_cursor));

	this->addChild(this->_detail_bg_render_obj);
}
void SkillListUi::closeDetailList() {

	this->_cursor_delay = this->_CURSOR_DELAY_TIME;
	this->_controll_type = 0;
	this->removeChild(this->_detail_bg_render_obj);
	this->_detail_label_obj->removeAllChildren();
}
// ------------------------------------------------------------------
void SkillListUi::initTypeLabelList() {
	map<skillType, map<string, SkillBase*>> skill_type_list = this->_skill_list->getSkillTypeObjList();

	for (auto skill_list : skill_type_list) {
		skillType skill_type = skill_list.first;

		// �܂��ڍ׃��X�g���쐬
		bool set_detail_flag = this->initDetailLabelList(skill_type);
		
		//�ڍ׃��X�g���Ȃ��ꍇ�A��ʂ�ǉ����Ȃ�
		if (set_detail_flag != true) {
			continue;
		}

		string type_name = this->getTypeName(skill_type);

		// ���x���擾
		LabelTTF* type_label_ttf = this->getLabelTTF(type_name);
		// �\���ʒu����
		type_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_type_num * (-1)));

		this->_type_label_obj->addChild(type_label_ttf);


		this->_type_list[this->_type_num] = skill_type;

		this->_type_num++;

		
	}
}
bool SkillListUi::initDetailLabelList(skillType skill_type){

	map<string, SkillBase*> skill_list = this->_skill_list->getSkillObjList(skill_type);
	this->_detail_num_list[skill_type] = 0;

	bool draw_flag = false;
	for (auto skill_obj_base : skill_list) {
		if (this->_detail_label_list[skill_type] == nullptr) {
			this->_detail_label_list[skill_type] = new RenderObject();
		}
		SkillBase* skill_obj = skill_obj_base.second;
		if (skill_obj->getUiDrawFlag() != true) {
			continue;
		}
		this->_detail_skill_list[skill_type][this->_detail_num_list[skill_type]] = skill_obj;

		string skill_name = skill_obj->getSkillName();

		// ���x���擾
		LabelTTF* skill_name_label_ttf = this->getLabelTTF(skill_name);
		// �\���ʒu����
		skill_name_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_detail_num_list[skill_type] * (-1)));

		this->_detail_label_list[skill_type]->addChild(skill_name_label_ttf);

		this->_detail_num_list[skill_type]++;
		draw_flag = true;
	}
	return draw_flag;
}
void SkillListUi::initOpenDetailList(skillType skill_type) {
	this->_detail_label_obj->removeAllChildren();
	this->_detail_label_obj->addChild(this->_detail_label_list[skill_type]);
	this->_open_detail_type = skill_type;

	// �\���ʒu������
	this->_detail_cursor = 0;
	this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_detail_cursor));

	this->addChild(this->_detail_bg_render_obj);
}
// ------------------------------------------------------------------
void SkillListUi::Update() {
	switch (this->_controll_type) {
	case 0:
		this->updateListType();
		break;
	case 1:
		this->updateListDetail();
		break;
	case 2:
		this->_controll_setting_ui_obj->Update();

		// �Z�b�g�����ꍇ�A1�O�ɂ��ǂ�
		if (this->_controll_setting_ui_obj->getDrawFlag() != true) {
			this->_controll_type = 1;
			this->removeChild(this->_controll_setting_ui_obj);
		}
		break;
	}
}
void SkillListUi::updateListType() {
	if (this->_cursor_delay > 0) {
		this->_cursor_delay--;
		return;
	}

	// ���X�g�ɉ����Ȃ��ꍇ�͏������Ȃ�
	if (this->_type_num <= 0) {
		return;
	}

	// �J�[�\���ړ�����
	// ��L�[������
	if (Gamepad::Down->isPush() == true) {
		
		this->_type_cursor += 1;

		if (this->_type_cursor >= this->_type_num) {
			this->_type_cursor = this->_type_num - 1;
		}

		this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;

	// ���L�[������
	} else if (Gamepad::Up->isPush() == true) {
		
		this->_type_cursor -= 1;

		if (this->_type_cursor < 0) {
			this->_type_cursor = 0;
		}
		this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;

	// ���L�[�A�������́��{�^�����������ꍇ�A�ڍׂ�\������
	} else if (Gamepad::Left->isPush() == true || Gamepad::Circle->isPush() == true) {
		
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		this->_controll_type = 1;

		this->openDetailList();
	}
}
void SkillListUi::updateListDetail() {
	if (this->_cursor_delay > 0) {
		this->_cursor_delay--;
		return;
	}

	// ���A�~�{�^���Ŏ�ވꗗ�֖߂�
	if (Gamepad::Right->isPush() == true || Gamepad::Cross->isPush() == true) {
		this->closeDetailList();
	}

	// ���X�g�ɉ����Ȃ��ꍇ�͏������Ȃ�
	if (this->_detail_num_list[this->_open_detail_type] <= 0) {
		return;
	}

	if (Gamepad::Down->isPush() == true) {
		this->_detail_cursor += 1;

		if (this->_detail_cursor >= this->_detail_num_list[this->_open_detail_type]) {
			this->_detail_cursor = this->_detail_num_list[this->_open_detail_type] - 1;
		}
		this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_detail_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;
	} else if (Gamepad::Up->isPush() == true) {
		this->_detail_cursor -= 1;

		if (this->_detail_cursor < 0) {
			this->_detail_cursor = 0;
		}
		this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_detail_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;

	// ���L�[�A�������́��{�^�����������ꍇ�A�V���[�g�J�b�g�ݒ��\������
	} else if (Gamepad::Left->isPush() == true || Gamepad::Square->isPush() == true) {
		
		this->_controll_type = 2;
		this->addChild(this->_controll_setting_ui_obj);
		this->_controll_setting_ui_obj->openUiToSkill(this->_detail_skill_list[this->_open_detail_type][this->_detail_cursor]);
	}
	
}
// ------------------------------------------------------------------
string SkillListUi::getTypeName(skillType skill_type) {
	unordered_map<skillType, string> type_name_list;
	type_name_list[skillType::sword] = "�Ў茕";
	//type_name_list[skillType::sword] = "�Ў茕";

	string type_name = "�ȂȂ�";

	if (type_name_list[skill_type] != "") {
		type_name = type_name_list[skill_type];
	}
	return type_name;
}
int SkillListUi::getDrawWidth() {
	int width = (this->_BG_WIDTH + -(this->_LINE_WIDTH * 2));
	return width;
}

LabelTTF* SkillListUi::getLabelTTF(string set_string_data) {

	LabelTTF* label_ttf = LabelTTF::create(set_string_data, this->_FONT_FILE, this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
	label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
	auto anchor_point_type = new cocos2d::Vec2(0, 1);
	label_ttf->setAnchorPoint(*anchor_point_type);

	return label_ttf;

}