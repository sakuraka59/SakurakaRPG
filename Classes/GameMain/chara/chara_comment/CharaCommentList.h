#pragma once
#pragma execution_character_set("utf-8")
#include <unordered_map>
#include "charaCommentType.h"
#include "charaSexualType.h"

using namespace std;

class CharaCommentList {

private: static bool _load_flag;
private: static bool _sexual_comment_flag;
private: static unordered_map<charaCommentType, unordered_map<charaSexualType, list<string>>> _comment_list;

private: CharaCommentList();
public: static void loadCommentList();
public: static string getComment(charaCommentType comment_type, charaSexualType chara_type);
};