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
    Sprite* char1=Sprite::create("Char1.png");
    
    addChild(char1);
    
    _blinkAction=0;
    
    setContentSize(char1->getContentSize());
    
    char1->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    
    char1->setColor(color);
    
    setCascadeOpacityEnabled(true);

    scheduleUpdate();
    
    vSpeed=0;
    
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
        vSpeed=kJumpImpulse;
}

bool Character::onCollideWithObject(RowObject* rowObject)
{
    return     rowObject->activated(this);
    

}

void Character::doDamage(int damage)
{
    if (damage>0)
    {
        if (_blinkAction)
            stopAction(_blinkAction);
        _blinkAction=Sequence::create(
                                      Blink::create(3, 9),
                                      FadeIn::create(0.1),
                                      NULL);
        runAction(_blinkAction);
    }
}