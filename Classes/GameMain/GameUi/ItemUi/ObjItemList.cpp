#include "ObjItemList.h"
#include "../../GAME_SETTING.h"

#include "../../item/equip_item/HaveEquipItemList.h"
#include "../../item/use_item/HaveUseItemList.h"
#include "../../item/haveItemType.h"

#include "../../item/equip_item/EquipItem.h"
#include "../../item/use_item/UseItem.h"

ObjItemList::ObjItemList(HaveUseItemList* use_item_list, HaveEquipItemList* equip_item_list) {

	this->_equip_item_list = equip_item_list;
	this->_use_item_list = use_item_list;

	// type ---------------------------------------------------------

	this->_type_bg_render_obj = this->getBgRenderObj();
	/*
	this->_type_label = "hoge";

	LabelTTF* type_label_ttf = LabelTTF::create(this->_type_label, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
	type_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
	auto anchor_point_type = new cocos2d::Vec2(0, 1);
	type_label_ttf->setAnchorPoint(*anchor_point_type);
	type_label_ttf->setPosition(0, 0);
	*/
	this->_type_label_obj = new RenderObject();
	this->_type_label_obj->setPosition(30, 400);
//	this->_type_label_obj->addChild(type_label_ttf);

	this->_type_bg_render_obj->addChild(this->_type_label_obj);

	// detail -------------------------------------------------------
	this->_detail_bg_render_obj = this->getBgRenderObj();

	
	this->_detail_label = "hoge";

	LabelTTF* type_label_ttf = LabelTTF::create(this->_type_label, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
	type_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
	auto anchor_point_type = new cocos2d::Vec2(0, 1);
	type_label_ttf->setAnchorPoint(*anchor_point_type);
	type_label_ttf->setPosition(0, 0);

	this->_detail_label_obj = new RenderObject();
	this->_detail_label_obj->setPosition(30, 400);
//	this->_type_label_obj->addChild(type_label_ttf);

	this->_detail_bg_render_obj->addChild(this->_detail_label_obj);
	//*/
	this->_detail_bg_render_obj->setPosition(220, 0);
	// test ---------------------------------------------------------
	this->openItemListInit();
	this->openItemDetailInit(haveItemType::portion);
	// --------------------------------------------------------------
	

	this->addChild(this->_type_bg_render_obj);
	this->addChild(this->_detail_bg_render_obj);
	//this->addChild(;
}
RenderObject* ObjItemList::getBgRenderObj() {
	RenderObject* bg_render_obj = new RenderObject();

	int bg_alpha = 128;
	int line_width = 5;
	int bg_width = 200;

	//---------------------------------------------------------------
	cocos2d::Rect arrow_rect = cocos2d::Rect(0, 0, 35, 2);
	cocos2d::Sprite* arrow_sprite = cocos2d::Sprite::create();

	arrow_sprite->setTextureRect(arrow_rect);
	arrow_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	arrow_sprite->setOpacity(255);

	auto anchor_point_arrow = new cocos2d::Vec2(0, 0);
	arrow_sprite->setAnchorPoint(*anchor_point_arrow);
	arrow_sprite->setPosition(170, 400 - (this->_FONT_SIZE/2));
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
void ObjItemList::openItemListInit(){
//	for (int i = (int)haveItemType::_no_type; i < (int)haveItemType::_enum_end; i++) {

//	}
	this->_use_item_list->getItemTypeList();
	this->_equip_item_list->getItemTypeList();

	this->_item_type_num = 0;
	this->_type_label = "";
	this->_type_label_obj->removeAllChildren();

	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list = this->_equip_item_list->getItemTypeList();
	for (auto item_list_obj : *equip_item_type_list) {
		haveItemType item_type = item_list_obj.first;
		string type_name = this->getItemTypeName(item_type);
//		this->_type_label += type_name + "\n\n";
		

		auto type_label_ttf = LabelTTF::create(type_name, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
		type_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
		auto anchor_point_type = new cocos2d::Vec2(0, 1);
		type_label_ttf->setAnchorPoint(*anchor_point_type);
		type_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_type_num * (-1)));
		this->_type_label_obj->addChild(type_label_ttf);

		this->_item_type_num++;

		this->_item_detail_num_list[item_type] = 0;
		for (auto use_item_obj : item_list_obj.second) {

			/*
			this->_item_detail_list[item_type] += use_item_obj.second->getItemName();
			this->_item_detail_list[item_type] += "\n\n";
			*/

			auto detail_label_ttf = LabelTTF::create(use_item_obj.second->getItemName(), "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
			detail_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
			auto anchor_point_type = new cocos2d::Vec2(0, 1);
			detail_label_ttf->setAnchorPoint(*anchor_point_type);
			detail_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));
			//this->_type_label_obj->addChild(detail_label_ttf);

			if (this->_item_detail_list[item_type] == nullptr) {
				this->_item_detail_list[item_type] = new RenderObject();
			} else {
				this->_item_detail_list[item_type]->removeAllChildren();
			}
			this->_item_detail_list[item_type]->addChild(detail_label_ttf);


			this->_item_detail_num_list[item_type]++;
		}
	}

	unordered_map<haveItemType, unordered_map<useItemId, UseItem*>>* use_item_type_list = this->_use_item_list->getItemTypeList();
	for (auto item_list_obj : *use_item_type_list) {
		haveItemType item_type = item_list_obj.first;
		string type_name = this->getItemTypeName(item_type);
//		this->_type_label += type_name + "\n\n";

		auto type_label_ttf = LabelTTF::create(type_name, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
		type_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
		auto anchor_point_type = new cocos2d::Vec2(0, 1);
		type_label_ttf->setAnchorPoint(*anchor_point_type);
		type_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_type_num * (-1)));
		this->_type_label_obj->addChild(type_label_ttf);

		this->_item_type_num++;

		this->_item_detail_num_list[item_type] = 0;
		for (auto use_item_obj : item_list_obj.second) {
			/*
			this->_item_detail_list[item_type] += use_item_obj.second->getItemName();
			this->_item_detail_list[item_type] += "\n\n";
			*/
			auto detail_label_ttf = LabelTTF::create(use_item_obj.second->getItemName(), "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
			detail_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
			auto anchor_point_type = new cocos2d::Vec2(0, 1);
			detail_label_ttf->setAnchorPoint(*anchor_point_type);
			detail_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));
			//this->_type_label_obj->addChild(detail_label_ttf);
			
			if (this->_item_detail_list[item_type] == nullptr) {
				this->_item_detail_list[item_type] = new RenderObject();
			} else {
				this->_item_detail_list[item_type]->removeAllChildren();
			}
			this->_item_detail_list[item_type]->addChild(detail_label_ttf);
			//*/
			this->_item_detail_num_list[item_type]++;
		}		
	}



//	this->_type_label_obj->setString(this->_type_label);
}
string ObjItemList::getItemTypeName(haveItemType item_type) {

	string type_name = "ななしのタイプ";
	switch (item_type) {
	case haveItemType::weapon:
		type_name = "ぶき";
		break;
	case haveItemType::body:
		type_name = "ふく";
		break;
	case haveItemType::portion:
		type_name = "くすり";
		break;
	case haveItemType::etc:
		type_name = "そのた";
		break;

	}

	return type_name;
}
void ObjItemList::openItemDetailInit(haveItemType item_type) {
//	this->_detail_label = this->_item_detail_list[item_type];
//	this->_detail_label_obj->setString(this->_detail_label);
	this->_detail_label_obj->addChild(this->_item_detail_list[item_type]);
}
void ObjItemList::Update() {

}