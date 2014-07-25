//
//  Character.h
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#ifndef __BunniesForever__Character__
#define __BunniesForever__Character__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class RowObject;

class Character : public Node
{
    Action* _blinkAction;
    float vSpeed;
    
    Sprite* _jumpSprite;
    Animation* _jumpAnim;
public:
    
    static Character* CharacterWithColor(const Color3B& color);
    bool initWithColor(const Color3B& color);
    void update(float dt);
    void draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated);
    void Jump();
    
    void doDamage(int damage);
    bool onCollideWithObject(RowObject* rowObject);
};

#endif /* defined(__BunniesForever__Character__) */
