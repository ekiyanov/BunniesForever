//
//  Character.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "Character.h"
#include "RowObject.h"
#include "SimpleAudioEngine.h"
#include "PlatformParams.h"

static int kGravity=30;
static int kMass=90;
static int kJumpImpulse=800;
static int kLegFingerLength=2;

bool Character::initWithColor(const Color3B& color)
{
    kGravity=PPIntForKey("gravity");
    kMass=PPIntForKey("mass");
    kJumpImpulse=PPIntForKey("jumpimpulse");
    kLegFingerLength=PPIntForKey("legfingerlength");
    
    int charheight=PPIntForKey("characterheight");
    
    Animation* animRun = AnimationCache::getInstance()->getAnimation("anim_run");
    if (animRun==0){
        Vector<SpriteFrame*> frames1;
        for (int i=0;i<4;i++)
        {
            char framename[64];sprintf(framename, "hero%i_0.png",i);
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
        frames1.clear();
        for (int i=0;i<4;i++)
        {
            char framename[64];sprintf(framename, "hero%i_1.png",i);
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
    
    char1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    jump->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    
    char1->setColor(color);
    
    setCascadeOpacityEnabled(true);

    scheduleUpdate();
    
    vSpeed=0;
    
    
    _jumpSprite=jump;
    _jumpAnim=animjump;
    
    float scale=charheight/getContentSize().height;
    setScale(scale);
    
    return true;
}

Character* Character::CharacterWithColor(const Color3B& color){
    Character* char1=new Character();
    char1->initWithColor(color);
    char1->autorelease();
    return char1;
}
void Character::draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    return;
    renderer->render();
    DrawPrimitives::setDrawColor4B(100, 100, 100, 255);
    DrawPrimitives::drawRect(Point::ZERO, Point(getContentSize().width,getContentSize().height));
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
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Click2.mp3");
    
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