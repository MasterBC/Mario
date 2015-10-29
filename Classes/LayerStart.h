#ifndef __LayerStart_H__
#define __LayerStart_H__
#include "Common.h"
//第一个场景界面
class LayerStart : public CCLayer
{
public:
	CREATE_FUNC(LayerStart);
	bool init();

	void Start(CCObject* sender);
	void Setup(CCObject* sender);
	void Quit(CCObject* sender);
	void About(CCObject* sender);
};
#endif
