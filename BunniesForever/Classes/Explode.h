//
//  Explode.h
//  NukeGun
//
//  Created by Kiyanov Eugene on 1/26/13.
//
//

#ifndef __NukeGun__Explode__
#define __NukeGun__Explode__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class Explode:public Node
{
    float _velocityx,_velocityy;
    Sprite*           _spr;
    float               _initialScale;
    int                 _type;
    
    SEL_SCHEDULE        _updateFunc;
    
    bool                _running;
public:
    bool init();
    void setType(int type);
    void start();
    void setInitialScale(float sc);
    
    void onUpdate1(float dt);
    void onUpdate2(float dt);
    
    void onAnimDone();
};

extern Node* createExplode1(Dictionary*);
extern Node* createExplode2(Dictionary*);
extern Node* createExplode3(Dictionary*);

extern void createExplodeSystem(Node* parent,const Point& position);
extern void createLargeExplodeSystem(Node* parent,const Point& position);

#endif /* defined(__NukeGun__Explode__) */
