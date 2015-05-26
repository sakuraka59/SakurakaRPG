#pragma once
#include "../../RenderObject.h"

class PlayerComment : public RenderObject{

private: int _BASE_POSITION_X = 0;
private: int _BASE_POSITION_Y = 0;

private: int _BASE_WIDTH_MARGIN = 0;
private: int _BASE_MOVE_SPEED = 10;	// �����A�j���[�V�����ł̉E���獶�֌����A�j���[�V�������x
private: int _FONT_SIZE = 14;
private: int _font_height = 0;
private: int _insert_move_x = 0;
private: int _correct_x = 0;

private: int _set_view_count = 0;
private: int _comment_line = 0;

private: bool _break_flag = false;

private: cocos2d::Sprite* _base_sprite;
private: cocos2d::LabelTTF* _label_obj;

// �R�����g�w�i�v�f�̓����x�A�j���[�V�����ݒ�
private: float _base_alpha = 0;
private: int _MAX_BASE_ALPHA = 255/2;
private: float _ADD_BASE_ALPHA = 6.0f;
private: float _END_BASE_ALPHA = 1.5f;

// �R�����g�e�L�X�g�v�f�̓����x�A�j���[�V�����ݒ�
private: float _text_alpha = 0;
private: int _MAX_TEXT_ALPHA = 255;
private: float _ADD_TEXT_ALPHA = 6.0f * 2;
private: float _END_TEXT_ALPHA = 1.5f;

private: int _COMMENT_VIEW_FRAME = 60 * 2;


public: PlayerComment(std::string comment);
public: void Update(int now_comment_correct_y);
private: void commentStartAnime();
private: bool commentEndAnime();
public: int getCommentLine();
public: bool getBreakFlag();
public: int getFontHeight();
public: int getCommentLine(std::string s);
public: int oneLineWidth(std::string comment);

private: std::list<std::string> stringSplit(std::string str, std::string delim);
private: std::string PlayerComment::stringReplace(std::string str, std::string from, std::string to);

public: int commentObjHeight();
};