#include <unordered_map>       // ハッシュテーブル

#include "cocos2d.h"
#include "ResourceManage.h"


using namespace cocos2d;
ResourceManage::ResourceManage(){

}
// 画像リソースを取得する

Sprite* ResourceManage::getSprite(std::string file_name)  {
	file_name = "icon.png";
	// データを初取得の際はキャッシュを持つ
	if (_sprite_cache.find(file_name) == _sprite_cache.end()) {
		_sprite_cache[file_name] = cocos2d::Sprite::create(file_name);
	}

	return _sprite_cache[file_name];
}