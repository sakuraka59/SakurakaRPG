#ifndef __RENDER_OBJECT__
#define __RENDER_OBJECT__

#include "cocos2d.h"


class RenderObject : public cocos2d::Node {

protected: double _draw_x = 0;
protected: double _draw_y = 0;
protected: double _draw_z = 0; // ƒWƒƒƒ“ƒv‚â•‚—V“™‚É‚æ‚é•â³Œü‚¯

public: double getDrawX();
public: double getDrawY();
public: double getDrawZ();
};

#endif //__RENDER_OBJECT__