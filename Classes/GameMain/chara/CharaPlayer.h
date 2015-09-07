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

// �{�^���ݒ胊�X�g
private: ControllSettingList* _controll_setting_list;
private: ControllSetting* _controll_setting;

// �e�X�g�p
private: int _test_comment_num = 0;
private: int _comment_delay_count = 0;
private: cocos2d::Sprite* _test_sprite;
private: CharaCommentList* _comment_list;

public: CharaPlayer(GameCamera* camera, PlayerCommentUI* comment_ui_obj, std::list<CharaBase*>* all_chara_list, std::list<MagicBase*>* magic_list, ShadowObjectList* shadow_list);

// ���ׂ�n�̃f�[�^
protected: double _search_x = 0;		// ���ׂ���W
protected: double _search_y = 0;		// ���ׂ���W
protected: bool _search_flag = false;	// ���ׂ�t���O
// update ---------------------------------------------------
protected: void mainUpdate() override;
public: void updateCamera();
protected: void charaDownMomentDetail() override;
protected: void charaRevival()override;
public: void damageAction() override;
//-------------------------------------------------
// �\���L�[�ɂ��L�����N�^�[�ړ�
//-------------------------------------------------
private: void moveCharaPlusKey();

// �R�����g���e
public: void sendComment(std::string comment) override;
public: void sendDirectComment(std::string comment) override;
public: void sendTypeComment(charaCommentType comment_type, charaSexualType chara_type) override;
public: void sendTypeCommentDirect(charaCommentType comment_type, charaSexualType chara_type) override;
public: void sendSexualComment() override;
protected: void setGroupList() override;

public: void setCharaMapPoint(double point_x, double point_y) override;

//-------------------------------------------------------------------
// �����ύX���̑���ݒ�擾
//-------------------------------------------------------------------
protected: void setControllSetting() override;


// ���ׂ�n�̋��ʓ���p
private: void setSearchFlag();
public: bool getSearchFlag();
public: double getSearchX();
public: double getSearchY();

// ----------------------------------------------------------
// �V���[�g�J�b�g�ݒ�p
public: ControllSetting* getContorllSetting();
//test only -------------------------------------------------
private: void testComment();
private: void testState();
private: void testAction();

};