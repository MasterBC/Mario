#ifndef __ProgressBar_H__
#define __ProgressBar_H__
#include "Common.h"
class ProgressBar : public CCLayer
{
public:
	static ProgressBar* create(const char* bgFile, const char* foreFile);
	bool init(const char* bgFile, const char* foreFile);

	void setPercentage(float per)
	{ 
		_bar->setPercentage(per); 
	}
	float getPercentage()
	{
		return _bar->getPercentage();
	}
	void setPosition(float x, float y)
	{
		_bar->setPosition(ccp(x, y));
		_bg->setPosition(ccp(x, y));
	}
private:
	CCProgressTimer* _bar;
	CCSprite* _bg;
};
#endif
