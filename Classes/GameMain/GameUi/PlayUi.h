#pragma once

#include "UiBase.h"
#include "cocos2d.h"
#include "../chara/CharaBase.h"
#include <unordered_map>

class SeedBase;
class GameCamera;
class CharaPlayer;
class PlayerCommentUI;

class CharaBase;
class MagicBase;
class SkillList;
class MapBase;

class MapObjectList;

class PlayUi : public UiBase
{
private: cocos2d::EventListenerKeyboard* _KEYBORD_EVENT;
public: PlayUi(PlayerCommentUI* comment_ui_obj, cocos2d::EventListenerKeyboard* KEYBORD_EVENT);
public: void Update();

private: cocos2d::Sprite* _test_sprite;

private: GameCamera* _play_camera;
private: CharaPlayer* _player_obj;

private: RenderObject* _order_object_list;
private: std::list<CharaBase*> _chara_list;
private: std::list<MagicBase*> _magic_list;
public: ShadowObjectList* _shadow_list;

public: SkillList* _skill_list;

private: MapBase* _map_obj;
private: std::unordered_map<int, MapObjectList*> _map_obj_line_list;

};