#include "PlayerCommentUI.h"
#include "PlayerComment.h"
#include "../GAME_SETTING.h"

PlayerCommentUI::PlayerCommentUI() {

	/*
	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, 100, 100);
	cocos2d::Sprite* base_sprite = cocos2d::Sprite::create();

	base_sprite->setTextureRect(frame_rect);
	base_sprite->setColor(cocos2d::Color3B(30, 30, 30));
	//base_sprite->setOpacity(this->_base_alpha);

	auto anchor_point = new cocos2d::Vec2(0, 0);
	base_sprite->setAnchorPoint(*anchor_point);
	base_sprite->setPosition(0, 0);
	this->addChild(base_sprite);
	*/
	this->setPosition(GAME_WIDTH - 202, 500);
}
void PlayerCommentUI::Update() {
	
	int now_comment_correct_y = 0;

	int now_comment_line = 0;
//	int FONT_SIZE = 14;
	// 一度、コメントすべてのライン数を取得する
	for (auto comment_data : this->_comment_list) {

		now_comment_line += comment_data.second->getCommentLine();
		int comment_obj_height = comment_data.second->commentObjHeight();
		now_comment_correct_y += comment_obj_height;
	}
//	now_comment_correct_y = ((5 + 16) * this->_comment_count) + (14 * now_comment_line);
//	now_comment_correct_y = FONT_SIZE * now_comment_line;
	for(auto comment_data : this->_comment_list) {

		if (comment_data.second->getBreakFlag() == true) {
			//comment_data
			this->removeChild(comment_data.second, true);
		}
		
		//now_comment_correct_y -= 5 + 16 + (comment_data.second->getFontSize() * comment_data.second->getCommentLine());
		int font_size_comment = comment_data.second->getFontHeight();
		int comment_line = comment_data.second->getCommentLine();
		//now_comment_correct_y -= (comment_data.second->getFontSize() * comment_data.second->getCommentLine());
		int comment_obj_height = comment_data.second->commentObjHeight();
		now_comment_correct_y -= (comment_obj_height);
		comment_data.second->Update(now_comment_correct_y);
	}
	//*/
}
//-----------------------------------------------------------
//	コメントを新規追加する
//-----------------------------------------------------------
void PlayerCommentUI::setComment(std::string comment) {


	if (this->_comment_count < this->_COMMENT_MAX) {

		this->_comment_list[this->_comment_count] = new PlayerComment(comment);
		this->addChild(this->_comment_list[this->_comment_count]);
		this->_comment_count++;

	} else {

		this->removeChild(this->_comment_list[0], true);
		this->_comment_list[0] = nullptr;
		for (int i = 1; i < this->_COMMENT_MAX; i++) {

			this->_comment_list[i - 1] = this->_comment_list[i];
		}
		this->_comment_list[this->_COMMENT_MAX - 1] = new PlayerComment(comment);
		this->addChild(this->_comment_list[this->_COMMENT_MAX - 1]);

	}
}