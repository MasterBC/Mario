#ifndef __Mario_H__
#define __Mario_H__
#include "Common.h"
//Mario抽象
class Mario : public CCSprite
{
public:
	CREATE_FUNC(Mario);
	bool init();

	//status
	Common::DIRECTION _dirRun;//LEFT,RIGHT,NONE
	Common::DIRECTION _dirFace;//LEFT,RIGHT,静止的时候脸的朝向
	int _speed;
	int _speedUp;//向上的速度，如果速度不为0，说明mario要继续上升
	int _speedDown;//向下的速度，如果速度不为0，说明mario要继续下降
	int _speedAcc;//加速度
	int _life;
	bool _canFire;
	bool _isBig;

	//跟据上述状态，改变mario当前的表现方式
	void updateStatus();
	//水平运动的操作函数
	void moveLeft(float dt);
	void moveRight(float dt);
	
	void stop();

	//CCAnimation* _walkLeftAnimationSmall;
	//CCAnimation* _walkRightAnimationSmall;
};

#endif