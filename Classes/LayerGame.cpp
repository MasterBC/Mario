#include "LayerGame.h"
#include "MenuCtrl.h"
LayerGame* LayerGame::create(int idx)
{
	LayerGame* pRet = new LayerGame();
	if (pRet && pRet->init(idx))
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
void LayerGame::loadResource()
{
	static const char* picfiles[] = {
		"about_normal.png",
		"about_select.png",
		"AB_normal.png",
		"AB_select.png",
		"allow_walkLeft.png",
		"allow_walkRight.png",
		"arrow.png",
		"arrowActionL.png",
		"arrowActionR.png",
		"arrowBroken.png",
		"arrowBullet.png",
		"arrow_die.png",
		"axe.png",
		"backA.png",
		"backB.png",
		"background.png",
		"backKeyImage.png",
		"backKeyLeft.png",
		"backKeyRight.png",
		"backToMenu.png",
		"battery.png",
		"batteryBoom1.png",
		"batteryBoom2.png",
		"batteryBoom3.png",
		"batteryBullet.png",
		"bg.png",
		"blinkcoin.png",
		"boss.png",
		"bossBullet.png",
		"brokencoin.png",
		"bulletBorder.png",
		"cloud.png",
		"coinani.png",
		"controlUI.png",
		"darkCloud.png",
		"fireActionL.png",
		"fireActionR.png",
		"fireBall.png",
		"fireLeft.png",
		"fireRight.png",
		"fire_die.png",
		"flag.png",
		"flower0.png",
		"flyFishLeft.png",
		"flyFishRight.png",
		"fps_images-hd.png",
		"fps_images-ipadhd.png",
		"fps_images.png",
		"gameover.png",
		"ladder.png",
		"left.png",
		"leftright.png",
		"lighting.png",
		"Mushroom0.png",
		"music_off.png",
		"music_on.png",
		"M_n.png",
		"M_s.png",
		"newgameA.png",
		"newgameB.png",
		"nextlevel_normal.png",
		"nextlevel_select.png",
		"normal_die.png",
		"PassFailure.png",
		"PassSuccess.png",
		"princess.png",
		"quitgame_normal.png",
		"quitgame_select.png",
		"restart_n.png",
		"restart_s.png",
		"resume_n.png",
		"resume_s.png",
		"retry_normal.png",
		"retry_select.png",
		"rewardMushroomSet.png",
		"right.png",
		"select_n.png",
		"select_s.png",
		"Setting_n.png",
		"setting_s.png",
		"Set_Menu.png",
		"Set_Music.png",
		"set_n.png",
		"set_s.png",
		"shanshuodecoin.png",
		"singleblock.png",
		"smallWalkLeft.png",
		"smallWalkRight.png",
		"small_die.png",
		"sound_effect_off.png",
		"sound_effect_on.png",
		"startgame_normal.png",
		"startgame_select.png",
		"superMarioMap.png",
		"switchBg.png",
		"Tools.png",
		"tortoise0.png",
		"walkLeft.png",
		"WalkLeft_fire.png",
		"walkRight.png",
		"WalkRight_fire.png"
	};
	static const char* musicfiles[] = {
		"AddLife.ogg",
		"BossDiaoLuoQiaoXia.ogg",
		"BossDie.ogg",
		"BossHuoQiu.ogg",
		"CaiSiGuaiWu.ogg",
		"DiaoRuXianJingSi.ogg",
		"DingChuMoGuHuoHua.ogg",
		"DingPoZhuan.ogg",
		"DingYingZhuanKuai.ogg",
		"EatCoin.ogg",
		"EatCoin.wma",
		"EatMushroomOrFlower.ogg",
		"GameOver.ogg",
		"HuoQiuDaDaoGuaiWu.ogg",
		"Jump.ogg",
		"OnLand.ogg",
		"OnLand.wma",
		"QiZiLuoXia.ogg",
		"RengHuoQiu.ogg",
		"SuoXiao.ogg",
		"YuDaoGuaiWuSi.ogg"
	};
	_totalfile = sizeof(picfiles) / sizeof(*picfiles);
	int musicfileCount = sizeof(musicfiles) / sizeof(*musicfiles);
	for (int i = 0; i < musicfileCount; ++i)
	{
		SimpleAudioEngine::sharedEngine()->preloadEffect(musicfiles[i]);
	}
	_loadfileCount = 0;
	for (int i = 0; i < _totalfile; ++i)
	{
		//异步加载
		CCTextureCache::sharedTextureCache()->addImageAsync(picfiles[i],this,callfuncO_selector(LayerGame::loadImageCallBack));
	}

	//schedule(schedule_selector(LayerGame::CheckLoadResource));
}
#if 0
void LayerGame::CheckLoadResource(float dt)
{
	if (_loadfileCount == _totalfile)
	{
		_bar->removeFromParent();
		startGame();
		unschedule(schedule_selector(LayerGame::CheckLoadResource));
	}
}
#endif
void LayerGame::startGame()
{
	//加载地图
	_map = CCTMXTiledMap::create(Common::format(_idx + 1, "MarioMap", ".tmx"));
	addChild(_map);
	Common::moveNode(_map, ccp(0, winSize.height - _map->getContentSize().height));

	//增加控制按钮
	addCtrl();

	//移动mario
	schedule(schedule_selector(LayerGame::moveMario));

	//加载地图对象元素
	CCTMXObjectGroup* objGroup = _map->objectGroupNamed("objects");
	CCArray* objs = objGroup->getObjects();
	CCObject* obj;
	CCARRAY_FOREACH(objs, obj)
	{
		CCDictionary* dict = (CCDictionary*)obj;
		const CCString* x = dict->valueForKey("x");
		const CCString* y = dict->valueForKey("y");
		const CCString* type = dict->valueForKey("type");
		if (type->m_sString == "BirthPoint")
		{
			//创建mario
			_mario = Mario::create();
			_mario->setPosition(ccp(x->intValue(), y->intValue() - _map->getTileSize().height));
			_mario->setAnchorPoint(ccp(0, 0));
			_map->addChild(_mario);
		}
	}
}
void LayerGame::moveMario(float dt)
{
	if (_marioDir == Common::LEFT)
	{
		_marioDir = Common::NONE;
		_mario->moveLeft(dt);
	}
	else if (_marioDir == Common::RIGHT)
	{
		_marioDir = Common::NONE;
		_mario->moveRight(dt);
	}
	else
	{
		_menuShow = CCSprite::createWithTexture(_textureDirNone);
		_mario->stop();
	}
}
void LayerGame::loadImageCallBack(CCObject* sender)
{
	_loadfileCount++;
	_bar->setPercentage(_loadfileCount * 100.0f / _totalfile);
	if (_loadfileCount == _totalfile)
	{
		_bar->removeFromParent();
		startGame();
	}
}
void LayerGame::addCtrl()
{
	CCSprite* sprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("controlUI.png"));
	addChild(sprite);
	sprite->setPosition(ccp(0, 0));
	sprite->setAnchorPoint(ccp(0, 0));

	//定制菜单
	MenuCtrl* menu = MenuCtrl::create();
	addChild(menu);

	_textureDirNone = CCTextureCache::sharedTextureCache()->addImage("backKeyImage.png");
	_textureDirLeft = CCTextureCache::sharedTextureCache()->addImage("backKeyLeft.png");
	_textureDirRight = CCTextureCache::sharedTextureCache()->addImage("backKeyRight.png");

	_menuShow = CCSprite::createWithTexture(_textureDirNone);
	addChild(_menuShow);
	CCPoint ptmenuShowPos = ccp(70,50);
	_menuShow->setPosition(ptmenuShowPos);

	CCSprite* left1 = CCSprite::create();
	CCSprite* left2 = CCSprite::create();
	left1->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	left2->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	CCMenuItemSprite* left = CCMenuItemSprite::create(left1, left2, this, menu_selector(LayerGame::moveLeft));
	menu->addChild(left);

	CCSprite* right1 = CCSprite::create();
	CCSprite* right2 = CCSprite::create();
	right1->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	right2->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	CCMenuItemSprite* right = CCMenuItemSprite::create(right1, right2, this, menu_selector(LayerGame::moveRight));
	menu->addChild(right);

	left->setPosition(ccp(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2));
	right->setPosition(ccp(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2));
	Common::moveNode(left, ccp(-_menuShow->getContentSize().width / 4, 0));
	Common::moveNode(right, ccp(_menuShow->getContentSize().width / 4, 0));

	_marioDir = Common::NONE;
}
void LayerGame::moveLeft(CCObject* sender)
{
	//_menuShow->setTexture(this->_textureDirLeft);
	_marioDir = Common::LEFT;
}
void LayerGame::moveRight(CCObject* sender)
{
	//_menuShow->setTexture(this->_textureDirRight);
	_marioDir = Common::RIGHT;
}
bool LayerGame::init(int idx)
{
	CCLayer::init();

	_idx = idx;
	//加载进度条
	_bar = ProgressBar::create("sliderTrack.png", "sliderProgress.png");
	addChild(_bar);
	_bar->setPosition(winSize.width / 2, winSize.height / 2);
	//CCSprite* bg = CCSprite::create("sliderTrack.png");
	//addChild(bg);
	//bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	//CCSprite* sprite = CCSprite::create("sliderProgress.png");
	//CCProgressTimer* bar = CCProgressTimer::create(sprite);
	//_bar = bar;
	//addChild(bar);
	//bar->setType(kCCProgressTimerTypeBar);
	//bar->setMidpoint(ccp(0, 0));
	//bar->setBarChangeRate(ccp(1, 0));
	//bar->setPercentage(0);
	//bar->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	//schedule(schedule_selector(LayerGame::SetBar), .1f);


	loadResource();

	//加载地图
	//_map = CCTMXTiledMap::create(Common::fromat(idx + 1, "MarioMap", ".tmx"));
	//addChild(_map);
	//_map->setPosition(ccp());

	
	return true;
}
void LayerGame::SetBar(float dt)
{
	_bar->setPercentage(_bar->getPercentage() + 1);
	if (_bar->getPercentage() >= 100)
		unschedule(schedule_selector(LayerGame::SetBar));
}