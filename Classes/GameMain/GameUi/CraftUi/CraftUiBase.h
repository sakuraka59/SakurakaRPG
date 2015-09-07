#pragma once
#include <map>
#include <unordered_map>
#include "cocos2d.h"
#include "../../../RenderObject.h"

class CharaPlayer;
class ItemBase;
class UseItem;

enum class haveItemType;

using namespace cocos2d;
using namespace std;

class CraftUiBase : public RenderObject {
// �\���Ɋւ���ݒ� -------------------------------------------------
protected: const int _TEXT_LINE_HEIGHT = 30;
protected: const int _FONT_SIZE = 18;
protected: const int _CURSOR_DELAY_TIME = 10;
protected: const int _BG_WIDTH = 200;
protected: const int _LINE_WIDTH = 5;
protected: const string _FONT_FILE = "fonts/APJapanesefontT.ttf";		// �g�p�t�H���g�t�@�C���i���񂸕�������
private: const string _NO_SETTING_TEXT = "�Ȃ�";

// �A�C�e���쐬�Ɋւ���ݒ� -----------------------------------------
// �A�C�e���ő�Z�b�g��
protected: const int _ITEM_SET_MAX = 4;
// �g�p�\�A�C�e�����
protected: unordered_map<haveItemType, haveItemType> _use_item_type_list;

private: const int _SET_LABEL_MARGIN = 10;
// CharaPlayer��� --------------------------------------------------
private: CharaPlayer* _player_obj;
//private: ControllSetting* _controll_setting;

// ����A�\���� ---------------------------------------------------
//	0 : �A�C�e����ވꗗ	1 : �A�C�e���ڍ׈ꗗ
private: int _controll_type = 0;

// �J�[�\�����쎞�ɂ�����f�B���C���ԃJ�E���g
private: int _cursor_delay = 0;


// �A�C�e���^�C�v�ꗗ -------------------------------------------------
private: RenderObject* _type_bg_render_obj;		// �w�i�`��
private: RenderObject* _type_label_obj;				// ��ޕ���
private: int _type_num = 0;							// �\�����X�g��
private: int _type_cursor = 0;						// �J�[�\���ʒu
private: unordered_map<int, haveItemType> _type_list;	// �J�[�\���ʒu����̎�ރ��X�g

// �A�C�e���ڍ׈ꗗ -------------------------------------------------
private: RenderObject* _detail_bg_render_obj;							// �w�i�`��
private: unordered_map<haveItemType, RenderObject*> _detail_label_list;	// �X�L���ꗗ�������X�g
private: unordered_map<haveItemType, int> _detail_num_list;				// �\�����X�g��
private: int _detail_cursor = 0;										// �J�[�\���ʒu
private: RenderObject* _detail_label_obj;								// �\������X�L���ꗗ����
private: haveItemType _open_detail_type;									// �J���ĕ\�����Ă���X�L���ꗗ�̃X�L���^�C�v

// �A�C�e���f�ސݒ�ꗗ -------------------------------------------------
private: RenderObject* _stuff_bg_render_obj;				// �w�i�`��
private: RenderObject* _stuff_label_obj;					// ��ޕ���
private: unordered_map<int, LabelTTF*> _stuff_label_list;	// �����͏�����������������̂ŁA�ꗗ�Ŏ����Ă���
private: int _stuff_set_num = 0;							// �\�����X�g��
private: map<int, string> _set_item_stuff_list;			// �쐬���̃A�C�e���ޗ��Z�b�g���X�g
private: map<string, int> _set_item_count;				// ����A�C�e�����������ꂽ��

// �A�C�e���I�u�W�F�N�g���X�g
private: unordered_map<haveItemType, unordered_map<int, ItemBase*>> _detail_list;



public: CraftUiBase(CharaPlayer* chara_obj);

// UI�̔w�i���쐬���ĕԂ�
private: RenderObject* getBgRenderObj();

// �f�ޗpUI�̔w�i���쐬���ĕԂ�
private: RenderObject* getStuffBgRenderObj();
// UI�̕\���n�֐� ---------------------------------------------------
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

// �^�C�v���Ƃ̈ꗗ���x���̏�����
private: bool initDetailLabelList(haveItemType item_type);

// �^�C�v���Ƃ̈ꗗ���x���̏�����(����A�C�e���n�j
private: bool initDetailLabelListToUse(haveItemType item_type);

// �ڍ׈ꗗ�J�����ۂ̏���������
private: void initOpenDetailList(haveItemType item_type);


// �X�V�����n -------------------------------------------------------

// �X�V�������C��
public: void Update();
// ��ވꗗ�X�V����
private: void updateListType();
// �ڍ׈ꗗ�X�V����
private: void updateListDetail();
		 

// �쐬�쐬���� - �A�C�e���I�� --------------------------------------
private: bool setItemMaterial(UseItem* item_obj);

// �Ō�ɃZ�b�g�����A�C�e�����͂���
private: bool unsetItemMaterial();

// �A�C�e���Z�b�g���A�쐬�\���V�s���擾
private: bool checkItemRecipe();
// ���̑� -----------------------------------------------------------
private: string getTypeName(haveItemType item_type);
// ���X�g�̕\������Ԃ�
public: int getDrawWidth();

// ���x���p�I�u�W�F�N�g���쐬���ĕԂ�
private: LabelTTF* getLabelTTF(string set_string_data);


};