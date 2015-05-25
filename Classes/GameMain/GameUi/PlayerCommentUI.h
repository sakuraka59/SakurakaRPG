#pragma once
#include "UiBase.h"
#include <unordered_map>


class PlayerComment;

class PlayerCommentUI : public UiBase {

private: std::unordered_map<int, PlayerComment*> _comment_list;
private: int _comment_count = 0;
private: int _COMMENT_MAX = 5;

private: cocos2d::TTFConfig _comment_font;
private: int _FONT_SIZE = 14;

public: PlayerCommentUI();
public: void Update();
public: void setComment(std::string comment, int line);
};