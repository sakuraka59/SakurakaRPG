#include "CraftUiBase.h"

#include "../../GAME_SETTING.h"
#include "../../../Input/Gamepad.h"

#include "../../chara/CharaPlayer.h"

#include "../../item/ItemBase.h"
#include "../../item/use_item/UseItem.h"
#include "../../item/haveItemType.h"
#include "../../item/use_item/HaveUseItemList.h"

#include "CraftRecipeDetail.h"
#include <unordered_set>
CraftUiBase::CraftUiBase(CharaPlayer* plauyer_obj) {
	this->_player_obj = plauyer_obj;

	int base_margin = 20;
	int label_margin = this->_SET_LABEL_MARGIN;

	// type ---------------------------------------------------------
	this->_type_bg_render_obj = this->getBgRenderObj();

	this->_type_label_obj = new RenderObject();
	this->_type_label_obj->setPosition(label_margin, 400);
	this->_type_bg_render_obj->addChild(this->_type_label_obj);

	// detail -------------------------------------------------------
	this->_detail_bg_render_obj = this->getBgRenderObj();

	this->_detail_label_obj = new RenderObject();
	this->_detail_label_obj->setPosition(label_margin, 400);
	this->_detail_bg_render_obj->addChild(this->_detail_label_obj);

	this->_detail_bg_render_obj->setPosition(200 + base_margin, 0);

	// staff --------------------------------------------------------

	this->_stuff_bg_render_obj = this->getStuffBgRenderObj();
	this->_stuff_label_obj = new RenderObject();
	for (int i = 0; i < this->_ITEM_SET_MAX; i++) {
		this->_stuff_label_list[i] = this->getLabelTTF(this->_NO_SETTING_TEXT);
		this->_stuff_label_list[i]->setPosition(0, (this->_TEXT_LINE_HEIGHT * (i + 1) * (-1)));
		this->_stuff_label_obj->addChild(this->_stuff_label_list[i]);
	}
	
	this->_stuff_label_obj->setPosition(label_margin, label_margin);
	this->_stuff_bg_render_obj->addChild(this->_stuff_label_obj);

	this->_stuff_bg_render_obj->setPosition(GAME_WIDTH / 2, GAME_HEIGHT - 50);
	// --------------------------------------------------------------
	this->addChild(this->_type_bg_render_obj);

	this->addChild(this->_stuff_bg_render_obj);

	// @TODO テスト用設定
	this->_use_item_type_list[haveItemType::portion] = haveItemType::portion;
	this->_use_item_type_list[haveItemType::food] = haveItemType::food;

	// 一覧初期化
	this->initTypeLabelList();


}
RenderObject* CraftUiBase::getBgRenderObj() {
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
	arrow_sprite->setPosition(180, 400 - (this->_FONT_SIZE / 2));
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
RenderObject* CraftUiBase::getStuffBgRenderObj() {
	RenderObject* bg_render_obj = new RenderObject();

	int bg_alpha = 128;
	int line_width = this->_LINE_WIDTH;
	int bg_width = this->_BG_WIDTH;
	int bg_height = (this->_TEXT_LINE_HEIGHT * this->_ITEM_SET_MAX) + (this->_SET_LABEL_MARGIN * 2) ;
	//---------------------------------------------------------------
	/*
	cocos2d::Rect arrow_rect = cocos2d::Rect(0, 0, 25, 2);
	cocos2d::Sprite* arrow_sprite = cocos2d::Sprite::create();

	arrow_sprite->setTextureRect(arrow_rect);
	arrow_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	arrow_sprite->setOpacity(255);

	auto anchor_point_arrow = new cocos2d::Vec2(0, 0);
	arrow_sprite->setAnchorPoint(*anchor_point_arrow);
	arrow_sprite->setPosition(180, 400 - (this->_FONT_SIZE / 2));
	bg_render_obj->addChild(arrow_sprite, 2);
	//*/
	//---------------------------------------------------------------


	cocos2d::Rect base_rect = cocos2d::Rect(0, 0, bg_width - (line_width * 2), bg_height);
	cocos2d::Sprite* base_sprite = cocos2d::Sprite::create();

	base_sprite->setTextureRect(base_rect);
	base_sprite->setColor(cocos2d::Color3B(0, 0, 0));
	base_sprite->setOpacity(bg_alpha);

	auto anchor_point_base = new cocos2d::Vec2(0, 0);
	base_sprite->setAnchorPoint(*anchor_point_base);
	base_sprite->setPosition(line_width, -(bg_height + line_width));
	bg_render_obj->addChild(base_sprite);

	// line side
	int line_height = bg_height + (line_width * 2);
	auto anchor_point_line = new cocos2d::Vec2(0, 0);
	Color3B line_color = cocos2d::Color3B(255, 255, 255);

	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, line_width, line_height);
	cocos2d::Sprite* frame_sprite = cocos2d::Sprite::create();

	frame_sprite->setTextureRect(frame_rect);
	frame_sprite->setColor(line_color);
	frame_sprite->setOpacity(bg_alpha);

	frame_sprite->setAnchorPoint(*anchor_point_line);
	frame_sprite->setPosition(0, -line_height);
	bg_render_obj->addChild(frame_sprite, 1);


	cocos2d::Rect frame_rect2 = cocos2d::Rect(0, 0, line_width, line_height);
	cocos2d::Sprite* frame_sprite2 = cocos2d::Sprite::create();

	frame_sprite2->setTextureRect(frame_rect2);
	frame_sprite2->setColor(line_color);
	frame_sprite2->setOpacity(bg_alpha);

	frame_sprite2->setAnchorPoint(*anchor_point_line);
	frame_sprite2->setPosition(bg_width - line_width, -line_height);
	bg_render_obj->addChild(frame_sprite2, 1);

	// line top bottom
	cocos2d::Rect frame_rect3 = cocos2d::Rect(0, 0, bg_width - (line_width * 2), line_width);
	cocos2d::Sprite* frame_sprite3 = cocos2d::Sprite::create();

	frame_sprite3->setTextureRect(frame_rect3);
	frame_sprite3->setColor(line_color);
	frame_sprite3->setOpacity(bg_alpha);

	frame_sprite3->setAnchorPoint(*anchor_point_line);
	frame_sprite3->setPosition(line_width, -line_width);
	bg_render_obj->addChild(frame_sprite3, 1);


	cocos2d::Rect frame_rect4 = cocos2d::Rect(0, 0, bg_width - (line_width * 2), line_width);
	cocos2d::Sprite* frame_sprite4 = cocos2d::Sprite::create();

	frame_sprite4->setTextureRect(frame_rect4);
	frame_sprite4->setColor(line_color);
	frame_sprite4->setOpacity(bg_alpha);

	frame_sprite4->setAnchorPoint(*anchor_point_line);
	frame_sprite4->setPosition(line_width, -(bg_height + (line_width * 2)));
	bg_render_obj->addChild(frame_sprite4, 1);

	return bg_render_obj;
}
// ------------------------------------------------------------------
void CraftUiBase::openUi() {
	this->removeChild(this->_detail_bg_render_obj);

	this->_controll_type = 0;

	this->_type_cursor = 0;
	this->_type_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_type_cursor));

	this->initTypeLabelList();
	this->_detail_label_obj->removeAllChildren();

	this->_stuff_set_num = 0;
	this->_set_item_stuff_list.clear();
	for (int i = 0; i < this->_ITEM_SET_MAX; i++) {
		this->_stuff_label_list[i]->setString(this->_NO_SETTING_TEXT);
		this->_set_item_count.clear();
	}

}
void CraftUiBase::closeUi() {

	this->removeChild(this->_detail_bg_render_obj);

	this->_detail_label_obj->removeAllChildren();
}
void CraftUiBase::openDetailList() {

	haveItemType item_type = this->_type_list[this->_type_cursor];

	this->_detail_label_obj->removeAllChildren();
	this->_detail_label_obj->addChild(this->_detail_label_list[item_type]);
	this->_open_detail_type = item_type;

	// 表示位置初期化
	this->_detail_cursor = 0;
	this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_detail_cursor));

	this->addChild(this->_detail_bg_render_obj);

	// 素材設定の初期化
//	this->_stuff_set_num = 0;
//	this->_set_item_stuff_list.clear();
}

void CraftUiBase::closeDetailList() {

	this->_cursor_delay = this->_CURSOR_DELAY_TIME;
	this->_controll_type = 0;
	this->removeChild(this->_detail_bg_render_obj);
	this->_detail_label_obj->removeAllChildren();
}
void CraftUiBase::initTypeLabelList() {
//	map<skillType, map<string, SkillBase*>> skill_type_list = this->_skill_list->getSkillTypeObjList();
	this->_type_label_obj->removeAllChildren();
	this->_type_num = 0;

	for (auto item_list : this->_use_item_type_list) {
		haveItemType skill_type = item_list.first;

		// まず詳細リストを作成
		bool set_detail_flag = this->initDetailLabelList(skill_type);

		//詳細リストがない場合、種別を追加しない
		if (set_detail_flag != true) {
			continue;
		}

		string type_name = this->getTypeName(skill_type);

		// ラベル取得
		LabelTTF* type_label_ttf = this->getLabelTTF(type_name);
		// 表示位置調整
		type_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_type_num * (-1)));

		this->_type_label_obj->addChild(type_label_ttf);


		this->_type_list[this->_type_num] = skill_type;

		this->_type_num++;
	}
}
bool CraftUiBase::initDetailLabelList(haveItemType item_type){

	//@TODO 面倒なので、現状はUseItem系のみ

	bool draw_flag = false;

	switch (item_type) {
	case haveItemType::portion:
	case haveItemType::food:
	case haveItemType::etc:

		draw_flag = this->initDetailLabelListToUse(item_type);
		break;
	}
	return draw_flag;
}
bool CraftUiBase::initDetailLabelListToUse(haveItemType item_type) {

	if (item_type != haveItemType::portion &&
		item_type != haveItemType::food &&
		item_type != haveItemType::etc
		) {
		return false;
	}

	this->_detail_num_list[item_type] = 0;
	if (this->_detail_label_list[item_type] != nullptr) {
		this->_detail_label_list[item_type]->removeAllChildren();
	}

	HaveUseItemList* item_list_obj = this->_player_obj->getHaveUseItemList();
	unordered_map<string, UseItem* > item_list = item_list_obj->getItemTypeDetailList(item_type);



	bool draw_flag = false;
	for (auto item_obj_base : item_list) {
		if (this->_detail_label_list[item_type] == nullptr) {
			this->_detail_label_list[item_type] = new RenderObject();
		}

		UseItem* item_obj = item_obj_base.second;
		int item_num = item_obj->getNum();

		string name_string_data = "";
		if (item_num >= 2) {
			name_string_data = item_obj->getItemName() + "(" + to_string(item_num) + ")";
		} else {
			name_string_data = item_obj->getItemName();
		}

		// ラベル取得
		LabelTTF* skill_name_label_ttf = this->getLabelTTF(name_string_data);
		// 表示位置調整
		skill_name_label_ttf->setPosition(0, (this->_TEXT_LINE_HEIGHT * this->_detail_num_list[item_type] * (-1)));

		this->_detail_label_list[item_type]->addChild(skill_name_label_ttf);

		this->_detail_list[item_type][this->_detail_num_list[item_type]] = item_obj;
		this->_detail_num_list[item_type]++;
		draw_flag = true;
	}
	return draw_flag;

}
void CraftUiBase::initOpenDetailList(haveItemType item_type) {
	this->_detail_label_obj->removeAllChildren();
	this->_detail_label_obj->addChild(this->_detail_label_list[item_type]);
	this->_open_detail_type = item_type;

	// 表示位置初期化
	this->_detail_cursor = 0;
	this->_detail_label_obj->setPositionY(400 + (this->_TEXT_LINE_HEIGHT * this->_detail_cursor));

	this->addChild(this->_detail_bg_render_obj);
}
// ------------------------------------------------------------------
void CraftUiBase::Update() {
	switch (this->_controll_type) {
	case 0:
		this->updateListType();
		break;
	case 1:
		this->updateListDetail();
		break;
	}
}
void CraftUiBase::updateListType() {
	if (this->_cursor_delay > 0) {
		this->_cursor_delay--;
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
	} else if (Gamepad::Right->isPush() == true || Gamepad::Circle->isPush() == true) {

		this->_cursor_delay = this->_CURSOR_DELAY_TIME;
		this->_controll_type = 1;

		this->openDetailList();
	}
}
void CraftUiBase::updateListDetail() {
	if (this->_cursor_delay > 0) {
		this->_cursor_delay--;
		return;
	}

	// 左、×ボタンで種類一覧へ戻る
	if (Gamepad::Left->isPush() == true || Gamepad::Cross->isPush() == true) {
		this->closeDetailList();
	}

	// リストに何もない場合は処理しない
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

		// ○ボタンを押した場合、材料としてセット
	} else if (Gamepad::Circle->isPush() == true) {
		this->setItemMaterial((UseItem*)this->_detail_list[this->_open_detail_type][this->_detail_cursor]);

		this->checkItemRecipe();
	} else if (Gamepad::Square->isPush() == true) {
		this->unsetItemMaterial();
		this->checkItemRecipe();
	}

}
// ------------------------------------------------------------------
bool CraftUiBase::setItemMaterial(UseItem* item_obj) {

	if (this->_stuff_set_num >= this->_ITEM_SET_MAX) {
		return false;
	}

	string item_id = item_obj->getUseItemId();
	if (this->_set_item_count[item_id] < 0) {
		this->_set_item_count[item_id] = 0;
	}

	// 所持数チェック
	if (item_obj->getNum() <= this->_set_item_count[item_id]) {
		return false;
	}


	this->_set_item_stuff_list[this->_stuff_set_num] = item_id;
	this->_stuff_label_list[this->_stuff_set_num]->setString(item_obj->getItemName());

	
	this->_set_item_count[item_id]++;

	this->_stuff_set_num++;

	return true;
}
bool CraftUiBase::unsetItemMaterial() {

	if (this->_stuff_set_num < 0) {
		this->_stuff_set_num = 0;
	}
	if (this->_stuff_set_num <= 0) {
		
		return false;
	}

	this->_stuff_set_num--;
	this->_set_item_count[this->_set_item_stuff_list[this->_stuff_set_num]]--;

	this->_set_item_stuff_list[this->_stuff_set_num] = "";
	this->_stuff_label_list[this->_stuff_set_num]->setString(this->_NO_SETTING_TEXT);



	return true;
}
bool CraftUiBase::checkItemRecipe() {

	CraftRecipeDetail* check_recipe_obj = new CraftRecipeDetail(
		this->_set_item_stuff_list[0],
		this->_set_item_stuff_list[1],
		this->_set_item_stuff_list[2],
		this->_set_item_stuff_list[3],
		"",
		1
	);

	// @TODO テストレシピ
//	map<CraftRecipeDetail*, int> recipe_test_list;
	set<CraftRecipeDetail*> recipe_test_list;
	CraftRecipeDetail* recipe_obj = new CraftRecipeDetail(
		"hard_bread_block",
		"",
		"",
		"",
		"hard_bread_slice",
		1
		);
	recipe_test_list.insert(recipe_obj);

	bool hoge = (recipe_obj < check_recipe_obj);
	if (recipe_test_list.find(check_recipe_obj) != recipe_test_list.end()) {
		return false;
	}
	bool test = check_recipe_obj==recipe_obj;
	if (test) {
		int piyo = 1;
	}


	// TEST

	testClass test_a(0);
	testClass test_b(0);

	bool test_c = false;
	test_c = test_a < test_b;
	return true;

	/*
	// @TODO テストレシピ
	unordered_map<string, unordered_map<string, unordered_map<string, unordered_map<string, string>>>> recipe_list;
	//recipe_test[0]
	recipe_list["hard_bread_block"][""][""][""] = "hard_bread_slice";

	// チェック用
	string check_recipe = recipe_list[this->_set_item_stuff_list[0]][this->_set_item_stuff_list[1]][this->_set_item_stuff_list[2]][this->_set_item_stuff_list[3]];
	if (check_recipe != "") {
		int hoge = 0;
		return true;
	}
	int piyo = 0;
	
	return false;
	*/
}
// ------------------------------------------------------------------
string CraftUiBase::getTypeName(haveItemType item_type) {
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
	// */
}
int CraftUiBase::getDrawWidth() {
	int width = (this->_BG_WIDTH + -(this->_LINE_WIDTH * 2));
//	int width = this->_BG_WIDTH;
	return width;
}
LabelTTF* CraftUiBase::getLabelTTF(string set_string_data) {

	LabelTTF* label_ttf = LabelTTF::create(set_string_data, this->_FONT_FILE, this->_FONT_SIZE, cocos2d::Size(200, GAME_HEIGHT), cocos2d::TextHAlignment::LEFT);
	label_ttf->setColor(cocos2d::Color3B(255, 255, 255));
	auto anchor_point_type = new cocos2d::Vec2(0, 1);
	label_ttf->setAnchorPoint(*anchor_point_type);

	return label_ttf;

}