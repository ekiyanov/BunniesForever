//
//  RowObject.h
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#ifndef __BunniesForever__RowObject__
#define __BunniesForever__RowObject__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;
class Character;
class RowObject: public Node
{
    int _type;
    
    bool _paused;
public:
    virtual bool init();
    
    virtual int type();
    
    void setPaused(bool state){_paused=state;}
    
    virtual void setType(int type);
    virtual bool activated(Character*){};
    virtual void draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated);
    virtual void update(float dt);
    virtual void removeFromGame();
};

#endif /* defined(__BunniesForever__RowObject__) */
