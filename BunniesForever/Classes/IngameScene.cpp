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
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "hellocpp/AndroidJNI.h"
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "iOSNative.h"
#endif

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
    return -_runspeed;
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
    
    char keyForReady[64]; sprintf(keyForReady, "readysetfor%zi",_rows.size());
    int val = Profile::getInstance()->intForKey(keyForReady);
    if (val==0)
    {
        Profile::getInstance()->setIntForKey(1, keyForReady);
        Profile::getInstance()->store();
    }
    
    for (auto it : _rows)
    {
        newTopY-=it->getContentSize().height;
        it->runAction(MoveTo::create(0.5, Point(0,newTopY)));
        
        it->killAllObjects();
        
        it->setReadySetGo(val==0||_rows.size()==1);
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
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    runAction(Sequence::create(DelayTime::create(0.8),
                               CallFunc::create([this](){
        
        if (_GameoverMenu==0)
        {
            MenuGameover* gomenu=new MenuGameover();
            gomenu->init();
            _GameoverMenu=gomenu;
        }
        
        addChild(_GameoverMenu);
        
        
        
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
        showAdmobJNI();
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
        showAd();
#endif
        
    }),NULL));
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
    
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    showAdmobJNI();
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    showAd();
#endif
}

bool IngameScene::allSetDone()
{
    for (auto r : _rows)
    {
        if (r->readySetGo()==false) return false;
    }
    
    return true;
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
    
    r->setReadySetGo(true);
    
    Label* II = Label::createWithTTF("II ", "fonts/victor-pixel.ttf",
                                     PPIntForKey("fontsize")*1);
    II->setColor(Color3B(63,63,63));
    MenuItemLabel* pausebtn=    MenuItemLabel::create(II,
                          [this](Ref*){
                              onTapPause(0);
                          });
    
    Menu* menu = Menu::create();
    menu->addChild(pausebtn);
    menu->setPosition(Point::ZERO);menu->setAnchorPoint(Point::ZERO);
    pausebtn->setPosition(Point(getContentSize().width-pausebtn->getContentSize().width/2,
                                getContentSize().height-pausebtn->getContentSize().height/2));
    
    Label* score = Label::createWithTTF("0","fonts/victor-pixel.ttf",
                                        PPIntForKey("fontsize")*1);
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
    
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("ingame2.mp3");
    
    _runspeed = PPIntForKey("runspeed");
    
    return true;
}

void IngameScene::onRestartGame(Ref*)
{
    for ( auto it : _rows)
        it->removeFromParentAndCleanup(true);
    _rows.clear();
    
    if (_GameoverMenu && _GameoverMenu->getParent())
        _GameoverMenu->removeFromParentAndCleanup(true);
    
    if (_PauseMenu && _PauseMenu->getParent())
    _PauseMenu->removeFromParentAndCleanup(true);
    
    _score=0;
    _scoreLabel->setString("0");
    
    addRow(Color3B::RED);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("ingame2.mp3");
    
    
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    hideAdmobJNI();
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    hideAd();
#endif
}

void IngameScene::onResumeGame(cocos2d::Ref *)
{
    for (auto it : _rows)
        it->setPaused(false);
    
    if (_PauseMenu && _PauseMenu->getParent())
        _PauseMenu->removeFromParentAndCleanup(true);
    
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    hideAdmobJNI();
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    hideAd();
#endif
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