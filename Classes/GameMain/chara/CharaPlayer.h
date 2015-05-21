#pragma once
#include "CharaBase.h"

class PlayerCommentUI;
class CharaCommentList;
class SkillList;

class CharaPlayer : public CharaBase {


private: bool _control_flag = true;
private: PlayerCommentUI* _comment_ui_obj;

// �e�X�g�p
private: int _test_comment_num = 0;
private: int _comment_delay_count = 0;
private: cocos2d::Sprite* _test_sprite;
private: CharaCommentList* _comment_list;

public: CharaPlayer(GameCamera* camera, PlayerCommentUI* comment_ui_obj, std::list<CharaBase*> all_chara_list, std::list<MagicBase*> magic_list, ShadowObjectList* shadow_list);

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
public: void sendDirectComment(std::string comment);
public: void sendTypeComment(charaCommentType comment_type, charaSexualType chara_type) override;
public: void sendTypeCommentDirect(charaCommentType comment_type, charaSexualType chara_type) override;
public: void sendSexualComment() override;
protected: void setGroupList() override;

public: void setCharaMapPoint(double point_x, double point_y) override;


//test only -------------------------------------------------
private: void testComment();
private: void testState();
private: void testAction();
};