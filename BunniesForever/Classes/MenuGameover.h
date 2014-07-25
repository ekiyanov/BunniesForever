//
//  MenuGameover.h
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#ifndef __BunniesForever__MenuGameover__
#define __BunniesForever__MenuGameover__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class MenuGameover : public Layer
{
    Label* topScoreLbl;
    Label* lastScoreLbl;
public:
    void draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated);
    bool init();
    
    void onEnter();
    bool onTouchBegan(Touch* touch,Event*){return true;}
};
#endif /* defined(__BunniesForever__MenuGameover__) */
