//
//  MenuPause.h
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#ifndef __BunniesForever__MenuPause__
#define __BunniesForever__MenuPause__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class MenuPause : public Layer
{
public:
    void draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated);
    bool init();
    bool onTouchBegan(Touch* touch,Event*){return true;}
};
#endif /* defined(__BunniesForever__MenuPause__) */
