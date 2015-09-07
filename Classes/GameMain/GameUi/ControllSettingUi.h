// �V���[�g�J�b�g�ݒ�pUI
#pragma once
#include "cocos2d.h"
#include "../../RenderObject.h"
#include <map>

using namespace std;
using namespace cocos2d;

enum class controllSettingType {
	_no_type = -1,
	skill,
	item,
	_enum_end,
};

enum class buttonSettingType;

class SkillList;
class CharaPlayer;
class ControllSetting;
class SkillBase;
class UseItem;

class ControllSettingUi : public RenderObject {
private: const int _TEXT_LINE_HEIGHT = 30;	// �e�L�X�g����
private: const int _FONT_SIZE = 18;			// �t�H���g�T�C�Y
private: const int _CURSOR_DELAY_TIME = 10;	// �J�[�\���̃f�B���C����
private: const int _BG_WIDTH = 250;			// �w�i�T�C�Y
private: const int _LINE_WIDTH = 5;			// �w�i�̍��E���C����
private: const string _FONT_FILE = "fonts/APJapanesefontT.ttf";		// �g�p�t�H���g�t�@�C���i���񂸕�������

private: const int _ITEM_SET_POSITION = 640 - 55;
private: const int _SKILL_SET_POSITION = 640 + 55;
// CharaPlayer���
private: CharaPlayer* _chara_obj;
private: SkillList* _skill_list;
private: ControllSetting* _controll_setting;
private: map<buttonSettingType, string> _button_set_list;

private: map<buttonSettingType, LabelTTF*> _set_detail_name_list;


// �ݒ肵�悤�Ƃ��Ă���X�L��
private: SkillBase* _skill_obj = nullptr;

// �ݒ肵�悤�Ƃ��Ă���A�C�e��
private: UseItem* _item_obj = nullptr;

// �J�[�\�����쎞�ɂ�����f�B���C���ԃJ�E���g
private: int _cursor_delay = 0;

// �`�悵�Ă��邩�ǂ���
private: bool _draw_flag = false;

// ����ݒ肵�悤�Ƃ��Ă��邩
private: controllSettingType _setting_type = controllSettingType::_no_type;
// �X�L���^�C�v�ꗗ -------------------------------------------------
private: RenderObject* _type_bg_render_obj;		// �w�i�`��
private: RenderObject* _type_label_obj;				// ��ޕ���
private: int _type_num = 0;							// �\�����X�g��
private: int _type_cursor = 0;						// �J�[�\���ʒu
private: unordered_map<int, buttonSettingType> _type_list;	// �J�[�\���ʒu����̎�ރ��X�g


public: ControllSettingUi(CharaPlayer* chara_obj, controllSettingType settint_type);


// �������n ---------------------------------------------------------
// UI�̔w�i���쐬���ĕԂ�
private: RenderObject* getBgRenderObj();

// �ꗗ�̏�����
private: void initTypeLabelList();
// UI����n ---------------------------------------------------------
// UI���J��
public: void openUiToSkill(SkillBase* skill_obj);
public: void openUiToItem(UseItem* item_obj);

private: void oepnUiSetDetailName();
// UI�����
public: void closeUi();

// �X�V���� ---------------------------------------------------------
public: void Update();
// ���̑� -----------------------------------------------------------
public: int getDrawWidth();	// UI�̉����擾

public: bool getDrawFlag();	// �\����Ԃ��ǂ����擾

// ���x���p�I�u�W�F�N�g���쐬���ĕԂ�
private: LabelTTF* getLabelTTF(string set_string_data);

};