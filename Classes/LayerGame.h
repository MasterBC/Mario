#ifndef __LayerGame_H__
#define __LayerGame_H__
#include "Common.h"
#include "ProgressBar.h"
#include "Mario.h"
//ÓÎÏ·Âß¼­
class LayerGame : public CCLayer
{
public:
	static LayerGame* create(int idx);
	bool init(int idx);

	void loadResource();
	void startGame();
	void loadImageCallBack(CCObject* sender);
	void CheckLoadResource(float dt);
	void SetBar(float dt);
	void addCtrl();
	void moveLeft(CCObject* sender);
	void moveRight(CCObject* sender);
	void moveMario(float dt);

	Common::DIRECTION _marioDir;

	ProgressBar* _bar;
	CCTMXTiledMap* _map;
	Mario* _mario;
	int _totalfile;
	int _loadfileCount;
	int _idx;

	CCTexture2D* _textureDirNone;
	CCTexture2D* _textureDirLeft;
	CCTexture2D* _textureDirRight;

	CCSprite* _menuShow;
};
#endif
