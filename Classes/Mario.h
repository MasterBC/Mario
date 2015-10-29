#ifndef __Mario_H__
#define __Mario_H__
#include "Common.h"
//Mario����
class Mario : public CCSprite
{
public:
	CREATE_FUNC(Mario);
	bool init();

	//status
	Common::DIRECTION _dirRun;//LEFT,RIGHT,NONE
	Common::DIRECTION _dirFace;//LEFT,RIGHT,��ֹ��ʱ�����ĳ���
	int _speed;
	int _speedUp;//���ϵ��ٶȣ�����ٶȲ�Ϊ0��˵��marioҪ��������
	int _speedDown;//���µ��ٶȣ�����ٶȲ�Ϊ0��˵��marioҪ�����½�
	int _speedAcc;//���ٶ�
	int _life;
	bool _canFire;
	bool _isBig;

	//��������״̬���ı�mario��ǰ�ı��ַ�ʽ
	void updateStatus();
	//ˮƽ�˶��Ĳ�������
	void moveLeft(float dt);
	void moveRight(float dt);
	
	void stop();

	//CCAnimation* _walkLeftAnimationSmall;
	//CCAnimation* _walkRightAnimationSmall;
};

#endif