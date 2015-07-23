#include "ObjItemList.h"

#include "../../GAME_SETTING.h"
#include "../../../Input/Gamepad.h"

#include "../../item/equip_item/HaveEquipItemList.h"
#include "../../item/use_item/HaveUseItemList.h"
#include "../../item/haveItemType.h"

#include "../../item/equip_item/EquipItem.h"
#include "../../item/use_item/UseItem.h"
#include "../../item/ItemBase.h"

ObjItemList::ObjItemList() {
	this->_type_label_obj = new RenderObject();
	this->_detail_label_obj = new RenderObject();
}
void ObjItemList::setItemList(HaveEquipItemList* equip_item_list, HaveUseItemList* use_item_list) {

	this->_equip_item_list = equip_item_list;
	this->_use_item_list = use_item_list;
	this->setItemListData(this->_equip_item_list->getItemTypeList(), this->_use_item_list->getItemTypeList());
}
void ObjItemList::setItemListData(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>>* use_item_type_list
) {
	this->_equip_item_list_detail = equip_item_type_list;
	this->_use_item_list_detail = use_item_type_list;
}
void ObjItemList::setBackGround() {
	// type ---------------------------------------------------------

	this->_type_bg_render_obj = this->getBgRenderObj();

	this->_type_label_obj = new RenderObject();
	this->_type_label_obj->setPosition(20, 400);


	this->_type_bg_render_obj->addChild(this->_type_label_obj);

	// detail -------------------------------------------------------
	this->_detail_bg_render_obj = this->getBgRenderObj();


	this->_detail_label = "";

	this->_detail_label_obj = new RenderObject();
	this->_detail_label_obj->setPosition(20, 400);
	//	this->_type_label_obj->addChild(type_label_ttf);

	this->_detail_bg_render_obj->addChild(this->_detail_label_obj);
	//*/
	this->_detail_bg_render_obj->setPosition(220, 0);
	// test ---------------------------------------------------------
	//	this->openItemListInit();

	// --------------------------------------------------------------


	this->addChild(this->_type_bg_render_obj);
	//	this->addChild(this->_detail_bg_render_obj);
	//this->addChild(;
}
RenderObject* ObjItemList::getBgRenderObj() {
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
	arrow_sprite->setPosition(180, 400 - (this->_FONT_SIZE/2));
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
	//	this->_bg_render_obj->setOpacity(128);
}

void ObjItemList::initCursorPosition() {
	// �J�[�\�������ʒu��
	this->_item_type_cursor = 0;
	this->_controll_type = 0;
	this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_item_type_cursor));
}
void ObjItemList::setOnlyFlag(bool open_only_flag) {
	this->_open_only_flag = open_only_flag;
}

// �ꗗ�J��
void ObjItemList::openItemListInit(){
//	for (int i = (int)haveItemType::_no_type; i < (int)haveItemType::_enum_end; i++) {

//	}

	this->initCursorPosition();

//	this->_use_item_list->getItemTypeList();
//	this->_equip_item_list->getItemTypeList();

	this->_item_type_num = 0;
	this->_type_label = "";
	this->_type_label_obj->removeAllChildren();


//	this->openItemListDetail(this->_equip_item_list->getItemTypeList(), this->_use_item_list->getItemTypeList());
	this->openItemListDetail(this->_equip_item_list_detail, this->_use_item_list_detail);


//	this->_type_label_obj->setString(this->_type_label);
}
void ObjItemList::openItemListDetail(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>>* use_item_type_list) {


	for (auto item_list_obj : *equip_item_type_list) {
		haveItemType item_type = item_list_obj.first;
		this->_type_list[this->_item_type_num] = item_type;
		string type_name = this->getItemTypeName(item_type);
		//		this->_type_label += type_name + "\n\n";


		this->openEquipItemDetailListInit(item_type);


		if (this->_item_detail_num_list[item_type] > 0) {
			auto type_label_ttf = LabelTTF::create(type_name, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
			type_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
			auto anchor_point_type = new cocos2d::Vec2(0, 1);
			type_label_ttf->setAnchorPoint(*anchor_point_type);
			type_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_type_num * (-1)));
			this->_type_label_obj->addChild(type_label_ttf);

			this->_item_type_num++;
		}
	}

	//unordered_map<haveItemType, unordered_map<useItemId, UseItem*>>* use_item_type_list = this->_use_item_list->getItemTypeList();
	for (auto item_list_obj : *use_item_type_list) {
		haveItemType item_type = item_list_obj.first;
		this->_type_list[this->_item_type_num] = item_type;

		string type_name = this->getItemTypeName(item_type);
		//		this->_type_label += type_name + "\n\n";

		this->_type_list[this->_item_type_num] = item_type;


		this->_item_detail_num_list[item_type] = 0;

		if (this->_item_detail_list[item_type] != nullptr) {
			this->_item_detail_list[item_type]->removeAllChildren();
		}

		for (auto use_item_obj : item_list_obj.second) {

			if (use_item_obj.second->getNum() <= 0) {
				continue;
			}
			
			auto detail_label_ttf = LabelTTF::create(use_item_obj.second->getItemName(), "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
			detail_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
			auto anchor_point_type = new cocos2d::Vec2(0, 1);
			detail_label_ttf->setAnchorPoint(*anchor_point_type);
			detail_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));
			//this->_type_label_obj->addChild(detail_label_ttf);

			if (this->_item_detail_list[item_type] == nullptr) {
				this->_item_detail_list[item_type] = new RenderObject();
			}
			this->_item_detail_list[item_type]->addChild(detail_label_ttf);
			

			// ���X�g�ɃA�C�e���I�u�W�F�N�g��ǉ�
			this->_detail_item_list[item_type][this->_item_detail_num_list[item_type]] = use_item_obj.second;
			this->_item_detail_num_list[item_type]++;

		}

		// ��ޓ��ɃA�C�e����1��ނł��\�������ꍇ
		if (this->_item_detail_num_list[item_type] > 0) {
			auto type_label_ttf = LabelTTF::create(type_name, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
			type_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
			auto anchor_point_type = new cocos2d::Vec2(0, 1);
			type_label_ttf->setAnchorPoint(*anchor_point_type);
			type_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_type_num * (-1)));
			this->_type_label_obj->addChild(type_label_ttf);

			this->_item_type_num++;

		}
	}
	
//	this->openUseItemDetailListInit(haveItemType::etc);
}
void ObjItemList::openItemDetailListInit(haveItemType item_type) {
	int test_break_point = 0;
	switch (item_type) {
		/*
		// �����n
	case haveItemType::weapon:
		this->openEquipItemDetailListInit(item_type);
		break;
		*/
		// �A�C�e���n
	case haveItemType::portion:
	case haveItemType::etc:
		this->openUseItemDetailListInit(item_type);
		break;
	}
}
void ObjItemList::openEquipItemDetailListInit(haveItemType item_type) {

	/*
	auto item_list_itr = this->_equip_item_list_detail.find(item_type);
	if (item_list_itr != this->_equip_item_list_detail.end()){
		return;
	}
	//*/

	this->_item_detail_num_list[item_type] = 0;

	unordered_map<int, EquipItem*> item_list_detail;
	bool get_flag = false;
	for (auto item_list_obj : *this->_equip_item_list_detail) {
		if (item_type == item_list_obj.first) {
			item_list_detail = item_list_obj.second;
			get_flag = true;
			break;
		}
	}
	if (get_flag != true) {
//		return;
	}
//	/*
	if (this->_item_detail_list[item_type] != nullptr) {
		this->_item_detail_list[item_type]->removeAllChildren();
	}
	for (auto use_item_obj : item_list_detail) {

		string name_string_data = use_item_obj.second->getItemName();
		auto detail_label_ttf = LabelTTF::create(name_string_data, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
		detail_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
		auto anchor_point_type = new cocos2d::Vec2(0, 1);
		detail_label_ttf->setAnchorPoint(*anchor_point_type);
		detail_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));
		//this->_type_label_obj->addChild(detail_label_ttf);

		if (this->_item_detail_list[item_type] == nullptr) {
			this->_item_detail_list[item_type] = new RenderObject();
		}

		this->_item_detail_list[item_type]->addChild(detail_label_ttf);

		// ���������ǂ����`�F�b�N�\��

		string equip_text = "��";
		auto equip_label_ttf = LabelTTF::create(equip_text, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE);
		equip_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
		auto anchor_point_equip = new cocos2d::Vec2(0, 1);
		equip_label_ttf->setAnchorPoint(*anchor_point_equip);
		equip_label_ttf->setPosition(-20, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));

		RenderObject* flag_render_obj = new RenderObject();
		flag_render_obj->addChild(equip_label_ttf);
		this->_equip_item_flag_list[item_type][use_item_obj.second] = flag_render_obj;

		if (use_item_obj.second->getEquipFlag() == true) {
			this->_item_detail_list[item_type]->addChild(this->_equip_item_flag_list[item_type][use_item_obj.second]);
//		this->_item_detail_list[item_type]->addChild(this->_equip_item_flag_list[item_type][use_item_obj.second]);
		}

		// ���X�g�ɃA�C�e���I�u�W�F�N�g��ǉ�
		this->_detail_item_list[item_type][this->_item_detail_num_list[item_type]] = use_item_obj.second;
		this->_item_detail_num_list[item_type]++;
	}


	// */
}
void ObjItemList::openUseItemDetailListInit(haveItemType item_type) {
	unordered_map<haveItemType, unordered_map<string, UseItem*>>* use_item_type_list = this->_use_item_list_detail;
	this->_item_detail_num_list[item_type] = 0;
	if (this->_item_detail_list[item_type] != nullptr) {
		this->_item_detail_list[item_type]->removeAllChildren();
	}
	for (auto use_item_obj : use_item_type_list->at(item_type)) {

		if (use_item_obj.second->getNum() <= 0) {
			continue;
		}
		/*
		this->_item_detail_list[item_type] += use_item_obj.second->getItemName();
		this->_item_detail_list[item_type] += "\n\n";
		*/

		string name_string_data = use_item_obj.second->getItemName();
		auto detail_label_ttf = LabelTTF::create(name_string_data, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
		detail_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
		auto anchor_point_type = new cocos2d::Vec2(0, 1);
		detail_label_ttf->setAnchorPoint(*anchor_point_type);
		detail_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));
		//this->_type_label_obj->addChild(detail_label_ttf);

		if (this->_item_detail_list[item_type] == nullptr) {
			this->_item_detail_list[item_type] = new RenderObject();
		}
		this->_item_detail_list[item_type]->addChild(detail_label_ttf);
		//*/

		// ���X�g�ɃA�C�e���I�u�W�F�N�g��ǉ�
		this->_detail_item_list[item_type][this->_item_detail_num_list[item_type]] = use_item_obj.second;
		this->_item_detail_num_list[item_type]++;
	}
}
string ObjItemList::getItemTypeName(haveItemType item_type) {

	string type_name = "�ȂȂ��̃^�C�v";
	switch (item_type) {
	case haveItemType::weapon:
		type_name = "�Ԃ�";
		break;
//	case haveItemType::body:
//		type_name = "�ӂ�";
//		break;
	case haveItemType::portion:
		type_name = "������";
		break;
	case haveItemType::etc:
		type_name = "���̂�";
		break;

	}

	return type_name;
}
void ObjItemList::openItemDetailInit(haveItemType item_type) {

	this->_detail_label_obj->removeAllChildren();
	this->_detail_label_obj->addChild(this->_item_detail_list[item_type]);
	this->_open_detail_type = item_type;

	// �\���ʒu������
	this->_item_detail_cursor = 0;
	this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_item_detail_cursor));

	this->addChild(this->_detail_bg_render_obj);
}
void ObjItemList::Update() {
	switch (this->_controll_type) {
	case 0:
		this->UpdateItemType();
		break;
	case 1:
		this->UpdateItemDetail();
		break;
	}
	
}
void ObjItemList::UpdateItemType() {

	if (this->_cursor_delay > 0) {
		this->_cursor_delay--;
		return;
	}



	// �J�[�\���ړ�����
	if (Gamepad::Down->isPush() == true) {
		// ���������ĂȂ��Ƃ��͉����������Ȃ�
		if (this->_item_type_num <= 0) {
			return;
		}

		this->_item_type_cursor += 1;

		if (this->_item_type_cursor >= this->_item_type_num) {
			this->_item_type_cursor = this->_item_type_num - 1;
		}

		this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_item_type_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;
	} else if (Gamepad::Up->isPush() == true) {
		// ���������ĂȂ��Ƃ��͉����������Ȃ�
		if (this->_item_type_num <= 0) {
			return;
		}

		this->_item_type_cursor -= 1;

		if (this->_item_type_cursor < 0) {
			this->_item_type_cursor = 0;
		}
		this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_item_type_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;
	}
	// �E���������ꍇ�A�ڍׂ�\������
	else if (Gamepad::Right->isPush() == true || Gamepad::Circle->isPush() == true) {
		// ���������ĂȂ��Ƃ��͉����������Ȃ�
		if (this->_item_type_num <= 0) {
			return;
		}
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		this->_controll_type = 1;

		this->openItemDetailInit(this->_type_list[this->_item_type_cursor]);
	}

}
void ObjItemList::UpdateItemDetail() {


	if (this->_cursor_delay > 0) {
		this->_cursor_delay--;
		return;
	}

	if (Gamepad::Down->isPush() == true) {
		this->_item_detail_cursor += 1;

		if (this->_item_detail_cursor >= this->_item_detail_num_list[this->_open_detail_type]) {
			this->_item_detail_cursor = this->_item_detail_num_list[this->_open_detail_type] - 1;
		}
		this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_item_detail_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;
	}
	else if (Gamepad::Up->isPush() == true) {
		this->_item_detail_cursor -= 1;

		if (this->_item_detail_cursor < 0) {
			this->_item_detail_cursor = 0;
		}
		this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_item_detail_cursor));
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		return;
	}
	// ���{�^���ŃA�C�e���g�p
	if (Gamepad::Circle->isPush() == true) {
		this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor]->useItem();

		this->useItemDrawUpdate(this->_open_detail_type, this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor]);

	}
	// ���{�^���ŃA�C�e����n��
	if (Gamepad::Square->isPush() == true) {

		this->transferItemObj();
	}
	// ���A�~�{�^���Ŏ�ވꗗ�֖߂�
	if (Gamepad::Left->isPush() == true || Gamepad::Cross->isPush() == true) {
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		this->_controll_type = 0;
		this->removeChild(this->_detail_bg_render_obj);
		this->_detail_label_obj->removeAllChildren();
//		this->openItemDetailInit(this->_type_list[this->_item_type_cursor]);
	}
}
//-------------------------------------------------------------------
//	�A�C�e���g�p���̕`��X�V
//-------------------------------------------------------------------
void ObjItemList::useItemDrawUpdate(haveItemType item_type, ItemBase* item_obj){
	switch (item_type) {
		// �����n
		case haveItemType::weapon:
		case haveItemType::armour:
			this->useItemDrawUpdateToEquip(item_type, (EquipItem*)item_obj);
		break;
		
		// �A�C�e���n
		case haveItemType::portion:
		case haveItemType::etc:
			this->useItemDrawUpdateToUse(item_type, (UseItem*)item_obj);
		break;
	// */
	}
}
void ObjItemList::useItemDrawUpdateToEquip(haveItemType item_type, EquipItem* item_obj) {
	bool equip_flag = item_obj->getEquipFlag();
	equipType equip_type = item_obj->getEquipType();
	if (equip_flag == true) {
		//equipType
		if (this->_equip_item_obj_list[equip_type] != nullptr) {
			this->removeEquipItem(this->_equip_item_obj_list[equip_type]);

		}

		RenderObject* flag_render_obj = this->_equip_item_flag_list[item_type][item_obj];
		this->_item_detail_list[item_type]->addChild(flag_render_obj);
		

		this->_equip_item_obj_list[equip_type] = item_obj;
	}
	else {
		this->_item_detail_list[item_type]->removeChild(this->_equip_item_flag_list[item_type][item_obj], true);
	}
}
void ObjItemList::useItemDrawUpdateToUse(haveItemType item_type, UseItem* item_obj) {
	if (item_obj->getNum() <= 0) {
		this->openUseItemDetailListInit(item_type);
	}
}
void ObjItemList::closeItemList() {
	this->_controll_type = 0;
	this->removeChild(this->_detail_bg_render_obj);
	this->_detail_label_obj->removeAllChildren();
}

void ObjItemList::removeEquipItem(EquipItem* remove_item_obj) {
	haveItemType item_type = remove_item_obj->getHaveItemType();
	equipType equip_type = remove_item_obj->getEquipType();

	RenderObject* remove_child_obj = this->_equip_item_flag_list[item_type][remove_item_obj];
	this->_item_detail_list[item_type]->removeChild(remove_child_obj, true);
	this->_equip_item_obj_list[equip_type] = nullptr;
}
//-------------------------------------------------------------------
// �A�C�e���ړ��n����
//-------------------------------------------------------------------
// �ڂ��O�̉������Ƃ��āA���葤�̃��X�g����ێ�
void ObjItemList::setObjItemListObj(ObjItemList* other_item_list_obj) {
	this->_other_item_list_obj = other_item_list_obj;
}
// �A�C�e���𑊎�ɓn��
void ObjItemList::transferItemObj() {
	if (this->_other_item_list_obj == nullptr || this->_open_only_flag == true) {
		return;
	}
	ItemBase* item_obj =  this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor];
	if (item_obj == nullptr) {

		return;
	}

	haveItemType item_type = item_obj->getHaveItemType();
	EquipItem* equip_item_obj = (EquipItem*)item_obj;
	UseItem* use_item_obj = (UseItem*)item_obj;

	switch (item_type) {
		// �����n
	case haveItemType::weapon:
	case haveItemType::armour:
		// �������͑���ɓn���Ȃ���
		if (equip_item_obj->getEquipFlag() == true) {
			return;
		}
		// ��ɓn���Ă��܂��ƁA�A�C�e���I�u�W�F�N�g������Index���X�V���Ă��܂��A������Index�ɎQ�Ƃł��Ȃ��Ȃ邽�߁A
		// �K�������̃A�C�e����j�����Ă���A�C�e����n������
		
		this->_equip_item_list->removeListToItem(equip_item_obj);
		this->removeEquipItemList(equip_item_obj);

		this->_other_item_list_obj->receiveEquipItemObj(equip_item_obj);

		
//		this->openItemListInit();
		
//		this->removeChild(this->_detail_bg_render_obj);
//		this->_detail_label_obj->removeAllChildren();
//		this->openItemListInit();
//		this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor] = nullptr;
		
		break;

		// �A�C�e���n
	case haveItemType::portion:
	case haveItemType::etc:
		this->useItemDrawUpdateToUse(item_type, (UseItem*)item_obj);
		break;
		// */
	}

//	this->openItemListInit();
}
// �A�C�e�����󂯎��i�����A�C�e��
void ObjItemList::receiveEquipItemObj(EquipItem* item_obj) {
//	this->_equip_item_list;
	this->_equip_item_list->setListToItem(item_obj);
	this->openEquipItemDetailListInit(item_obj->getHaveItemType());
//	this->openItemListInit();
}
// �A�C�e�����󂯎��i����A�C�e��
void ObjItemList::receiveUseItemObj(UseItem* item_obj) {
	this->_use_item_list->setItem(item_obj->getUseItemId(), 1);

//	this->openItemListInit();
}
// �A�C�e����j������i�����A�C�e��
void ObjItemList::removeEquipItemList(EquipItem* item_obj) {
	
	// �v�f���폜����

	if (item_obj == nullptr) {
		return;
	}
	auto item_list_itr = this->_detail_item_list[this->_open_detail_type].find(this->_item_detail_cursor);
	if (item_list_itr != this->_detail_item_list[this->_open_detail_type].end()){		// �L�[�̗v�f�����݂��Ă���ꍇ
		this->_detail_item_list[this->_open_detail_type].erase(item_list_itr);
	}

	this->openEquipItemDetailListInit(item_obj->getHaveItemType());
}