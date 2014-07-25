//
//  RunRow.h
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#ifndef __BunniesForever__RunRow__
#define __BunniesForever__RunRow__

#include <iostream>
#include "cocos2d.h"
#include "RowObject.h"
using namespace cocos2d;
class Character;
class RunRow : public Layer
{
    Character* pCharacter;
    
    Vector<RowObject*>       _rowObjects;
    
    float           _nextGeneration;
    
public:
    bool init(const Color3B & color);
    
    bool onTouchBegan(Touch* touch, Event* event);
    
    void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
    
    void update(float dt);
    
    void updateCollision();
    
    void updateGeneration(float dt);
    
    void killAllObjects();
};
#endif /* defined(__BunniesForever__RunRow__) */
