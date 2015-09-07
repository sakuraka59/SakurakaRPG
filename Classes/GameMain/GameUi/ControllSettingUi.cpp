#include "ControllSettingUi.h"
#include "SkillUi.h"

#include "../GAME_SETTING.h"
#include "../../Input/Gamepad.h"

#include "../chara/CharaPlayer.h"
#include "../chara/controll_setting/ControlSetting.h"
#include "../skill/SkillList.h"
#include "../skill/SkillBase.h"

#include "../item/use_item/UseItem.h"

ControllSettingUi::ControllSettingUi(CharaPlayer* chara_obj, controllSettingType setting_type) {
	this->_chara_obj = chara_obj;
	this->_skill_list = chara_obj->getSkillList();
	this->_setting_type = setting_type;


	// @TODO 力技で操作設定可能リストを作成
	this->_button_set_list[buttonSettingType::circle]		= "○";
	this->_button_set_list[buttonSettingType::triangle]		= "△";
	this->_button_set_list[buttonSettingType::R1]			= "R1";
	this->_button_set_list[buttonSettingType::R2]			= "R2";

	this->_button_set_list[buttonSettingType::circle_L1]	= "L1+○";
	this->_button_set_list[buttonSettingType::triangle_L1]	= "L1+△";
	this->_button_set_list[buttonSettingType::R1_L1]		= "L1+R1";
	this->_button_set_list[buttonSettingType::R2_L1]		= "L1+R2";

	this->_button_set_list[buttonSettingType::circle_L2]	= "L2+○";
	this->_button_set_list[buttonSettingType::triangle_L2]	= "L2+△";
	this->_button_set_list[buttonSettingType::R1_L2]		= "L2+R1";
	this->_button_set_list[buttonSettingType::R2_L2]		= "L2+R2";

	// type ---------------------------------------------------------
	this->_type_bg_render_obj = this->getBgRenderObj();

	int hoge = (GAME_WIDTH / 2) - (this->getDrawWidth() / 2);
	this->_type_bg_render_obj->setPosition(0, 0);

	this->_type_label_obj = new RenderObject();
	this->_type_label_obj->setPosition(20, 400);
	this->_type_bg_render_obj->addChild(this->_type_label_obj);

	// --------------------------------------------------------------

	this->addChild(this->_type_bg_render_obj);

	this->initTypeLabelList();
}
RenderObject* ControllSettingUi::getBgRenderObj() {
	RenderObject* bg_render_obj = new RenderObject();

	int bg_alpha = 128;
	
	int line_width = this->_LINE_WIDTH;
	int bg_width = this->_BG_WIDTH;
	int bg_height = GAME_HEIGHT;
	int bg_top = 00;

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


	cocos2d::Rect base_rect = cocos2d::Rect(0, 0, bg_width - (line_width * 2), bg_height);
	cocos2d::Sprite* base_sprite = cocos2d::Sprite::create();

	base_sprite->setTextureRect(base_rect);
	base_sprite->setColor(cocos2d::Color3B(0, 0, 0));
	base_sprite->setOpacity(bg_alpha);

	auto anchor_point_base = new cocos2d::Vec2(0, 0);
	base_sprite->setAnchorPoint(*anchor_point_base);
	base_sprite->setPosition(line_width, bg_top);
	bg_render_obj->addChild(base_sprite, 0);

	// line

	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, 5, bg_height);
	cocos2d::Sprite* frame_sprite = cocos2d::Sprite::create();

	frame_sprite->setTextureRect(frame_rect);
	frame_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite->setOpacity(bg_alpha);

	auto anchor_point_line = new cocos2d::Vec2(0, 0);
	frame_sprite->setAnchorPoint(*anchor_point_line);
	frame_sprite->setPosition(0, bg_top);
	bg_render_obj->addChild(frame_sprite, 1);

	cocos2d::Rect frame_rect2 = cocos2d::Rect(0, 0, 5, bg_height);
	cocos2d::Sprite* frame_sprite2 = cocos2d::Sprite::create();

	frame_sprite2->setTextureRect(frame_rect2);
	frame_sprite2->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite2->setOpacity(bg_alpha);

	frame_sprite2->setAnchorPoint(*anchor_point_line);
	frame_sprite2->setPosition(bg_width - line_width, bg_top);
	bg_render_obj->addChild(frame_sprite2, 1);

	return bg_render_obj;
}
void ControllSettingUi::initTypeLabelList() {
//	map<skillType, map<string, SkillBase*>> skill_type_list = this->_skill_list->getSkillTypeObjList();

	for (auto button_list : this->_button_set_list) {
		buttonSettingType button_type = button_list.first;

		string type_name = button_list.second;

		// ラベル取得
		LabelTTF* type_label_ttf = this->getLabelTTF(type_name);
		// 表示位置調整
		type_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_type_num * (-1)));

		this->_type_label_obj->addChild(type_label_ttf);


		this->_type_list[this->_type_num] = button_type;

		// セットしたデータの名前入れる場所を用意
		this->_set_detail_name_list[button_type] = this->getLabelTTF("なし");

		this->_set_detail_name_list[button_type]->setPosition(this->_FONT_SIZE * 3, (this->_TEXT_LINE_HEIGHT * this->_type_num * (-1)));
		this->_type_label_obj->addChild(this->_set_detail_name_list[button_type]);

		this->_type_num++;
	}
}
// ------------------------------------------------------------------
void ControllSettingUi::openUiToSkill(SkillBase* skill_obj) {
	if (skill_obj == nullptr) {
		return;
	}

	this->_skill_obj = skill_obj;
//	this->addChild(this->_type_bg_render_obj);
	this->_type_cursor = 0;
	this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));
	this->_draw_flag = true;

	this->oepnUiSetDetailName();
}

void ControllSettingUi::openUiToItem(UseItem* item_obj) {
	if (item_obj == nullptr) {
		return;
	}

	this->_item_obj = item_obj;
	//	this->addChild(this->_type_bg_render_obj);
	this->_type_cursor = 0;
	this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));
	this->_draw_flag = true;

	this->oepnUiSetDetailName();
}
void ControllSettingUi::oepnUiSetDetailName() {
	for (auto button_list : this->_button_set_list) {
		buttonSettingType button_type = button_list.first;

		this->_controll_setting = this->_chara_obj->getContorllSetting();
		
		string setting_obj_name = this->_controll_setting->getControllObjName(button_type);

		this->_set_detail_name_list[button_type]->setString(setting_obj_name);

	}
}
void ControllSettingUi::closeUi() {
	this->_skill_obj = nullptr;
	this->_item_obj = nullptr;
	this->_draw_flag = false;
}
void ControllSettingUi::Update() {
	if (this->_draw_flag != true) {
		return;
	}
	/*
	// △ボタンでUI閉じるのは、使用元のUIで実装されているので不要
	if (Gamepad::Triangle->isPush() == true) {
		this->closeUi();
		return;
	}
	*/
	// ×ボタンでUI閉じる
	if (Gamepad::Cross->isPush() == true) {
		this->closeUi();
		return;
	}
	// 設定内容によって十字キーの閉じボタン変える
	bool close_flag = false;
	switch (this->_setting_type) {
	case controllSettingType::skill:
		if (Gamepad::Right->isPush() == true) {
			close_flag = true;
		}
		break;
	case controllSettingType::item:
		if (Gamepad::Left->isPush() == true) {
			close_flag = true;
		}
		break;
	}
	if (close_flag == true) {
		this->closeUi();
		return;
	}


	// リストに何もない場合は処理しない
	if (this->_type_num <= 0) {
		return;
	}

	// カーソル移動処理
	// 上キー押した
	if (Gamepad::Down->isPush() == true) {

		this->_type_cursor += 1;

		if (this->_type_cursor >= this->_type_num) {
			this->_type_cursor = this->_type_num - 1;
		}

		this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;

		// 下キー押した
	} else if (Gamepad::Up->isPush() == true) {

		this->_type_cursor -= 1;

		if (this->_type_cursor < 0) {
			this->_type_cursor = 0;
		}
		this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;

		// 左キー、もしくは○ボタンを押した場合、詳細を表示する
	} else if (Gamepad::Circle->isPush() == true) {
		this->_controll_setting = this->_chara_obj->getContorllSetting();

		switch (this->_setting_type) {
		case controllSettingType::skill:
			this->_controll_setting->setControllSettingSkill(this->_type_list[this->_type_cursor], this->_skill_obj);
			break;
		case controllSettingType::item:
			this->_controll_setting->setControllSettingItem(this->_type_list[this->_type_cursor], this->_item_obj);
			break;
		}
		
		
		this->closeUi();

	}
}
int ControllSettingUi::getDrawWidth() {
	//int width = (this->_BG_WIDTH + -(this->_LINE_WIDTH * 2));
	int width = this->_BG_WIDTH;
	return width;
}
bool ControllSettingUi::getDrawFlag() {
	return this->_draw_flag;
}
LabelTTF* ControllSettingUi::getLabelTTF(string set_string_data) {

	LabelTTF* label_ttf = LabelTTF::create(set_string_data, this->_FONT_FILE, this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
	label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
	auto anchor_point_type = new cocos2d::Vec2(0, 1);
	label_ttf->setAnchorPoint(*anchor_point_type);

	return label_ttf;

}