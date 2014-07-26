//
//  MenuGameover.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "MenuGameover.h"
#include "cocos-ext.h"
#include "PlatformParams.h"
#include "Profile.h"

#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "hellocpp/AndroidJNI.h"
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "iOSNative.h"
#endif


using namespace extension;
void MenuGameover::draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::drawSolidRect(Point::ZERO,
                                  Point(getContentSize().width,
                                        getContentSize().height),
                                  Color4F(1,1,1,0.75));
}

void MenuGameover::onEnter()
{
    Layer::onEnter();
    
    significantEvent();
    
    int last=Profile::getInstance()->intForKey("lastscore");
    int top=Profile::getInstance()->intForKey("topscore");
    
    char topScore[64]; sprintf(topScore,  "  TOP: %i", top);
    char lastScore[64];sprintf(lastScore, "SCORE: %i", last);
    
    
    topScoreLbl->setString(topScore);
    lastScoreLbl->setString(lastScore);
    
    _lastScore=last;
    
    if (last>top)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Win.mp3");
        top=last;
        Profile::getInstance()->setIntForKey(top, "topscore");
        Profile::getInstance()->store();
        runAction(
                  Sequence::create(
                                   DelayTime::create(2),
                                   CallFunc::create([this](){
                      topScoreLbl->setScale(0.2);
                      int last=Profile::getInstance()->intForKey("lastscore");
                      char lastScore[64];sprintf(lastScore, "  TOP: %i", last);
                      topScoreLbl->setString(lastScore);
                      topScoreLbl->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.25));
                  }),
                                   NULL)
                  );
    }else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Lose.wav");
    }

    
}

bool MenuGameover::init()
{
    Layer::init();
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    
    Label* score = Label::createWithTTF("", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
    score->setColor(Color3B(63,63,63));
    addChild(score);
    
    topScoreLbl=score;
    
    Label* score2= Label::createWithTTF("", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
    score2->setColor(Color3B(63,63,63));
    addChild(score2);
    
    lastScoreLbl=score2;
    
    
    
    score->setAlignment(TextHAlignment::LEFT);
    score2->setAlignment(TextHAlignment::LEFT);
    
    score->setAnchorPoint(Point(0,0));
    score2->setAnchorPoint(Point(0,0));
    
    score->setPosition(Point(getContentSize().width*0.2,
                             getContentSize().height*0.75));
    score2->setPosition(Point(getContentSize().width*0.2,
                             getContentSize().height*0.75-PPIntForKey("fontsize")*0.8));
    
    
    Label* title= Label::createWithTTF("GAME OVER", "fonts/victor-pixel.ttf",
                                              PPIntForKey("fontsize"));
    title->setColor(Color3B(63,63,63));
    addChild(title);
    title->setPosition(Point(getContentSize().width/2,
                             getContentSize().height*0.9));
    
    Scale9Sprite * btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.35,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithTTF("SHARE", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(11,197,243));
    }
    
    MenuItemLabel* share = MenuItemLabel::create(btnBg,
                                                  [this](Ref*){
//                                                      NotificationCenter::getInstance()->postNotification("onShare");
                                                      
                                                      char textToShare[1024];
                                                      sprintf(textToShare, "I've got %i score with 'Bunnies Forever'. Can yout beat me ? ",_lastScore);
                                                      
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
                                                      shareFBText(textToShare);
#endif
                                                      
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
                                                      shareFBText(textToShare);
#endif
                                                      
                                                      
                                                  });
    
    
    btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.35,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithTTF("RATE", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(11,197,243));
    }
    
    MenuItemLabel* rate = MenuItemLabel::create(btnBg,
                                                 [this](Ref*){
                                                     rateus();
                                                 });
    
    btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*7+10,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithTTF("RESTART", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(233,143,11));
    }

    
    MenuItemLabel* restart = MenuItemLabel::create(btnBg,
                                                   [](Ref*){
                                                       NotificationCenter::getInstance()->postNotification("onRestart");
                                                   });
    
    Menu* menu = Menu::create();
    menu->addChild(share);
    menu->addChild(rate);
    menu->addChild(restart);
    
    Point pt=Point::ZERO;
    
    share->setPosition(pt.x-share->getContentSize().width/2-5,pt.y+5+share->getContentSize().height/2);
    rate->setPosition(pt.x+rate->getContentSize().width/2+5,pt.y+5+rate->getContentSize().height/2);
    restart->setPosition(pt.x,pt.y-5-restart->getContentSize().height/2);
    
//    menu->alignItemsInColumns (2,1, NULL);
//    menu->alignItemsVerticallyWithPadding(getContentSize().height*0.02);
    
    addChild(menu);
    
    return true;
}

