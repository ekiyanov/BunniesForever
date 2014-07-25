//
//  Explode.cpp
//  NukeGun
//
//  Created by Kiyanov Eugene on 1/26/13.
//
//

#include "Explode.h"
#include "Factory.h"
#include "SimpleAudioEngine.h"

bool Explode::init()
{
    return true;
}

void Explode::setInitialScale(float sc)
{
    _initialScale=sc;
    
    _running=false;
    
    setScale(_initialScale);
}

void Explode::setType(int type)
{
    removeAllChildrenWithCleanup(true);
    if (type==1||type==3)
    {
        Sprite* spr = Sprite::createWithSpriteFrameName("ExploShape.png");
        spr->setColor(CCRANDOM_0_1()<=0.5?Color3B(100, 100, 100):(type==1?Color3B(179, 179, 179):Color3B(255,144,0)));
        addChild(spr);
        setRotation(CCRANDOM_0_1()*360);
        _velocityx=(CCRANDOM_0_1()*50+50)*cosf(getRotation()/180.f*M_PI);
        _velocityy=(CCRANDOM_0_1()*50+50)*sinf(getRotation()/180.f*M_PI);
        _spr=spr;
        
        _updateFunc = schedule_selector(Explode::onUpdate1);
        
    }
    if (type==2)
    {
        Sprite* spr = Sprite::createWithSpriteFrameName("ExploShape1.png");
        spr->setColor(CCRANDOM_0_1()<=0.5?Color3B(100, 100, 100):(type==1?Color3B(179, 179, 179):Color3B(255,144,0)));
        addChild(spr);
        BlendFunc blend;
        blend.src=GL_ONE;
        blend.dst=GL_ONE_MINUS_SRC_COLOR;
        setRotation(CCRANDOM_0_1()*360);
        spr->setBlendFunc(blend);
        spr->setScale(0.5);
        _velocityx=(CCRANDOM_0_1()*50+50)*cosf(getRotation()/180.f*M_PI);
        _velocityy=(CCRANDOM_0_1()*50+50)*sinf(getRotation()/180.f*M_PI);
        _spr=spr;
        spr->setOpacity(255);
        setScale(0);
        
        _updateFunc = schedule_selector(Explode::onUpdate2);
    }
    
    if (_running==false)
    {
        schedule(_updateFunc);
        _running=true;
    }
}

void Explode::onUpdate1(float dt)
{
    float opacity = _spr->getOpacity();
    opacity-=dt*3.5*255;
    _spr->setOpacity(opacity);
    
    if (getScaleX()>0) setScale(getScaleX()-dt*3.5);
    
    if (opacity<=0) onAnimDone();
    
    setPositionX(getPositionX()+dt*_velocityx);
    setPositionY(getPositionY()+dt*_velocityy);
}

void Explode::onUpdate2(float dt)
{
    if (getScaleX()<1)
    {
        setScale(getScaleX()+dt*3);
    }
    
    float opacity = _spr->getOpacity();
    opacity-=dt*3*255;
    if (opacity<=0) opacity=0;
    _spr->setOpacity(opacity);
    
    if (opacity==0) onAnimDone();
    
    setPositionX(getPositionX()+dt*_velocityx);
    setPositionY(getPositionY()+dt*_velocityy);
}

void Explode::onAnimDone()
{
    retain();
    unscheduleAllSelectors();
    _running=false;
    removeFromParentAndCleanup(true);
    autorelease();
}

void Explode::start()
{
    if (_type==2)
    {
        setScale(0);
//        runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.33, 1),\
                                         CCCallFunc::create(this,\
                                                            callfunc_selector(Explode::onAnimDone))));
        _spr->setOpacity(255);
     //   _spr->runAction(CCFadeOut::create(0.33));
    }
    if (_type==1||_type==3)
    {
        _spr->setOpacity(255);
        _spr->runAction(CCFadeOut::create(0.7));
        
        setScale(_initialScale);
    //    runAction(CCSequence::createWithTwoActions(\
                  CCScaleTo::create(0.7/_initialScale, 0),\
                                                   CCCallFunc::create(this,\
                                                                      callfunc_selector(Explode::onAnimDone))));
    }
}

Node* createExplode1(Dictionary* dict)
{
    Explode * expl = new Explode();
    expl->init();
    expl->setType(1);
    expl->autorelease();
    return expl;
}

Node* createExplode2(Dictionary* dict)
{
    Explode * expl = new Explode();
    expl->init();
    expl->setType(2);
    expl->autorelease();
    return expl;
}

Node* createExplode3(Dictionary* dict)
{
    Explode * expl = new Explode();
    expl->init();
    expl->setType(3);
    expl->autorelease();
    return expl;
}

void createExplodeSystem(Node* parent, const Point& position)
{
    Explode * expl;
    
    for (int i=0;i<3;++i)
    {
        
    expl = (Explode*)createExplode1(NULL);
    

    expl->setInitialScale(1);
    expl->start();
    parent->addChild(expl);
    expl->setPosition(position);
    
    expl = (Explode*)createExplode1(NULL);
    expl->setInitialScale(1);
    expl->setRotation(1/M_PI*180);
    expl->start();
    parent->addChild(expl);
    expl->setPosition(position);
    }
    for (int i=0;i<5;++i)
    {
        expl = (Explode*)createExplode3(NULL);
        expl->setInitialScale(0.6);
        expl->setPosition(position);
        expl->start();
        parent->addChild(expl);
    }
    
    for (int i=0;i<5;++i)
    {
        expl = (Explode*)createExplode2(NULL);
        expl->setPosition(position);
        expl->start();
        parent->addChild(expl);
    }
    char explodeName[64];
    sprintf(explodeName, "SmallVehicleExplosion%i.wav",rand()%3+1);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(explodeName);
}

void createLargeExplodeSystem(CCNode* parent, const CCPoint& position)
{
    createExplodeSystem(parent, position);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("LargeVehicleExplosion3.wav");
}

namespace  {
    static const bool registerExplode = Factory::sharedInstance()->registerFabric("Explode1", createExplode1) &&
                                        Factory::sharedInstance()->registerFabric("Explode2", createExplode2) &&
                                        Factory::sharedInstance()->registerFabric("Explode3", createExplode3);
};