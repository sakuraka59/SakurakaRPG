#include "CharaCommentList.h"
#include "../../../Random.h"

bool CharaCommentList::_load_flag = false;
bool CharaCommentList::_sexual_comment_flag = false;
unordered_map<charaCommentType, unordered_map<charaSexualType, list<string>>> CharaCommentList::_comment_list;
void CharaCommentList::loadCommentList() {
	if (CharaCommentList::_load_flag == true) {
		return;
	}

	// デフォルトコメント
//	CharaCommentList::_comment_list[charaCommentType::_no_type][charaSexualType::_no_type].push_back("にゅーん");
//	CharaCommentList::_comment_list[charaCommentType::_no_type][charaSexualType::_no_type].push_back("ふぅ…");

	CharaCommentList::_comment_list[charaCommentType::_no_type][charaSexualType::_no_type].push_back("コメントテスト１");
	CharaCommentList::_comment_list[charaCommentType::_no_type][charaSexualType::_no_type].push_back("こめんとてすと２");


	CharaCommentList::_comment_list[charaCommentType::chara_attack][charaSexualType::_no_type].push_back("はっ！");
	CharaCommentList::_comment_list[charaCommentType::chara_attack][charaSexualType::_no_type].push_back("っ！");


	CharaCommentList::_comment_list[charaCommentType::search_box][charaSexualType::_no_type].push_back("何かあるかな…？");
//	CharaCommentList::_comment_list[charaCommentType::search_box][charaSexualType::_no_type].push_back("うーん…？");


	CharaCommentList::_load_flag = true;
}
string CharaCommentList::getComment(charaCommentType comment_type, charaSexualType chara_type) {
	Random* rand_obj = new Random();
	int rand_comment_index = 0;

	list<string> comment_list = CharaCommentList::_comment_list[charaCommentType::_no_type][charaSexualType::_no_type];

	int num = CharaCommentList::_comment_list[comment_type][chara_type].size();
	if (num > 0) {
		comment_list = CharaCommentList::_comment_list[comment_type][chara_type];
	} else if (CharaCommentList::_comment_list[comment_type][charaSexualType::_no_type].size() > 0) {
		comment_list = CharaCommentList::_comment_list[comment_type][charaSexualType::_no_type];

	} else if (CharaCommentList::_comment_list[charaCommentType::_no_type][chara_type].size() > 0) {
		comment_list = CharaCommentList::_comment_list[charaCommentType::_no_type][chara_type];
	} else if (CharaCommentList::_comment_list[charaCommentType::_no_type][charaSexualType::_no_type].size() > 0) {
		comment_list = CharaCommentList::_comment_list[charaCommentType::_no_type][charaSexualType::_no_type];
	}
	//			int a = comment_list.Count - 1;
	rand_comment_index = rand_obj->getRandNum(comment_list.size() -1);

	auto list_itr = comment_list.begin();
	for (int i = 0; i < rand_comment_index; i++) {
		list_itr++;
	}

	return *list_itr;

}