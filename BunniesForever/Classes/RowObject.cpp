//
//  RowObject.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "RowObject.h"
#include "IngameScene.h"
#include "ObjectFactory.h"
#include "SimpleAudioEngine.h"
#include "Character.h"
#include "cocos-ext.h"
#include "PlatformParams.h"


bool RowObject::init()
{
    setContentSize(Size(60,60));
    scheduleUpdate();
    _paused=false;
    return true;
}

void RowObject::update(float dt)
{
    if (_paused)return;
    
    setPositionX(getPositionX()+IngameScene::getInstance()->runSpeed()*dt);
    
    if (getPositionX()+getContentSize().width<0)
    {
        removeFromGame();
    }
}

void RowObject::removeFromGame()
{
    unscheduleUpdate();
    
    removeFromParentAndCleanup(true);
}

void RowObject::draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    return;
    renderer->render();
    DrawPrimitives::setDrawColor4B(100, 100, 100, 255);
    DrawPrimitives::drawRect(Point::ZERO, Point(getContentSize().width,getContentSize().height));
}

void RowObject::setType(int type)
{
    _type=type;
}

int RowObject::type()
{
    return _type;
}

class RowObjectBonus:public RowObject{
public:
    int type(){return 1;}
    bool activated(Character* char1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("coin3.wav");
        
        if (IngameScene::getInstance()!=0)
            IngameScene::getInstance()->addScore(1);
        
        return true;
    }
};

class RowObjectTerminal:public RowObject
{
public:
    int type(){return 1;}
    bool activated(Character* char1)
    {
        
        char1->doDamage(1);
        
        return false;
    }
};

class RowObjectRescueMore:public RowObject
{
    bool _activated;
public:
    bool init()
    {
        RowObject::init();
        _activated=false;
        return true;
    }
    int type(){return 2;}
    bool activated(Character* char1)
    {
        if (_activated==false){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AchievementGet.mp3");
            
            IngameScene::getInstance()->addRow(Color3B::GREEN);
            _activated=true;
        }
        return false;
    }
};

namespace  {
    const static bool terminal = RowObjectFactory::getInstance()->RegisterConstructorForKey("terminal",
                                                                                            [](std::string)->RowObject*
                                                                                            {
                                                                                                RowObject* ro=new RowObjectTerminal();
                                                                                                ro->init();
                                                                                                Sprite* termIcon=Sprite::create("box.png");
                                                                                                ro->addChild(termIcon, 0, 0);
                                                                                                ro->setType(0);
                                                                                                ro->setContentSize(termIcon->getContentSize());
                                                                                                termIcon->setPosition(ro->getContentSize().width/2,
                                                                                                                      ro->getContentSize().height/2);
                                                                                                return ro;
                                                                                            });
    
    const static bool bonus = RowObjectFactory::getInstance()->RegisterConstructorForKey("bonus",
                                                                                            [](std::string)->RowObject*
                                                                                            {
                                                                                                RowObject* ro=new RowObjectBonus();
                                                                                                ro->init();
                                                                                                ro->setType(1);
                                                                                                Sprite* termIcon=Sprite::create("Bonus.png");
                                                                                                ro->addChild(termIcon, 0, 0);
                                                                                                ro->setContentSize(termIcon->getContentSize());
                                                                                                termIcon->setPosition(ro->getContentSize().width/2,
                                                                                                                      ro->getContentSize().height/2);
                                                                                                return ro;
                                                                                            });
    
    const static bool rescue = RowObjectFactory::getInstance()->RegisterConstructorForKey("rescue",
                                                                                         [](std::string)->RowObject*
                                                                                         {
                                                                                             RowObject* ro=new RowObjectRescueMore();
                                                                                             ro->init();
                                                                                             extension::Scale9Sprite* bar = extension::Scale9Sprite::create("sq100.png");
                                                                                             bar->setContentSize(Size(PPIntForKey("rescuebarwidth"),PPIntForKey("rowheight")));
                                                                                             ro->addChild(bar, 0, 0);
                                                                                             
                                                                                             bar->setColor(IngameScene::getInstance()->getNextColor());
                                                                                             bar->setOpacity(100);
                                                                                             
                                                                                             Sprite* bunny = Sprite::createWithSpriteFrameName("hero0_0.png");
                                                                                             ro->addChild(bunny);

                                                                                             
                                                                                             ro->setContentSize(bar->getContentSize());
                                                                                             bar->setPosition(ro->getContentSize().width/2,
                                                                                                                   ro->getContentSize().height/2);
                                                                                             bunny->setPosition(ro->getContentSize().width/2,
                                                                                                                ro->getContentSize().height/2);
                                                                                             bunny->setOpacity(200);
                                                                                             return ro;
                                                                                         });
}