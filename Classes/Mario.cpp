#include "Mario.h"


bool Mario::init()
{
	//设置脸朝右的帧
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("smallWalkRight.png");
	CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, texture->getContentSize().width / 11, texture->getContentSize().height));
	CCSprite::initWithSpriteFrame(frame);
	//设置mario的ZOrder
	setZOrder(100);

	//属性的初始化
	_speed = 100;
	_dirRun = Common::NONE;
	_dirFace = Common::RIGHT;
	_life = 3;
	_speedUp = 0;
	_speedDown = 0;
	_speedAcc = 10;
	_isBig = false;
	_canFire = false;

	//mario用到的动画
	//创建向左走的动画
	CCAnimationCache::sharedAnimationCache()->addAnimation(Common::createAnimation("smallWalkLeft.png", 0, 9, 14, 0.05f), "SmallWalkLeft");
	//创建向右走的动画
	CCAnimationCache::sharedAnimationCache()->addAnimation(Common::createAnimation("smallWalkRight.png", 0, 9, 14, 0.05f), "SmallWalkRight");
	return true;
}

void Mario::moveLeft(float dt)
{
	if (_dirRun != Common::LEFT)
	{
		_dirRun = Common::LEFT;
		_dirFace = Common::LEFT;
		updateStatus();
	}
	Common::moveNode(this, ccp(-dt*_speed, 0));
	
}
void Mario::moveRight(float dt)
{
	if (_dirRun != Common::RIGHT)
	{
		_dirRun = Common::RIGHT;
		_dirFace = Common::RIGHT;
		updateStatus();
	}
	Common::moveNode(this, ccp(dt*_speed, 0));

	//卷动地图
	CCNode* map = getParent();
	CCPoint ptWorld = map->convertToWorldSpace(this->getPosition());
	if (ptWorld.x > winSize.width / 2)
	{
		Common::moveNode(map, ccp(-dt*_speed, 0));
	}
}
void Mario::updateStatus()
{
	stopAllActions();
	if (_dirRun == Common::LEFT)
	{
		runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("SmallWalkLeft"))));
	}
	else if (_dirRun == Common::RIGHT)
	{
		runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("SmallWalkRight"))));
	}
	else//静止
	{
		if (_dirFace==Common::LEFT)
		{
			this->setDisplayFrameWithAnimationName("SmallWalkLeft", 0);
		}
		else
		{
			this->setDisplayFrameWithAnimationName("SmallWalkRight", 0);
		}
	}
}
void Mario::stop()
{
	if (_dirRun != Common::NONE)
	{
		_dirRun = Common::NONE;
		updateStatus();
	}
}