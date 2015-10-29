#ifndef __LayerMenu_H__
#define __LayerMenu_H__
#include "Common.h"
//ักนุ
class LayerMenu : public CCLayer
{
public:
	CREATE_FUNC(LayerMenu);
	bool init();
	void Back(CCObject* sender);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	bool isClick(CCTouch *pTouch);

	CCScrollView* _view;
};
#endif
