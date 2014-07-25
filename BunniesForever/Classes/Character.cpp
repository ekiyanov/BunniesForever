//
//  Character.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "Character.h"
#include "RowObject.h"

static const int kGravity=30;
static const int kMass=90;
static const int kJumpImpulse=800;
static const int kLegFingerLength=2;

bool Character::initWithColor(const Color3B& color)
{
    Animation* animRun = AnimationCache::getInstance()->getAnimation("anim_run");
    if (animRun==0){
        Vector<SpriteFrame*> frames1;
        for (int i=0;i<4;i++)
        {
            char framename[64];sprintf(framename, "hero0_%i.png",i);
            SpriteFrame*fr=SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
            frames1.pushBack(fr);
        }
        animRun = Animation::createWithSpriteFrames(frames1);
        animRun->setDelayPerUnit(0.2);
        
        AnimationCache::getInstance()->addAnimation(animRun, "anim_run");
    }
    
    Animation * animjump = AnimationCache::getInstance()->getAnimation("anim_jump");
    if (animjump==0){
        Vector<SpriteFrame*> frames1;
        for (int i=0;i<4;i++)
        {
            char framename[64];sprintf(framename, "hero0_%i.png",i);
            SpriteFrame*fr=SpriteFrameCache::getInstance()->getSpriteFrameByName(framename);
            frames1.pushBack(fr);
        }
        animjump = Animation::createWithSpriteFrames(frames1);
        animjump->setDelayPerUnit(0.2);
        
        AnimationCache::getInstance()->addAnimation(animjump, "anim_jump");
    }

    Sprite* char1=Sprite::createWithSpriteFrame(animRun->getFrames().front()->getSpriteFrame());
    addChild(char1);
    
    char1->runAction(RepeatForever::create(Animate::create(animRun)));
    Sprite* jump=Sprite::createWithSpriteFrame(animjump->getFrames().front()->getSpriteFrame());
    addChild(jump);
    
    
    _blinkAction=0;
    
    setContentSize(char1->getContentSize());
    
    char1->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    jump->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    
    char1->setColor(color);
    
    setCascadeOpacityEnabled(true);

    scheduleUpdate();
    
    vSpeed=0;
    
    
    _jumpSprite=jump;
    _jumpAnim=animjump;
    
    return true;
}

Character* Character::CharacterWithColor(const Color3B& color){
    Character* char1=new Character();
    char1->initWithColor(color);
    char1->autorelease();
    return char1;
}

void Character::update(float dt)
{
    vSpeed-=kGravity*kMass*dt;
    setPositionY(getPositionY()+vSpeed*dt);
    if (getPositionY()<0)
    {
        setPositionY(0);
        vSpeed=0;
    }
}

void Character::Jump()
{
    if (getPositionY()<kLegFingerLength)
    {
        vSpeed=kJumpImpulse;
        _jumpSprite->runAction(Sequence::create(
                                                Animate::create(_jumpAnim),
                                                CallFunc::create([this](){
        
            _jumpSprite->setSpriteFrame(_jumpAnim->getFrames().front()->getSpriteFrame());
        })
                                                , NULL));
    }
}

bool Character::onCollideWithObject(RowObject* rowObject)
{
    return     rowObject->activated(this);
}

void Character::doDamage(int damage)
{
    if (damage>0)
    {
        NotificationCenter::getInstance()->postNotification("onGameover");
        return;
        if (_blinkAction)
            stopAction(_blinkAction);
        
        _blinkAction=Sequence::create(
                                      Blink::create(3, 9),
                                      FadeIn::create(0.1),
                                      NULL);
        runAction(_blinkAction);
    }
}