#include "PlayerComment.h"

PlayerComment::PlayerComment(std::string comment)
{

	int line = this->getCommentLine(comment) + 1;
	int text_width = this->oneLineWidth(comment);
	
	// コメントの投稿行数を取得
	this->_comment_line = line;

	this->_font_height = this->_FONT_SIZE + 2;
	// 背景に１ドットのテクスチャを使用（引き伸ばしてつかう）
	int comment_width = (text_width * this->_FONT_SIZE) / 1;// +(this->_BASE_WIDTH_MARGIN * 2);
	int comment_height = (this->_font_height * this->_comment_line);
	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, comment_width, comment_height);
	this->_base_sprite = cocos2d::Sprite::create();

	this->_base_sprite->setTextureRect(frame_rect);
//	this->_base_sprite->setColor(cocos2d::Color3B(255, 255 * 0.7, 255 * 0.8));
	this->_base_sprite->setColor(cocos2d::Color3B(0, 0, 0));
	this->_base_sprite->setOpacity(this->_base_alpha);

	this->_base_sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
	this->_base_sprite->setPosition(0, 0);
	this->addChild(this->_base_sprite);

	/*
	var texture_info = Director.Instance.GL.WhiteTextureInfo;
	this->_base_sprite = new SpriteUV(){ TextureInfo = texture_info };

	// コメントの投稿行数を取得
	this->_comment_line = line;
	int comment_width = (this->_BASE_WIDTH_MARGIN * 2) + text_width * this->_FONT_SIZE;

	// this->_base_sprite.Scale = new Vector2(this->_BASE_WIDTH ,16 + (this->_FONT_SIZE * this->_comment_line));
	this->_base_sprite.Scale = new Vector2(comment_width, 16 + (this->_FONT_SIZE * this->_comment_line));

	this->_base_sprite.Color = new Vector4(1.0f, 0.7f, 0.8f, (float)((float)this->_base_alpha / 100));
	this->_base_sprite.BlendMode = BlendMode.Normal;

	if (this->_comment_line == 1) {
		this->_base_sprite.Position = new Vector2(0, this->_FONT_SIZE);
	}
	this->AddChild(this->_base_sprite);

	this->_comment_label = new Label();
	*/


	this->_label_obj = cocos2d::LabelTTF::create(comment, "fonts/arial.ttf", this->_FONT_SIZE, cocos2d::Size(comment_width, comment_height), cocos2d::TextHAlignment::LEFT);
	this->_label_obj->setColor(cocos2d::Color3B::WHITE);
	this->_label_obj->setOpacity(this->_text_alpha);
	this->_label_obj->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
	this->_label_obj->setPosition(0, 0);
	this->addChild(this->_label_obj);


	/*
	Font test_comment_font = new Font("/Application/res/font/uzura.ttf", this->_FONT_SIZE, FontStyle.Regular);
	this->_comment_label.FontMap = new FontMap(test_comment_font, comment, 1024);
	//			this->_comment_label.FontMap = new FontMap( comment_font, comment ,1024);

	this->_comment_label.Text = comment;
	this->_comment_label.Color = new Vector4(1.0f, 1.0f, 1.0f, (float)((float)this->_text_alpha / 100));
	this->_comment_label.Position = new Vector2(this->_BASE_WIDTH_MARGIN, this->_FONT_SIZE + 8);
	this->AddChild(this->_comment_label);
	//*/
	// 初期表示座標補正
	this->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));

	this->_insert_move_x = comment_width;
	this->_correct_x = comment_width - 200;
	this->setPosition(this->_BASE_POSITION_X - this->_correct_x + this->_insert_move_x, 0);
	
	// 5秒間表示
	this->_set_view_count = this->_COMMENT_VIEW_FRAME;

}

void PlayerComment::Update(int now_comment_correct_y) {

	if (this->_set_view_count > 0) {
		this->commentStartAnime();
		this->_set_view_count--;
	}
	else {
		bool anime_end_flag = this->commentEndAnime();
		if (anime_end_flag == true) {
			// このオブジェクトを破棄させる
			this->_break_flag = true;
		}
	}


	// 描画位置の修正
	this->setPosition(this->_BASE_POSITION_X - this->_correct_x + this->_insert_move_x, now_comment_correct_y);

}
//-----------------------------------------------------------
// 投稿直後のアニメーション動作
//-----------------------------------------------------------
void PlayerComment::commentStartAnime() {


	if (this->_base_alpha < this->_MAX_BASE_ALPHA) {
		//this->_base_sprite.Color = new Vector4(1.0f, 0.7f, 0.8f, (float)((float)this->_base_alpha / 100));
		this->_base_sprite->setOpacity(this->_base_alpha);
		this->_base_alpha += this->_ADD_BASE_ALPHA;
	}
	if (this->_base_alpha > this->_MAX_BASE_ALPHA) {
		this->_base_alpha = this->_MAX_BASE_ALPHA;

		this->_base_sprite->setOpacity(this->_base_alpha);

	}
	//*
	if (this->_text_alpha < this->_MAX_TEXT_ALPHA) {
		//this->_comment_label.Color = new Vector4(1.0f, 1.0f, 1.0f, (float)((float)this->_text_alpha / 100));
		this->_label_obj->setOpacity(this->_text_alpha);
		this->_text_alpha += this->_ADD_TEXT_ALPHA;
	}
	if (this->_text_alpha > this->_MAX_TEXT_ALPHA) {
		this->_text_alpha = this->_MAX_TEXT_ALPHA;
		//this->_comment_label.Color = new Vector4(1.0f, 1.0f, 1.0f, (float)((float)this->_text_alpha / 100));
		this->_label_obj->setOpacity(this->_text_alpha);

	}
	//*/
	// 投稿直後の動作
	if (this->_insert_move_x < 0) {
		this->_insert_move_x = 0;
	}
	else if (this->_insert_move_x > 0) {
		this->_insert_move_x -= this->_BASE_MOVE_SPEED;
	}
}
//-----------------------------------------------------------
// 表示終了時のアニメーション動作
//-----------------------------------------------------------
bool PlayerComment::commentEndAnime() {

	if (this->_base_alpha > 0) {
		//this->_base_sprite.Color = new Vector4(1.0f, 0.7f, 0.8f, (float)((float)this->_base_alpha / 100));
		this->_base_sprite->setOpacity(this->_base_alpha);
		this->_base_alpha -= this->_END_BASE_ALPHA;
	}
	if (this->_base_alpha <= 0) {
		return true;
	}
	
	if (this->_text_alpha > 0) {
		//this->_comment_label.Color = new Vector4(1.0f, 1.0f, 1.0f, (float)((float)this->_text_alpha / 100));
		this->_label_obj->setOpacity(this->_text_alpha);
		this->_text_alpha -= this->_END_TEXT_ALPHA;
	}
	
	if (this->_base_alpha <= 0 && this->_text_alpha <= 0) {
		return true;
	}
	//*/
	return false;
}
int PlayerComment::getCommentLine() {
	return this->_comment_line;
}
int PlayerComment::getCommentLine(std::string s) {
	//
	std::string rep_s = this->stringReplace(s, "\n", "");

	
	auto hoge = rep_s.size();
	auto pito = s.size();
	return s.size() - rep_s.size();
}
bool PlayerComment::getBreakFlag() {
	return this->_break_flag;
}
int PlayerComment::getFontHeight() {
	return this->_font_height;
}

int PlayerComment::oneLineWidth(std::string comment){

	// カンマ区切りで分割して配列に格納する
	//std::unordered_map<int, std::string> stArrayData = comment.Split('\n');
	//std::string delim = "\n";

	// C#版とは違い、1バイト = 1文字扱いのため、多少違うことに注意
	std::list<std::string> stArrayData = this->stringSplit(comment, "\n");

	int text_width = 0;

	// データを確認する
	//for (auto map_obj_line : this->_map_obj_line_list) {
	for(std::string stData : stArrayData) {
		int now_text_width = stData.size();

		if (now_text_width >= text_width) {
			text_width = now_text_width;
		}

	}
	return text_width;
}

std::list<std::string> PlayerComment::stringSplit(std::string str, std::string delim)
{
	std::list<std::string> result;
	int cutAt;
	while ((cutAt = str.find_first_of(delim)) != str.npos)
	{
		if (cutAt > 0)
		{
			result.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length() > 0)
	{
		result.push_back(str);
	}
	return result;
}
std::string PlayerComment::stringReplace(std::string str, std::string from, std::string to) {

	std::string::size_type pos = str.find(from);
	while (pos != std::string::npos){
		str.replace(pos, from.size(), to);
		pos = str.find(from, pos + to.size());
	}

	return str;
}

int PlayerComment::commentObjHeight() {
//	int font_size_comment = comment_data.second->getFontHeight();
//	int comment_line = comment_data.second->getCommentLine();
	int obj_height = this->getFontHeight() * this->getCommentLine() + 5;

	return obj_height;
}