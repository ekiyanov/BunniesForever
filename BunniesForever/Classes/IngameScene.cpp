//
//  IngameScene.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "IngameScene.h"
#include "RunRow.h"
#include "MenuGameover.h"
#include "MenuPause.h"
#include "Profile.h"
#include "PlatformParams.h"

static IngameScene* __instance = 0;

Scene* IngameScene::scene()
{
    Scene* sc= Scene::create();
    IngameScene* ingame=new IngameScene();
    ingame->autorelease();
    ingame->init();
    __instance=ingame;
    sc->addChild(ingame);
    return sc;
}



IngameScene* IngameScene::getInstance()
{
    return __instance;
}

float IngameScene::runSpeed()
{
    return -500;
}

void IngameScene::addRow(const Color3B& color)
{
    RunRow* r = new RunRow();
    
    r->init(getNextColor());
    r->autorelease();
    
    float newheight=0;

    
    
    _rows.pushBack(r);
    
    addChild(r);
    
    for (auto it : _rows)
        newheight+=it->getContentSize().height;
    
    float newTopY = getContentSize().height/2+newheight/2;
    
    r->setPosition(Point(getContentSize().width,newTopY-newheight));
    
    for (auto it : _rows)
    {
        newTopY-=it->getContentSize().height;
        it->runAction(MoveTo::create(0.5, Point(0,newTopY)));
        
        it->killAllObjects();
    }
}

bool IngameScene::CanSpawnRows()
{
    if (_rows.size()<4){
        return _score>=(pow(5,_rows.size()));
    }
    
    return false;
}

void IngameScene::draw(Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::drawSolidRect(Point::ZERO, Point(getContentSize().width,
                                                     getContentSize().height),
                                  Color4F::WHITE);
}

void IngameScene::onGameOver(cocos2d::Ref *)
{
    for (auto r : _rows)
    {
        r->setPaused(true);
    }
    
    Profile::getInstance()->setIntForKey(_score,"lastscore");
    Profile::getInstance()->store();
    
    if (_GameoverMenu==0)
    {
        MenuGameover* gomenu=new MenuGameover();
        gomenu->init();
        _GameoverMenu=gomenu;
    }
    
    addChild(_GameoverMenu);
}

void IngameScene::onTapPause(cocos2d::Ref *)
{
    for (auto r : _rows)
    {
        r->setPaused(true);
    }
    
    if (_PauseMenu==0)
    {
        MenuPause* gomenu=new MenuPause();
        gomenu->init();
        _PauseMenu=gomenu;
    }
    
    addChild(_PauseMenu);
}

bool IngameScene::init()
{
    
    Layer::init();

    RunRow* r = new RunRow();
    r->init(Color3B::RED);
    r->autorelease();
    addChild(r);
    r->setPosition(Point(0,getContentSize().height/2-r->getContentSize().height/2));
    
    _rows.pushBack(r);
    
    MenuItemLabel* pausebtn=    MenuItemLabel::create(Sprite::create("PauseBtn.png"),
                          [this](Ref*){
                              onTapPause(0);
                          });
    
    Menu* menu = Menu::create();
    menu->addChild(pausebtn);
    menu->setPosition(Point::ZERO);menu->setAnchorPoint(Point::ZERO);
    pausebtn->setPosition(Point(getContentSize().width-pausebtn->getContentSize().width/2,
                                getContentSize().height-pausebtn->getContentSize().height/2));
    
    Label* score = Label::createWithTTF("0","fonts/victor-pixel.ttf",
                                        PPIntForKey("fontsize")*0.7);
    addChild(score);
    score->setPosition(Point(getContentSize().width/2,
                             getContentSize().height-score->getContentSize().height));
    _scoreLabel=score;
    _scoreLabel->setColor(Color3B(63,63,63));
    _score=0;
    
    addChild(menu);
    
    NotificationCenter::getInstance()->addObserver(this,
                                                   callfuncO_selector(IngameScene::onGameOver), "onGameover",
                                                   0);
    NotificationCenter::getInstance()->addObserver(this,
                                                   callfuncO_selector(IngameScene::onResumeGame), "onResume",
                                                   0);
    NotificationCenter::getInstance()->addObserver(this,
                                                   callfuncO_selector(IngameScene::onRestartGame), "onRestart",
                                                   0);
    
    
    return true;
}

void IngameScene::onRestartGame(Ref*)
{
    for ( auto it : _rows)
        it->removeFromParentAndCleanup(true);
    _rows.clear();
    
    if (_GameoverMenu)
        _GameoverMenu->removeFromParentAndCleanup(true);
    
    _score=0;
    _scoreLabel->setString("0");
    
    addRow(Color3B::RED);
}

void IngameScene::onResumeGame(cocos2d::Ref *)
{
    for (auto it : _rows)
        it->setPaused(false);
    
    if (_PauseMenu)
        _PauseMenu->removeFromParentAndCleanup(true);
}

Color3B IngameScene::getNextColor()
{
    int colors[]=
    {
        244,7,46,
        103,189,69,
        246,182,8,
        198,8,246
    };
    
    int * colors2=&colors[_rows.size()*3];
    
    return Color3B(colors2[0],colors2[1],colors2[2]);
}

void IngameScene::addScore(int score)
{
    _score+=score;
    
    char text[64];sprintf(text, "%i",_score);
    _scoreLabel->setString(text);
}