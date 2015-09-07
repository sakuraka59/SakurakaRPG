#pragma once
#include "UiBase.h"
#include <unordered_map>

using namespace std;

class CharaPlayer;
class SkillListUi;

class SkillUi : public UiBase {

private: CharaPlayer* _player_obj;
private: SkillListUi* _skill_list_ui_obj;

private: bool _draw_flag = false;		// �`�悵�Ă��邩�ǂ���
public: SkillUi();

// ������
public: void Init(CharaPlayer* player_obj);

// �J��
public: void openUi();

// ����
public: void closeUi();

// �X�V����
public: void Update();



};