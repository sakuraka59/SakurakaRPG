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

private: const int _TEXT_LINE_HEIGHT = 30;	// テキスト高さ
private: const int _FONT_SIZE = 18;			// フォントサイズ
private: const int _CURSOR_DELAY_TIME = 10;	// カーソルのディレイ時間
private: const int _BG_WIDTH = 200;			// 背景サイズ
private: const int _LINE_WIDTH = 5;			// 背景の左右ライン幅
private: const string _FONT_FILE = "fonts/APJapanesefontT.ttf";		// 使用フォントファイル（あんず文字等幅


// CharaPlayer情報 --------------------------------------------------
private: CharaPlayer* _chara_obj;
private: SkillList* _skill_list;
//private: ControllSetting* _controll_setting;

private: ControllSettingUi* _controll_setting_ui_obj;

// 操作、表示状況 ---------------------------------------------------
//	0 : アイテム種類一覧	1 : アイテム詳細一覧	2 : ショートカット設定
private: int _controll_type = 0;

// カーソル操作時におけるディレイ時間カウント
private: int _cursor_delay = 0;

// スキルタイプ一覧 -------------------------------------------------
private: RenderObject* _type_bg_render_obj;		// 背景描画
private: RenderObject* _type_label_obj;				// 種類文字
private: int _type_num = 0;							// 表示リスト数
private: int _type_cursor = 0;						// カーソル位置
private: unordered_map<int, skillType> _type_list;	// カーソル位置からの種類リスト


// スキル詳細一覧 -------------------------------------------------
private: RenderObject* _detail_bg_render_obj;							// 背景描画
private: unordered_map<skillType, RenderObject*> _detail_label_list;	// スキル一覧文字リスト
private: unordered_map<skillType, int> _detail_num_list;				// 表示リスト数
private: int _detail_cursor = 0;										// カーソル位置
private: RenderObject* _detail_label_obj;								// 表示するスキル一覧文字
private: skillType _open_detail_type;									// 開いて表示しているスキル一覧のスキルタイプ

// スキルオブジェクト一覧
private: unordered_map<skillType, unordered_map<int, SkillBase*>> _detail_skill_list;

public: SkillListUi(CharaPlayer* chara_obj);

// UIの背景を作成して返す
private: RenderObject* getBgRenderObj();

// UIを開く
public: void openUi();
// UIを閉じる
public: void closeUi();

// 詳細一覧を開く
public: void openDetailList();
// 詳細一覧を閉じる
public: void closeDetailList();
// 初期化処理系 -----------------------------------------------------

// 種類一覧のラベル初期化
private: void initTypeLabelList();

// タイプごとのスキル一覧ラベルの初期化
private: bool initDetailLabelList(skillType skill_type);

// 詳細一覧開いた際の初期化処理
private: void initOpenDetailList(skillType skill_type);
// 更新処理系 -------------------------------------------------------

// 更新処理メイン
public: void Update();
// 種類一覧更新処理
private: void updateListType();
// 詳細一覧更新処理
private: void updateListDetail();

// その他 -----------------------------------------------------------
private: string getTypeName(skillType skill_type);
// リストの表示幅を返す
public: int getDrawWidth();

// ラベル用オブジェクトを作成して返す
private: LabelTTF* SkillListUi::getLabelTTF(string set_string_data);
};