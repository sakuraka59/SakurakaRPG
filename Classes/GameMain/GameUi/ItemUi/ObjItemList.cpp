#include "ObjItemList.h"
#include "../../GAME_SETTING.h"

#include "../../item/equip_item/HaveEquipItemList.h"
#include "../../item/use_item/HaveUseItemList.h"
#include "../../item/haveItemType.h"

ObjItemList::ObjItemList(HaveUseItemList* use_item_list, HaveEquipItemList* equip_item_list) {

	this->_equip_item_list = equip_item_list;
	this->_use_item_list = use_item_list;

	this->_type_bg_render_obj = this->getBgRenderObj();
	// base



	this->addChild(this->_type_bg_render_obj);
}
RenderObject* ObjItemList::getBgRenderObj() {
	RenderObject* bg_render_obj = new RenderObject();

	int bg_alpha = 128;
	int line_width = 5;
	int bg_width = 200;
	cocos2d::Rect base_rect = cocos2d::Rect(0, 0, bg_width - (line_width * 2), GAME_HEIGHT);
	cocos2d::Sprite* base_sprite = cocos2d::Sprite::create();

	base_sprite->setTextureRect(base_rect);
	base_sprite->setColor(cocos2d::Color3B(0, 0, 0));
	base_sprite->setOpacity(bg_alpha);

	auto anchor_point_base = new cocos2d::Vec2(0, 0);
	base_sprite->setAnchorPoint(*anchor_point_base);
	base_sprite->setPosition(line_width, 0);
	bg_render_obj->addChild(base_sprite);

	// line

	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, 5, GAME_HEIGHT);
	cocos2d::Sprite* frame_sprite = cocos2d::Sprite::create();

	frame_sprite->setTextureRect(frame_rect);
	frame_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite->setOpacity(bg_alpha);

	auto anchor_point_line = new cocos2d::Vec2(0, 0);
	frame_sprite->setAnchorPoint(*anchor_point_line);
	frame_sprite->setPosition(0, 0);
	bg_render_obj->addChild(frame_sprite);

	cocos2d::Rect frame_rect2 = cocos2d::Rect(0, 0, 5, GAME_HEIGHT);
	cocos2d::Sprite* frame_sprite2 = cocos2d::Sprite::create();

	frame_sprite2->setTextureRect(frame_rect2);
	frame_sprite2->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite2->setOpacity(bg_alpha);

	frame_sprite2->setAnchorPoint(*anchor_point_line);
	frame_sprite2->setPosition(bg_width - line_width, 0);
	bg_render_obj->addChild(frame_sprite2);

	return bg_render_obj;
	//	this->_bg_render_obj->setOpacity(128);
}
void ObjItemList::openItemListInit(){
//	for (int i = (int)haveItemType::_no_type; i < (int)haveItemType::_enum_end; i++) {

//	}
	this->_use_item_list->getItemTypeList();
	this->_equip_item_list->getItemTypeList();
	for (auto use_item_list_obj : this->_use_item_list->getItemTypeList()) {
		
	}
}