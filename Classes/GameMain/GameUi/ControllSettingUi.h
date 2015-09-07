// ショートカット設定用UI
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
private: const int _TEXT_LINE_HEIGHT = 30;	// テキスト高さ
private: const int _FONT_SIZE = 18;			// フォントサイズ
private: const int _CURSOR_DELAY_TIME = 10;	// カーソルのディレイ時間
private: const int _BG_WIDTH = 250;			// 背景サイズ
private: const int _LINE_WIDTH = 5;			// 背景の左右ライン幅
private: const string _FONT_FILE = "fonts/APJapanesefontT.ttf";		// 使用フォントファイル（あんず文字等幅

private: const int _ITEM_SET_POSITION = 640 - 55;
private: const int _SKILL_SET_POSITION = 640 + 55;
// CharaPlayer情報
private: CharaPlayer* _chara_obj;
private: SkillList* _skill_list;
private: ControllSetting* _controll_setting;
private: map<buttonSettingType, string> _button_set_list;

private: map<buttonSettingType, LabelTTF*> _set_detail_name_list;


// 設定しようとしているスキル
private: SkillBase* _skill_obj = nullptr;

// 設定しようとしているアイテム
private: UseItem* _item_obj = nullptr;

// カーソル操作時におけるディレイ時間カウント
private: int _cursor_delay = 0;

// 描画しているかどうか
private: bool _draw_flag = false;

// 何を設定しようとしているか
private: controllSettingType _setting_type = controllSettingType::_no_type;
// スキルタイプ一覧 -------------------------------------------------
private: RenderObject* _type_bg_render_obj;		// 背景描画
private: RenderObject* _type_label_obj;				// 種類文字
private: int _type_num = 0;							// 表示リスト数
private: int _type_cursor = 0;						// カーソル位置
private: unordered_map<int, buttonSettingType> _type_list;	// カーソル位置からの種類リスト


public: ControllSettingUi(CharaPlayer* chara_obj, controllSettingType settint_type);


// 初期化系 ---------------------------------------------------------
// UIの背景を作成して返す
private: RenderObject* getBgRenderObj();

// 一覧の初期化
private: void initTypeLabelList();
// UI制御系 ---------------------------------------------------------
// UIを開く
public: void openUiToSkill(SkillBase* skill_obj);
public: void openUiToItem(UseItem* item_obj);

private: void oepnUiSetDetailName();
// UIを閉じる
public: void closeUi();

// 更新処理 ---------------------------------------------------------
public: void Update();
// その他 -----------------------------------------------------------
public: int getDrawWidth();	// UIの横幅取得

public: bool getDrawFlag();	// 表示状態かどうか取得

// ラベル用オブジェクトを作成して返す
private: LabelTTF* getLabelTTF(string set_string_data);

};