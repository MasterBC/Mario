#ifndef __Common_H__
#define __Common_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

#define winSize CCDirector::sharedDirector()->getWinSize()

struct Common
{
	enum DIRECTION{ LEFT, RIGHT, UP, DOWN, NONE };
	static CCScene* scene(CCLayer* layer)
	{
		CCScene* scene = CCScene::create();
		scene->addChild(layer);
		//scene->autorelease();
		return scene;
	}
	static void moveNode(CCNode* node, CCPoint pt)
	{
		node->setPosition(node->getPosition() + pt);
	}
	static char* format(int v, const char* prefix = "", const char* suffix = "")
	{
		static char buf[2048];
		sprintf(buf, "%s%d%s", prefix, v, suffix);
		return buf;
	}
	static CCAnimation* createAnimation(const char* filename, int start, int end, int width, float delay)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		CCArray* array = CCArray::create();
		for (int i = start; i <= end; ++i)
		{
			CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(i*width, 0, width, texture->getContentSize().height));
			array->addObject(frame);
		}

		return CCAnimation::createWithSpriteFrames(array, delay);
	}
};

#endif