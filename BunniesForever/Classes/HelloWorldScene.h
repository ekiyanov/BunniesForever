#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
    {
        renderer->render();
        
        cocos2d::DrawPrimitives::drawSolidRect(cocos2d::Point(0,0),cocos2d::Point(getContentSize().width,
                                                                                  getContentSize().height),
                                               Color4F(1,1,1,1));
    }
};

#endif // __HELLOWORLD_SCENE_H__
