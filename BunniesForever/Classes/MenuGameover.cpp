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

using namespace extension;
void MenuGameover::draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::drawSolidRect(Point::ZERO,
                                  Point(getContentSize().width,
                                        getContentSize().height),
                                  Color4F(1,1,1,0.75));
}

bool MenuGameover::init()
{
    Layer::init();
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    
    char topScore[64]; sprintf(topScore,  "  TOP: %i", Profile::getInstance()->intForKey("topscore"));
    char lastScore[64];sprintf(lastScore, "SCORE: %i", Profile::getInstance()->intForKey("lastscore"));
    
    int last=Profile::getInstance()->intForKey("lastscore");
    int top=Profile::getInstance()->intForKey("topscore");
    


    Label* score = Label::createWithTTF("", "victor-pixel.ttf", PPIntForKey("fontsize"));
    score->setString(topScore);
    addChild(score);
    
    Label* score2= Label::createWithTTF("", "victor-pixel.ttf", PPIntForKey("fontsize"));
    score2->setString(lastScore);
    addChild(score2);
    
    
    if (last>top)
    {
        top=last;
        Profile::getInstance()->setIntForKey(top, "topscore");
        Profile::getInstance()->store();
        runAction(
                  Sequence::create(
                                   DelayTime::create(1),
                                   CallFunc::create([this,score](){
                      score->setScale(0.2);
                      int last=Profile::getInstance()->intForKey("lastscore");
                      char lastScore[64];sprintf(lastScore, "SCORE: %i", last);
                      score->setString(lastScore);
                      score->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.25));
                  }),
                                   NULL)
                  );
    }
    
    score->setAlignment(TextHAlignment::LEFT);
    score2->setAlignment(TextHAlignment::LEFT);
    
    score->setAnchorPoint(Point(0,0));
    score2->setAnchorPoint(Point(0,0));
    
    score->setPosition(Point(getContentSize().width*0.4,
                             getContentSize().height*0.7));
    score2->setPosition(Point(getContentSize().width/2,
                             getContentSize().height*0.7-score2->getContentSize().height));
    
    
    Label* title= Label::createWithTTF("GAME OVER", "victor-pixel.ttf",
                                              PPIntForKey("fontsize"));
    addChild(title);
    title->setPosition(Point(getContentSize().width/2,
                             getContentSize().height*0.8));
    
    Scale9Sprite * btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithTTF("SHARE", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(11,197,243));
    }
    
    MenuItemLabel* share = MenuItemLabel::create(btnBg,
                                                  [](Ref*){
                                                      NotificationCenter::getInstance()->postNotification("onShare");
                                                  });
    
    btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
    
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
    menu->addChild(restart);
    
    menu->alignItemsVerticallyWithPadding(getContentSize().height*0.02);
    
    addChild(menu);
    
    return true;
}

