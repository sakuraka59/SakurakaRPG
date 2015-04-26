#include <unordered_map>       // �n�b�V���e�[�u��

#include "cocos2d.h"
#include "ResourceManage.h"


using namespace cocos2d;



ResourceManage::ResourceManage(){

}
// �摜���\�[�X���擾����

Sprite* ResourceManage::getSprite(std::string file_name)  {
	
	file_name = "icon.png";
	// �f�[�^�����擾�̍ۂ̓L���b�V��������
	if (this->_sprite_cache.find(file_name) == this->_sprite_cache.end()) {
		this->_sprite_cache[file_name] = cocos2d::Sprite::create(file_name);
	}

	return _sprite_cache[file_name];
	
	//return cocos2d::Sprite::create(file_name);
}
//*/