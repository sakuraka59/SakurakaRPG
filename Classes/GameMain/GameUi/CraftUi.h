#pragma once
#include "UiBase.h"
#include <unordered_map>

using namespace std;

class CharaPlayer;
class CraftUiBase;

class CraftUi : public UiBase {

private: CharaPlayer* _player_obj;
private: CraftUiBase* _list_ui_obj;

private: bool _draw_flag = false;		// �`�悵�Ă��邩�ǂ���
public: CraftUi();

// ������
public: void Init(CharaPlayer* player_obj);

// �J��
public: void openUi();

// ����
public: void closeUi();

// �X�V����
public: void Update();



};