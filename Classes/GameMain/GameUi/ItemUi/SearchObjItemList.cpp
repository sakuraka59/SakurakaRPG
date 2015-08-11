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