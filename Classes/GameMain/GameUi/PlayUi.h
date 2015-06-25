#pragma once

#include "UiBase.h"
#include "cocos2d.h"
#include "../chara/CharaBase.h"
#include <unordered_map>

using namespace std;

class SeedBase;
class GameCamera;
class CharaPlayer;
class PlayerCommentUI;

class CharaNpc;
class CharaBase;
class MagicBase;
class SkillList;
class MapBase;

class MapObjectList;
class MapGroundObjectList;

class ItemUi;

class PlayUi : public UiBase
{
//private: cocos2d::EventListenerKeyboard* _KEYBORD_EVENT;

private: cocos2d::Sprite* _test_sprite;

private: GameCamera* _play_camera;
private: CharaPlayer* _player_obj;

private: RenderObject* _order_object_list;
private: list<CharaNpc*> _npc_list;
private: list<CharaBase*> _chara_list;
private: list<MagicBase*> _magic_list;
public: ShadowObjectList* _shadow_list;

public: SkillList* _skill_list;

private: MapBase* _map_obj;
private: std::unordered_map<int, MapObjectList*> _map_obj_line_list;
private: MapGroundObjectList* _mg_object_list_obj;

private: ItemUi* _item_ui_obj;

public: PlayUi(PlayerCommentUI* comment_ui_obj);
public: void Update();
private: void checkHitMapObject(CharaBase* chara_obj);
private: void checkHitMapGroundObject(CharaBase* chara_obj);
private: void checkHitMagic(MagicBase* magic_obj, std::list<MagicBase*>* delete_magic_list);
private: bool checkHeightHit(MagicBase* magic_obj, CharaBase* check_chara_obj);

public: CharaPlayer* getCharaPlayerObj();
private: void playerSearchAction();

public: void setItemUiObj(ItemUi* item_ui_obj);

// マップ移動処理を行う
public: void setMapMove();
};