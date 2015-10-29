#ifndef __MenuCtrl_H__
#define __MenuCtrl_H__
#include "Common.h"
class MenuCtrl : public CCMenu
{
public:
	CREATE_FUNC(MenuCtrl);
	bool init();
	void update(float dt);
};
#endif
