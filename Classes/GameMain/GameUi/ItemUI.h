#pragma once
#include "UiBase.h"

class CharaPlayer;
class ObjItemList;

class ItemUi : public UiBase {
private: bool _draw_flag = false;
private: double _draw_alpha = 0;
private: CharaPlayer* _player_obj;

private: ObjItemList* _player_item_list_obj;

public: ItemUi(CharaPlayer* player_obj);

public: void closeItemUi();		// ����
public: void openItemUi();		// ���g�̃A�C�e��UI�̂݊J��
public: void openItemUiToObj();	// �I�u�W�F�N�g����̃A�C�e���擾���Ɏg��




};