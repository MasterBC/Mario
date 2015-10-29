#include "ProgressBar.h"

ProgressBar* ProgressBar::create(const char* bgFile, const char* foreFile)
{
	ProgressBar* pRet = new ProgressBar;
	if (pRet&&pRet->init(bgFile,foreFile))
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}
bool ProgressBar::init(const char* bgFile, const char* foreFile)
{
	CCLayer::init();

	CCSprite* bg = CCSprite::create(bgFile);
	_bg = bg;
	addChild(bg);
	CCSprite* fore = CCSprite::create(foreFile);
	_bar = CCProgressTimer::create(fore);
	_bar->setType(kCCProgressTimerTypeBar);
	_bar->setMidpoint(ccp(0, 0));
	_bar->setBarChangeRate(ccp(1, 0));
	_bar->setPercentage(0);

	addChild(_bar);
	return true;
}
