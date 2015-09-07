#pragma once

#include "cocos2d.h"
#include "../../../RenderObject.h"

using namespace std;
using namespace cocos2d;

class SkillList;
class CharaPlayer;
class ControllSetting;

class SkillBase;
class ControllSettingUi;

enum class skillType;

class SkillListUi : public RenderObject {

private: const int _TEXT_LINE_HEIGHT = 30;	// �e�L�X�g����
private: const int _FONT_SIZE = 18;			// �t�H���g�T�C�Y
private: const int _CURSOR_DELAY_TIME = 10;	// �J�[�\���̃f�B���C����
private: const int _BG_WIDTH = 200;			// �w�i�T�C�Y
private: const int _LINE_WIDTH = 5;			// �w�i�̍��E���C����
private: const string _FONT_FILE = "fonts/APJapanesefontT.ttf";		// �g�p�t�H���g�t�@�C���i���񂸕�������


// CharaPlayer��� --------------------------------------------------
private: CharaPlayer* _chara_obj;
private: SkillList* _skill_list;
//private: ControllSetting* _controll_setting;

private: ControllSettingUi* _controll_setting_ui_obj;

// ����A�\���� ---------------------------------------------------
//	0 : �A�C�e����ވꗗ	1 : �A�C�e���ڍ׈ꗗ	2 : �V���[�g�J�b�g�ݒ�
private: int _controll_type = 0;

// �J�[�\�����쎞�ɂ�����f�B���C���ԃJ�E���g
private: int _cursor_delay = 0;

// �X�L���^�C�v�ꗗ -------------------------------------------------
private: RenderObject* _type_bg_render_obj;		// �w�i�`��
private: RenderObject* _type_label_obj;				// ��ޕ���
private: int _type_num = 0;							// �\�����X�g��
private: int _type_cursor = 0;						// �J�[�\���ʒu
private: unordered_map<int, skillType> _type_list;	// �J�[�\���ʒu����̎�ރ��X�g


// �X�L���ڍ׈ꗗ -------------------------------------------------
private: RenderObject* _detail_bg_render_obj;							// �w�i�`��
private: unordered_map<skillType, RenderObject*> _detail_label_list;	// �X�L���ꗗ�������X�g
private: unordered_map<skillType, int> _detail_num_list;				// �\�����X�g��
private: int _detail_cursor = 0;										// �J�[�\���ʒu
private: RenderObject* _detail_label_obj;								// �\������X�L���ꗗ����
private: skillType _open_detail_type;									// �J���ĕ\�����Ă���X�L���ꗗ�̃X�L���^�C�v

// �X�L���I�u�W�F�N�g�ꗗ
private: unordered_map<skillType, unordered_map<int, SkillBase*>> _detail_skill_list;

public: SkillListUi(CharaPlayer* chara_obj);

// UI�̔w�i���쐬���ĕԂ�
private: RenderObject* getBgRenderObj();

// UI���J��
public: void openUi();
// UI�����
public: void closeUi();

// �ڍ׈ꗗ���J��
public: void openDetailList();
// �ڍ׈ꗗ�����
public: void closeDetailList();
// �����������n -----------------------------------------------------

// ��ވꗗ�̃��x��������
private: void initTypeLabelList();

// �^�C�v���Ƃ̃X�L���ꗗ���x���̏�����
private: bool initDetailLabelList(skillType skill_type);

// �ڍ׈ꗗ�J�����ۂ̏���������
private: void initOpenDetailList(skillType skill_type);
// �X�V�����n -------------------------------------------------------

// �X�V�������C��
public: void Update();
// ��ވꗗ�X�V����
private: void updateListType();
// �ڍ׈ꗗ�X�V����
private: void updateListDetail();

// ���̑� -----------------------------------------------------------
private: string getTypeName(skillType skill_type);
// ���X�g�̕\������Ԃ�
public: int getDrawWidth();

// ���x���p�I�u�W�F�N�g���쐬���ĕԂ�
private: LabelTTF* SkillListUi::getLabelTTF(string set_string_data);
};