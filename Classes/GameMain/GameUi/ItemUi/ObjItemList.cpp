#include "ObjItemList.h"

#include "../../GAME_SETTING.h"
#include "../../../Input/Gamepad.h"

#include "../../item/equip_item/HaveEquipItemList.h"
#include "../../item/use_item/HaveUseItemList.h"
#include "../../item/haveItemType.h"

#include "../../item/equip_item/EquipItem.h"
#include "../../item/use_item/UseItem.h"
#include "../../item/ItemBase.h"

#include "../../chara/CharaPlayer.h"
#include "../ControllSettingUi.h"

ObjItemList::ObjItemList() {
	this->_type_label_obj = new RenderObject();
	this->_detail_label_obj = new RenderObject();
}
void ObjItemList::setCharaPlayer(CharaPlayer* chara_obj) {
	this->_chara_obj = chara_obj;
	// controll setting ui 
	this->_controll_setting_ui_obj = new ControllSettingUi(chara_obj, controllSettingType::item);
	this->_controll_setting_ui_obj->setPosition(220 * 2, 0);
	
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
	// カーソル初期位置へ
	this->_item_type_cursor = 0;
	this->_controll_type = 0;
	this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_item_type_cursor));
}
void ObjItemList::setOnlyFlag(bool open_only_flag) {
	this->_open_only_flag = open_only_flag;
}

// 一覧開く
void ObjItemList::openItemListInit(){
//	for (int i = (int)haveItemType::_no_type; i < (int)haveItemType::_enum_end; i++) {

//	}

	this->initCursorPosition();

//	this->_use_item_list->getItemTypeList();
//	this->_equip_item_list->getItemTypeList();

	this->_item_type_num = 0;

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



		this->openEquipItemDetailListInit(item_type);


		if (this->_item_detail_num_list[item_type] > 0) {
			auto type_label_ttf = LabelTTF::create(type_name, this->_FONT_FILE, this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
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


		this->_type_list[this->_item_type_num] = item_type;
		this->openUseItemDetailListInit(item_type);
		

		// 種類内にアイテムが1種類でも表示される場合
		if (this->_item_detail_num_list[item_type] > 0) {
			auto type_label_ttf = LabelTTF::create(type_name, this->_FONT_FILE, this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
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
		// 装備系
	case haveItemType::weapon:
		this->openEquipItemDetailListInit(item_type);
		break;
		*/
		// アイテム系
	case haveItemType::portion:
	case haveItemType::food:
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
		auto detail_label_ttf = LabelTTF::create(name_string_data, this->_FONT_FILE, this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
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
		auto equip_label_ttf = LabelTTF::create(equip_text, this->_FONT_FILE, this->_FONT_SIZE);
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

		// リストにアイテムオブジェクトを追加
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
	for (auto use_item_obj_base : use_item_type_list->at(item_type)) {

		UseItem* use_item_obj = use_item_obj_base.second;
		int item_num = use_item_obj->getNum();
		if (item_num <= 0) {
			continue;
		}
		/*
		this->_item_detail_list[item_type] += use_item_obj->getItemName();
		this->_item_detail_list[item_type] += "\n\n";
		*/

		string name_string_data = "";
		
		if (item_num >= 2) {
			name_string_data = use_item_obj->getItemName() + "(" + to_string(item_num) + ")";
		} else {
			name_string_data = use_item_obj->getItemName();
		}


		this->_use_item_label_list[use_item_obj] = LabelTTF::create(name_string_data, this->_FONT_FILE, this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
		this->_use_item_label_list[use_item_obj]->setColor(cocos2d::Color3B(255, 255, 255));
		auto anchor_point_type = new cocos2d::Vec2(0, 1);
		this->_use_item_label_list[use_item_obj]->setAnchorPoint(*anchor_point_type);
		this->_use_item_label_list[use_item_obj]->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_item_detail_num_list[item_type] * (-1)));
		//this->_type_label_obj->addChild(detail_label_ttf);


		if (this->_item_detail_list[item_type] == nullptr) {
			this->_item_detail_list[item_type] = new RenderObject();
		}
		this->_item_detail_list[item_type]->addChild(this->_use_item_label_list[use_item_obj]);
		//*/

		// リストにアイテムオブジェクトを追加
		this->_detail_item_list[item_type][this->_item_detail_num_list[item_type]] = use_item_obj;
		this->_item_detail_num_list[item_type]++;
	}
}
string ObjItemList::getItemTypeName(haveItemType item_type) {
	return _getHaveItemTypeName(item_type);
	/*
	string type_name = "ななしのタイプ";
	switch (item_type) {
	case haveItemType::weapon:
		type_name = "ぶき";
		break;
//	case haveItemType::body:
//		type_name = "ふく";
//		break;
	case haveItemType::portion:
		type_name = "くすり";
		break;
	case haveItemType::food:
		type_name = "たべもの";
		break;
	case haveItemType::etc:
		type_name = "そのた";
		break;

	}

	return type_name;
	*/
}
void ObjItemList::openItemDetailInit(haveItemType item_type) {

	this->_detail_label_obj->removeAllChildren();
	this->_detail_label_obj->addChild(this->_item_detail_list[item_type]);
	this->_open_detail_type = item_type;

	// 表示位置初期化
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
	case 2:
		this->_controll_setting_ui_obj->Update();

		// セット閉じた場合、1つ前にもどす
		if (this->_controll_setting_ui_obj->getDrawFlag() != true) {
			this->_controll_type = 1;
			this->removeChild(this->_controll_setting_ui_obj);
		}
		break;
	}
	
}
//-------------------------------------------------------------------
// 所持しているアイテムの種類一覧を再描画
//-------------------------------------------------------------------
void ObjItemList::resetItemTypeList() {

	this->_item_type_num = 0;

	this->_type_label_obj->removeAllChildren();

	// @TODO 所持アイテム種類簡易初期化。
	this->openItemListDetail(this->_equip_item_list_detail, this->_use_item_list_detail);



	
}
void ObjItemList::UpdateItemType() {

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
	} else if (Gamepad::Up->isPush() == true) {
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
	else if (Gamepad::Right->isPush() == true || Gamepad::Circle->isPush() == true) {
		// 何も持ってないときは何も処理しない
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
	// ○ボタンでアイテム使用
	else if (Gamepad::Circle->isPush() == true) {
		this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor]->useItem();

		this->useItemDrawUpdate(this->_open_detail_type, this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor]);

	}
	// □ボタンでショートカット設定を出す
	else if (Gamepad::Square->isPush() == true || Gamepad::Right->isPush() == true) {

		// 現状ではポーションのみ設定可能
		if (this->_open_detail_type != haveItemType::portion ||
			this->_open_detail_type != haveItemType::food) {
			return;
		}
		this->_controll_type = 2;
		this->_controll_setting_ui_obj->openUiToItem((UseItem*)this->_detail_item_list[this->_open_detail_type][this->_item_detail_cursor]);
		this->addChild(this->_controll_setting_ui_obj);
		int hoge = 1;
//		this->_controll_setting_ui_obj->openUiToSkill(this->_detail_skill_list[this->_open_detail_type][this->_detail_cursor]);
	}
	// R2ボタンでアイテムを渡す
	else if (Gamepad::R2->isPush() == true) {
		this->transferItemObj();
	}
	// 左、×ボタンで種類一覧へ戻る
	else if (Gamepad::Left->isPush() == true || Gamepad::Cross->isPush() == true) {
		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		this->_controll_type = 0;
		this->removeChild(this->_detail_bg_render_obj);
		this->_detail_label_obj->removeAllChildren();
//		this->openItemDetailInit(this->_type_list[this->_item_type_cursor]);
	}
}
//-------------------------------------------------------------------
//	アイテム使用時の描画更新
//-------------------------------------------------------------------
void ObjItemList::useItemDrawUpdate(haveItemType item_type, ItemBase* item_obj){
	switch (item_type) {
		// 装備系
		case haveItemType::weapon:
		case haveItemType::armour:
			this->useItemDrawUpdateToEquip(item_type, (EquipItem*)item_obj);
		break;
		
		// アイテム系
		case haveItemType::portion:
		case haveItemType::food:
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
		this->_item_detail_num_list[item_type]++;
		
		this->openUseItemDetailListInit(item_type);

		/*
		if (this->_item_detail_num_list[item_type] <= 1) {
//			this->resetItemTypeList();
//			this->openItemListInit();
		}
		*/

	} else  {
		int item_num = item_obj->getNum();
		string name_string_data = "";

		if (item_num >= 2) {
			name_string_data = item_obj->getItemName() + "(" + to_string(item_num) + ")";
		} else {
			name_string_data = item_obj->getItemName();
		}
		this->_use_item_label_list[item_obj]->setString(name_string_data);
	}
}
void ObjItemList::closeItemList() {
	this->_controll_type = 0;
	this->removeChild(this->_detail_bg_render_obj);
	this->_detail_label_obj->removeAllChildren();

	if (this->_controll_setting_ui_obj != nullptr) {
		this->removeChild(this->_controll_setting_ui_obj);
	}
	
}

void ObjItemList::removeEquipItem(EquipItem* remove_item_obj) {
	haveItemType item_type = remove_item_obj->getHaveItemType();
	equipType equip_type = remove_item_obj->getEquipType();

	RenderObject* remove_child_obj = this->_equip_item_flag_list[item_type][remove_item_obj];
	this->_item_detail_list[item_type]->removeChild(remove_child_obj, true);
	this->_equip_item_obj_list[equip_type] = nullptr;
}
//-------------------------------------------------------------------
// アイテム移動系処理
//-------------------------------------------------------------------
// 移す前の下準備として、相手側のリスト情報を保持
void ObjItemList::setObjItemListObj(ObjItemList* other_item_list_obj) {
	this->_other_item_list_obj = other_item_list_obj;
}
// アイテムを相手に渡す
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
		// 装備系
	case haveItemType::weapon:
	case haveItemType::armour:
		// 装備中は相手に渡せないよ
		if (equip_item_obj->getEquipFlag() == true) {
			return;
		}
		// 先に渡してしまうと、アイテムオブジェクトが持つIndexを更新してしまい、元側のIndexに参照できなくなるため、
		// 必ず元側のアイテムを破棄してからアイテムを渡すこと
		
		this->_equip_item_list->removeListToItem(equip_item_obj);
		this->removeEquipItemList(equip_item_obj);

		this->_other_item_list_obj->receiveEquipItemObj(equip_item_obj);
//		this->_other_item_list_obj->openUseItemDetailListInit(item_type);
		this->_other_item_list_obj->resetItemTypeList();

		break;

		// アイテム系
	case haveItemType::portion:
	case haveItemType::food:
	case haveItemType::etc:
		if (this->removeUseItemList(use_item_obj) != true) {
			break;
		}
		this->_other_item_list_obj->receiveUseItemObj(use_item_obj);

		this->useItemDrawUpdateToUse(item_type, use_item_obj);
		this->_other_item_list_obj->resetItemTypeList();

//		this->_other_item_list_obj->openUseItemDetailListInit(item_type);
//		this->_other_item_list_objopenItemListInit();


		
		break;
		// */
	}

//	this->openItemListInit();
}
// アイテムを受け取る（装備アイテム
void ObjItemList::receiveEquipItemObj(EquipItem* item_obj) {
//	this->_equip_item_list;
	this->_equip_item_list->setListToItem(item_obj);
	this->openEquipItemDetailListInit(item_obj->getHaveItemType());
//	this->openItemListInit();
}
// アイテムを受け取る（消費アイテム
void ObjItemList::receiveUseItemObj(UseItem* item_obj) {
	this->_use_item_list->setItem(item_obj, 1);

	

//	this->openItemListInit();
}
// アイテムを破棄する（装備アイテム
void ObjItemList::removeEquipItemList(EquipItem* item_obj) {
	
	// 要素を削除する

	if (item_obj == nullptr) {
		return;
	}
	auto item_list_itr = this->_detail_item_list[this->_open_detail_type].find(this->_item_detail_cursor);
	if (item_list_itr != this->_detail_item_list[this->_open_detail_type].end()){		// キーの要素が存在している場合
		this->_detail_item_list[this->_open_detail_type].erase(item_list_itr);
	}

	this->openEquipItemDetailListInit(item_obj->getHaveItemType());
}

bool ObjItemList::removeUseItemList(UseItem* item_obj) {
	return item_obj->removeUseItem(1);
}
