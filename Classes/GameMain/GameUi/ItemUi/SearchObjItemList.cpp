#include "SearchObjItemList.h"
#include "../../GAME_SETTING.h"
#include "../../../Input/Gamepad.h"

SearchObjItemList::SearchObjItemList() {
	/*

	*/
}
void SearchObjItemList::setBackGround() {
	// type ---------------------------------------------------------

	this->_type_bg_render_obj = this->getBgRenderObj();


	this->_type_label_obj->setPosition(20, 400);


	this->_type_bg_render_obj->addChild(this->_type_label_obj);

	// detail -------------------------------------------------------
	this->_detail_bg_render_obj = this->getBgRenderObj();


	this->_detail_label = "";

	
	this->_detail_label_obj->setPosition(20, 400);
	//	this->_type_label_obj->addChild(type_label_ttf);

	this->_detail_bg_render_obj->addChild(this->_detail_label_obj);

	this->_detail_bg_render_obj->setPosition(-220, 0);

	this->addChild(this->_type_bg_render_obj);
}
// 背景描画準備
RenderObject* SearchObjItemList::getBgRenderObj() {
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
	//	this->_bg_render_obj->setOpacity(128);
}

int SearchObjItemList::getDrawWidth() {
	int width = (this->_BG_WIDTH + -(this->_LINE_WIDTH * 2));
	return width;
}

void SearchObjItemList::UpdateItemType() {

	if (this->_cursor_delay > 0) {
		this->_cursor_delay--;
		return;
	}

	// カーソル移動処理
	if (Gamepad::Down->isPush() == true) {
		// 何も持ってないときは何も処理しない
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
	}
	else if (Gamepad::Up->isPush() == true) {
		// 何も持ってないときは何も処理しない
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
	// 右を押した場合、詳細を表示する
	else if (Gamepad::Left->isPush() == true || Gamepad::Circle->isPush() == true) {
		// 何も持ってないときは何も処理しない
		if (this->_item_type_num <= 0) {
			return;
		}
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		this->_controll_type = 1;

		this->openItemDetailInit(this->_type_list[this->_item_type_cursor]);
	}

}
void SearchObjItemList::UpdateItemDetail() {


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

	if (Gamepad::Circle->isPush() == true) {
		int hoge = 1;
		this->transferItemObj();
//		this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor]->useItem();
		//		this->openItemDetailListInit(this->_open_detail_type);
//		this->useItemDrawUpdate(this->_open_detail_type, this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor]);


	} else if (Gamepad::Square->isPush() == true) {

//		this->transferItemObj();
	}

	// 左、×ボタンで種類一覧へ戻る
	if (Gamepad::Right->isPush() == true || Gamepad::Cross->isPush() == true) {
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		this->_controll_type = 0;
		this->removeChild(this->_detail_bg_render_obj);
		this->_detail_label_obj->removeAllChildren();
		//		this->openItemDetailInit(this->_type_list[this->_item_type_cursor]);
	}
}








/*
#include "SearchObjItemList.h"

#include "../../GAME_SETTING.h"
#include "../../chara/CharaPlayer.h"

#include "../../item/equip_item/HaveEquipItemList.h"
#include "../../item/use_item/HaveUseItemList.h"
#include "../../item/haveItemType.h"

#include "../../item/equip_item/EquipItem.h"
#include "../../item/use_item/UseItem.h"
#include "../../item/ItemBase.h"

SearchObjItemList::SearchObjItemList() {
	// 背景

//	this->_list_bg_obj = this->getBgRenderObj();
//	this->addChild(this->_list_bg_obj);

//	RenderObject* hogr = this->getBgRenderObj();
//	hogr->setPosition(-220, 0);
//	this->addChild(hogr);
	

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

	this->_detail_bg_render_obj->setPosition(-220, 0);
}
void SearchObjItemList::Init(CharaPlayer* player_obj) {
	this->_player_obj = player_obj;
}
void SearchObjItemList::setItemList(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>> equip_item_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>> use_item_list
) {
	this->_equip_item_list = equip_item_list;
	this->_use_item_list = use_item_list;
}
void SearchObjItemList::Update() {

}
// アイテムを1つ入手する
void SearchObjItemList::getItem() {

}
void SearchObjItemList::getAllItem() {

}

// 背景描画準備
RenderObject* SearchObjItemList::getBgRenderObj() {
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
	//	this->_bg_render_obj->setOpacity(128);
}

int SearchObjItemList::getDrawWidth(){
	return this->_BG_WIDTH + (this->_LINE_WIDTH * 2);
}

// アイテム表示準備
void SearchObjItemList::openItemListDetail(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>>* use_item_type_list
) {

	//unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list = this->_equip_item_list->getItemTypeList();
	for (auto item_list_obj : *equip_item_type_list) {
		haveItemType item_type = item_list_obj.first;
		this->_type_list[this->_item_type_num] = item_type;
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

		if (this->_item_detail_list[item_type] != nullptr) {
			this->_item_detail_list[item_type]->removeAllChildren();
		}

		for (auto use_item_obj : item_list_obj.second) {

			

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

			// 装備中かどうかチェック表示

			string equip_text = "☆";
			auto equip_label_ttf = LabelTTF::create(equip_text, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE);
			equip_label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
			auto anchor_point_equip = new cocos2d::Vec2(0, 1);
			equip_label_ttf->setAnchorPoint(*anchor_point_equip);
			equip_label_ttf->setPosition(-20, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));

			RenderObject* flag_render_obj = new RenderObject();
			flag_render_obj->addChild(equip_label_ttf);
			this->_equip_item_flag_list[item_type][use_item_obj.second] = flag_render_obj;

			if (use_item_obj.second->getEquipFlag() == true) {
				//				this->_item_detail_list[item_type]->addChild(this->_equip_item_flag_list[item_type][use_item_obj.second]);
			}


			// リストにアイテムオブジェクトを追加
			this->_detail_item_list[item_type][this->_item_detail_num_list[item_type]] = use_item_obj.second;
			this->_item_detail_num_list[item_type]++;
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
			

			// リストにアイテムオブジェクトを追加
			this->_detail_item_list[item_type][this->_item_detail_num_list[item_type]] = use_item_obj.second;
			this->_item_detail_num_list[item_type]++;

		}

		// 種類内にアイテムが1種類でも表示される場合
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
}

// */