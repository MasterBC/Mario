#include "MenuCtrl.h"

bool MenuCtrl::init()
{
	CCMenu::init();

	scheduleUpdate();
	return true;
}
void MenuCtrl::update(float dt)
{
	if (this->m_pSelectedItem && this->m_eState == kCCMenuStateTrackingTouch)
	{
		m_pSelectedItem->activate();
	}
}
