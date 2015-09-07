#pragma once
#include "CharaBase.h"

class PlayerCommentUI;
class CharaCommentList;
class SkillList;
class ControllSettingList;
class ControllSetting;

class CharaPlayer : public CharaBase {


private: bool _control_flag = true;
private: PlayerCommentUI* _comment_ui_obj;

// ボタン設定リスト
private: ControllSettingList* _controll_setting_list;
private: ControllSetting* _controll_setting;

// テスト用
private: int _test_comment_num = 0;
private: int _comment_delay_count = 0;
private: cocos2d::Sprite* _test_sprite;
private: CharaCommentList* _comment_list;

public: CharaPlayer(GameCamera* camera, PlayerCommentUI* comment_ui_obj, std::list<CharaBase*>* all_chara_list, std::list<MagicBase*>* magic_list, ShadowObjectList* shadow_list);

// 調べる系のデータ
protected: double _search_x = 0;		// 調べる座標
protected: double _search_y = 0;		// 調べる座標
protected: bool _search_flag = false;	// 調べるフラグ
// update ---------------------------------------------------
protected: void mainUpdate() override;
public: void updateCamera();
protected: void charaDownMomentDetail() override;
protected: void charaRevival()override;
public: void damageAction() override;
//-------------------------------------------------
// 十字キーによるキャラクター移動
//-------------------------------------------------
private: void moveCharaPlusKey();

// コメント投稿
public: void sendComment(std::string comment) override;
public: void sendDirectComment(std::string comment) override;
public: void sendTypeComment(charaCommentType comment_type, charaSexualType chara_type) override;
public: void sendTypeCommentDirect(charaCommentType comment_type, charaSexualType chara_type) override;
public: void sendSexualComment() override;
protected: void setGroupList() override;

public: void setCharaMapPoint(double point_x, double point_y) override;

//-------------------------------------------------------------------
// 装備変更時の操作設定取得
//-------------------------------------------------------------------
protected: void setControllSetting() override;


// 調べる系の共通動作用
private: void setSearchFlag();
public: bool getSearchFlag();
public: double getSearchX();
public: double getSearchY();

// ----------------------------------------------------------
// ショートカット設定用
public: ControllSetting* getContorllSetting();
//test only -------------------------------------------------
private: void testComment();
private: void testState();
private: void testAction();

};